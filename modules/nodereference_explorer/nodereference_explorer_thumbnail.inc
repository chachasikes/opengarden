<?php 

/**
 * Widgets setting for thumbnail generation
 * @param $op
 * @param $widget
 * @return 
 *   $form elements
 */
function nodereference_explorer_thumbnail_widget_settings($op, $widget) {
 switch ($op) {
    case 'form':
    	if ($widget['type'] == 'nodereference_explorer') {
    		$form = array();
    		$match = isset($widget['thumbnail_teaser']) ? $widget['thumbnail_teaser'] : 'Default';
    	
    		//get all presets
    		$presets = imagecache_presets();
    	
    		
    		//prepare as a list of presets for a select field (key = value)
        	$preset_names = array();
    		$preset_names['Default'] = 'Default';
    	
    		foreach ($presets as $preset) {
    			$preset_names[$preset['presetname']] = $preset['presetname'];
    		}
    		
    		//prepare as a list of field names for a select field (key = value)
    		$fields = content_fields();
    		$field_names = array();
    		foreach ($fields as $field) {
    			$field_names[$field['field_name']] = $field['field_name'];
    		}
    		array_unshift($field_names, '');
    		
    		//create the field's selection form item
    		$node_fields = isset($widget['thumbnail_node_fields']) ? $widget['thumbnail_node_fields'] : '';
    		$form['thumbnail_node_fields'] = array(
            	'#type' => 'select',
            	'#title' => t('Referencing node field name for thumbnail generation'),
    			'#options' => $field_names,
            	'#default_value' => $node_fields,
            	'#description' => t('Select the field name (e. g. field_photo) of the referencing content type field<br/>
            		which should be generated as a thumbnail. For example, if this content type is called "news" and you <br/>
            		refer a content type called "photo" holding an imagefield called "field_foto", the value "field_foto" is to be selected.<br/>
            		Leave it blank when you do not want to generate thumbnails.'),
          );
          
          //create the preset selection form item
          $form['thumbnail_teaser'] = array(
            	'#type' => 'select',
            	'#title' => t('Thumbnail preset'),
            	'#options' => $preset_names,
            	'#default_value' => $match,
            	'#description' => t('Choose the preset which should generate thumbnails for images. <br/>
            		The default preset does nothing at the moment, i. e. leaves the image in full size.<br/> 
            		The recommended configuration is as followed:<br/>
            		1) Create a preset under "Administer->Site building->ImageCache"<br/>
            		2) Add a resize action, which scales the image to width 75 px and height 50 px (Ratio: 3:2)<br/>
            		3) Return to this form and choose your created preset<br/>
            		Now you should see your results in the selection table, f. e. in "Default value"<br/>'),
          );
      return $form;
    }

    //specify an array of form keys here which should be saved
    case 'save':
      return array('thumbnail_node_fields', 'thumbnail_teaser');
  }
}

/**
 * get the field value of a node
 */
function nodereference_explorer_thumbnail_field_value($nid, $field_name) {
	$node = node_load($nid);
	return $node->$field_name;
}

/**
 * Create a thumbnail from a full sized image
 * @param $imageLink
 *   link to the full sized image
 * @param $teaser
 *   name of the thumbnail preset
 * @return
 *   url of the created thumbnail
 */
function nodereference_explorer_thumbnail_generate($imageLink, $teaser) {
	//Thumbnail generation, needs a preset called thumbnail
	
	if (!teaser) $teaser = 'Default'; //default	
	
	if ($teaser != 'Default') {
		$thumbnail_preset_name = $teaser;
		
		//get preset by name
		$thumbnail_preset = imagecache_preset_by_name($thumbnail_preset_name);
			
		//get all actions attached to the preset
		$thumbnail_preset_actions = imagecache_preset_actions($thumbnail_preset);
		
		//build the thumbnail url
		$thumbnail_url = imagecache_create_url($thumbnail_preset_name, $imageLink);
		
		//create the thumbnail at the specifeid location (url)
		imagecache_build_derivative($thumbnail_preset_actions, $imageLink, $thumbnail_url);
	}
	else { //nothing is happening now by default, i. e. the whole picture is shown
		   //TO-DO: add generic imagecache resizing with width 75 px and height 50 px
		$thumbnail_url = '/'.$imageLink; //without leading slash
		/*$actiondefinitions = imagecache_action_definitions();
		//imagecache
		$resize_action = $actiondefinitions['imagecache_resize'];
		//imagecache_
		
		//$thumbnail_preset_actions = imagecache_preset_actions($thumbnail_preset);
		$thumbnail_url = imagecache_create_url('default-photopicker-thumbnail', $imageLink);
		$sucess = imagecache_build_derivative($resize_action, $imageLink, $thumbnail_url);*/
	}
	return $thumbnail_url;
}