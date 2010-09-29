<?php 

function nodereference_explorer_widget_info() {
	return array( 
    	'nodereference_explorer' => array(
        	'label' => t('Explorer'),
        	'field types' => array('nodereference'), //add to the noderef field type is done here
    )
  );
}

/**
 * Implementation of hook_widget().
 * 
 * This method attaches a single form element to the form. It will be 
 * built out and validated in the callback(s) listed in hook_elements. 
 * We build it out in the callbacks rather than here in hook_widget so 
 * it can be plugged into any module that can provide it with valid
 * $field information.
 *
 * Content module will set the weight, field name and delta values
 * for each form element. This is a change from earlier CCK versions
 * where the widget managed its own multiple values.
 *
 * If there are multiple values for this field, the content module will
 * call this function as many times as needed.
 *
 * @param $form
 *   the entire form array, $form['#node'] holds node information
 * @param $form_state
 *   the form_state, $form_state['values'][$field['field_name']]
 *   holds the field's form values.
 * @param $field
 *   the field array
 * @param $items
 *   array of default values for this field
 * @param $delta
 *   the order of this item in the array of subelements (0, 1, 2, etc)
 *
 * @return
 *   the form item for a single element for this field
 */
function nodereference_explorer_widget(&$form, &$form_state, $field, $items, $delta = 0) {
	if ($field['widget']['type'] == 'nodereference_explorer') {
		 $nodereference_field = $field;
		  // The nodereference explorer widget doesn't need to create its own
  		 // element, it wraps around the autocomplete widgets and exploits all 
  		 //functionality of that widget and extends it by our own widgets.
   		 $nodereference_field['widget']['type'] = 'nodereference_autocomplete';
		 $element = nodereference_widget($form, $form_state, $nodereference_field, $items, $delta);
		 
		 //add now a explorer specific rendering process
		 $nodereference_field['widget']['type'] = 'nodereference_explorer'; //for theme
		 $element['#process'] = array('nodereference_explorer_widget_process');
		 $element['#attributes'] = array('thumbnail_node_fields' => $field['widget']['thumbnail_node_fields'],
		 								 'thumbnail_teaser' => $field['widget']['thumbnail_teaser']);
		 return $element;
	}
}

/**
 * Implementation of hook_widget_settings().
 */
function nodereference_explorer_widget_settings($op, $widget) {
	return nodereference_explorer_thumbnail_widget_settings($op, $widget);
}

/**
 * Enhances the explorer further with a dialog popup, flexigrid table fired
 * by buttons. Attention: This is somehow experimental now and you are leaving
 * the drupal form api. Parameters like dialog or table layout should be made
 * configurable.
 * @param $element
 *   form widget
 * @param $edit
 * @param $form_state
 *   the form_state, $form_state['values'][$field['field_name']] holds the field's form values.
 * @param $form
 *   the entire form array, $form['#node'] holds node information
 * @return $element
 *   widget including javascript
 */
