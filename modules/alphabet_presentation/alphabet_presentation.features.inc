<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function alphabet_presentation_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_imagecache_default_presets().
 */
function alphabet_presentation_imagecache_default_presets() {
  $items = array(
    'full' => array(
      'presetname' => 'full',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '1400',
            'height' => '100%',
          ),
        ),
      ),
    ),
    'thumbnail' => array(
      'presetname' => 'thumbnail',
      'actions' => array(
        '0' => array(
          'weight' => '-10',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '360',
            'height' => '240',
          ),
        ),
        '1' => array(
          'weight' => '-9',
          'module' => 'imagecache_canvasactions',
          'action' => 'canvasactions_roundedcorners',
          'data' => array(
            'radius' => '20',
            'independent_corners_set' => array(
              'independent_corners' => 0,
              'radii' => array(
                'tl' => '',
                'tr' => '',
                'bl' => '',
                'br' => '',
              ),
            ),
          ),
        ),
        '2' => array(
          'weight' => '-8',
          'module' => 'imagecache',
          'action' => 'imagecache_rotate',
          'data' => array(
            'degrees' => '-5',
            'random' => 0,
            'bgcolor' => '#ffffff',
          ),
        ),
        '3' => array(
          'weight' => '0',
          'module' => 'imagecache_canvasactions',
          'action' => 'canvasactions_canvas2file',
          'data' => array(
            'xpos' => 0,
            'ypos' => 0,
            'alpha' => '100',
            'path' => 'profiles/alphabet_presentation/themes/sitetheme/images/image_underlay.gif',
            'dimensions' => 'original',
          ),
        ),
      ),
    ),
    'thumbnail_small' => array(
      'presetname' => 'thumbnail_small',
      'actions' => array(
        '0' => array(
          'weight' => '0',
          'module' => 'imagecache',
          'action' => 'imagecache_scale_and_crop',
          'data' => array(
            'width' => '100',
            'height' => '100',
          ),
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implementation of hook_node_info().
 */
function alphabet_presentation_node_info() {
  $items = array(
    'item' => array(
      'name' => t('Item'),
      'module' => 'features',
      'description' => t('An item (image, story, media)'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