function nodereference_explorer_widget_process($element, $edit, $form_state, $form) {

   // The nodereference explorer widget doesn't need to create its own
   // element, it can wrap around and exploits all functionality of
   //that widget and extends it by our own widgets.
   // Add a validation step where the value can be unwrapped.
	$element = nodereference_autocomplete_process($element, $edit, $form_state, $form);

	//generate necessay ids
	//form_clean_id($element['#id']);
	$field_id = $element['#id'];  //id of element
	$select_id = $field_id.'-select-node'; //id of select button
	$remove_id = $field_id.'-remove-node'; //id of remove button
	$widget_id = $field_id.'-nid-nid'; //id of autocomplete text field
	$dialog_id = $field_id.'-dialog'; //id of dialog
	$iframe_id = $dialog_id.'-iframe'; //id of internal frame where dialog content is loaded
	$image_preview_id = $field_id.'-photo';
	
	//url for flexigrid data which calls json data from client side
	$service_node_url = '/'. NODE_REFERENCE_SERVICE_NODE_DATA .'/'.$element['#field_name'];
	
	//browse and remove buttons
    $buttons = '<input id="'.$select_id.'" type="button" value="Browse"/>&nbsp;&nbsp;&nbsp;
		 	 	<input id="'.$remove_id.'" type="button" value="Clear"/>';
  	
  	//dialog div holding an internal frame which loads a html page containing the flexi/
  	//grid setup. This loose coupling is necessar to seperate the themes (css) which disturb
  	//the flexigrid table. Parameters are transmitted via Cookies, i. e. the aqCookie lib.
  	$dialog = '<div id="'.$dialog_id.'" class="flora" title="Node/Item Selection">'
        				.'<iframe id="'.$iframe_id.'" src="/'.NODE_REFERENCE_EXPLORER_MODULE_PATH.'/table/selection_table.html" frameborder="0" width="630" height="550"></iframe>'
        			.'</div>';
        			
      
  	//get the field's node id
  	$nid = $element['#default_value']['nid'];
  	
  	//get field for thumbnail generation
	if (isset($element['#attributes']['thumbnail_node_fields'])) {
  		$node_field = $element['#attributes']['thumbnail_node_fields'];
	}
  	
	//generate a thumbnail from an imagefield
  	if ($node_field != null) {	
  		
  		 //get the field's value
 		 $image_field = nodereference_explorer_thumbnail_field_value($nid, $node_field);

 		 //get the path to the file
  		 $filepath = $image_field[0]['filepath'];
  		
  		 //get the teaser for the thumbnail (see widget settings)
  		if (isset($element['#attributes']['thumbnail_teaser'])) {
  			$thumbnail_teaser = $element['#attributes']['thumbnail_teaser'];
  		}
  		//set the initaliazation params
  		$src = nodereference_explorer_thumbnail_generate($filepath, $thumbnail_teaser);
  		$href = $filepath;
  		$name = $image_field[0]['filename'];
  		$alt = $filepath;
  		$image_id = $image_field[0]['fid'];
  	}
	else {
  		$href = '';
  		$src = '';
  		$alt = '';
  		$name = '';
  		$image_id = '';
  	}
  	//load the current node object
  	$node = node_load($nid);
  	
  	if ($href == '') { //no image thumbnail
  		$style = 'display:none';
  		$image_preview = "<img id=\"$image_preview_id\" style=\"$style\" longdesc=\"".date("r", $node->changed)."\"/>";
  	}
  	else { //image thumbnail
  		$style = 'display:true';
  		$image_preview =
        "<a href=\"/$href\" style=\"$style\" class=\"thickbox\">"
        ."<img id=\"$image_preview_id\" src=\"$src\" alt=\"$alt\" name=\"$name\" image_id=\"$image_id\" longdesc=\"".date("r", $node->changed)."\"/></a>";
       // ."<br/>";
  	}
  	
  	//server name
    $server_name = $_SERVER['SERVER_NAME'];
   // $server_info = '<div id="server-info" style="display:none">'.$server_name.'</div>';

  	 //add html elements after the autocomplete widget
  	$element['#suffix'] = $image_preview . '<br/>'.$buttons . $dialog; // . $server_info;
    //$element['#prefix'] = $image_preview;
    
    
  	//add javascript
  	//this is ugly as hell, there must be a better way to do this!
  	//very old school js creation
  	$js = '$(document).ready(function() {
  	
  	$.aqCookie.domain = \''.$server_name.'\'; //drupal-dev-local.osce.org
  	$.aqCookie.del(\'nodereference_explorer_image_thumbnail\');
  	$.aqCookie.del(\'nodereference_explorer_image_full\');
  	$.aqCookie.del(\'nodereference_explorer_service_url\');
  	$.aqCookie.del(\'nodereferenece_explorer_id\');
  	$.aqCookie.del(\'nodereferenece_explorer_date\');
  	$.aqCookie.del(\'nodereferenece_explorer_title\');
  		
	$("#'.$dialog_id.'").dialog({ 
		modal: true, 
		   width: 680,
		   height: 500,
		   minWidth: 680,
		   minHeight: 500,
		overlay: { opacity: 0.5,
				   background: "black", 
				   show: "slow" },
				   autoOpen: false,
				   buttons: {
                        "Ok": function() {
                        $.aqCookie.domain = \''.$server_name.'\';
					    var node = $.aqCookie.get([\'nodereferenece_explorer_id\', 
					                              \'nodereferenece_explorer_title\', 
					                              \'nodereferenece_explorer_date\',
					                              \'nodereferenece_explorer_image_thumbnail\',
					                              \'nodereferenece_explorer_image_full\']);
					   
					  $("#'.$widget_id.'").val(node[\'nodereferenece_explorer_title\'] + " [nid:"+node[\'nodereferenece_explorer_id\']+"]"); //.attr("src", image[\'thumbnail\']);
					 // $("#'.$image_preview_id.'").parent().attr("date", node[\'nodereferenece_explorer_date\']);
					  $date = node[\'nodereferenece_explorer_date\'];
					  
					  if (node[\'nodereferenece_explorer_image_thumbnail\'] == undefined) {
						//alert($date);	
					  $("#'.$image_preview_id.'").replaceWith(\'<a href="" style="display:none"><img id="'.$image_preview_id.'" style="display:none" longdesc="\'+$date+\'"/></a>\');
						}
						else {
						
						$img_html = "<a href=\"";
						$img_html += node[\'nodereferenece_explorer_image_full\']+"\" style=\"display:true\" class=\"thickbox\">";
        				$img_html += "<img id=\"'.$image_preview_id.'\" src=\""+node[\'nodereferenece_explorer_image_thumbnail\']+"\"";
        				$img_html += " alt=\""+node[\'nodereferenece_explorer_image_full\']+"\"";
        				$img_html += " name=\""+node[\'nodereferenece_explorer_title\']+"\" image_id=\""+node[\'nodereferenece_explorer_id\']+"\" longdesc=\""+node[\'nodereferenece_explorer_date\']+"\"/></a>";
        				//$img_html += "<br/>"");
						
						
							$("#'.$image_preview_id.'").replaceWith($img_html);
						
					  		//$("#'.$image_preview_id.'").attr("src", node[\'nodereferenece_explorer_image_thumbnail\']);
					  		//$("#'.$image_preview_id.'").parent().attr("href", node[\'nodereferenece_explorer_image_full\']);
					  	}
					  
					  $("#'.$image_preview_id.'").parent().attr("style", "display:true");
					 
					
  	$.aqCookie.del(\'nodereference_explorer_image_thumbnail\');
  	$.aqCookie.del(\'nodereference_explorer_image_full\');
  	$.aqCookie.del(\'nodereference_explorer_service_url\');
  	$.aqCookie.del(\'nodereferenece_explorer_id\');
  	$.aqCookie.del(\'nodereferenece_explorer_date\');
  	$.aqCookie.del(\'nodereferenece_explorer_title\');
                   
					   $(this).dialog("close");
                        },
                        "Cancel": function() {
                        	$.aqCookie.domain = \''.$server_name.'\';
  	$.aqCookie.del(\'nodereference_explorer_image_thumbnail\');
  	$.aqCookie.del(\'nodereference_explorer_image_full\');
  	$.aqCookie.del(\'nodereference_explorer_service_url\');
  	$.aqCookie.del(\'nodereferenece_explorer_id\');
  	$.aqCookie.del(\'nodereferenece_explorer_date\');
  	$.aqCookie.del(\'nodereferenece_explorer_title\');
                        $(this).dialog("close");
                        }
                }
		});
				$("#'.$select_id.'").click(function() {
					$.aqCookie.domain = \''.$server_name.'\';
					   
  						$.aqCookie.set(\'nodereference_explorer_service_url\', \''.$service_node_url.'\');
  						
  						 var val = $("#'.$widget_id.'").val();
  						 $del1 = val.indexOf(\'[\');
  						 $del2 = val.indexOf(\']\');
  						 $title = val.substring(0, $del1-1);
  						 $id = val.substring($del1+5, $del2);
  						 
					     $src =  $("#'.$image_preview_id.'").attr("src");
					     
					     $href = $("#'.$image_preview_id.'").parent().attr("href");
					     $date = $("#'.$image_preview_id.'").attr("longdesc");
					     $("#'.$image_preview_id.'").parent().attr("style", "display:true");
  						
					    $.aqCookie.set(\'nodereference_explorer_image_thumbnail\', $src); //\''.$src.'\');
					    $.aqCookie.set(\'nodereference_explorer_image_full\', $href); //\''.$href.'\');
  						
					    $.aqCookie.set(\'nodereferenece_explorer_id\', $id); //\''.$nid.'\');
  						$.aqCookie.set(\'nodereferenece_explorer_date\', $date); //\''.date("r", $node->changed).'\');
  						$.aqCookie.set(\'nodereferenece_explorer_title\', $title); //\''.$node->title.'\');
					
					//$title = $.aqCookie.get([\'nodereferenece_explorer_title\']);
		
					$("#'.$dialog_id.'").attr("style", "display:true");
					$iframe = $("#'.$iframe_id.'").attr("src");
					$("#'.$iframe_id.'").attr("src", $iframe);
					$("#'.$dialog_id.'").dialog(\'open\');
				});
				
				$("#'.$remove_id.'").click(function() {
					$("#'.$widget_id.'").val(\'\');
					$("#'.$image_preview_id.'").replaceWith(\'<a href="" style="display:none"><img id="'.$image_preview_id.'" style="display:none" longdesc=\"\"/></a>\');
				});
			});';
	drupal_add_js($js, 'inline');
  return $element;
}