<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function flickr_feeds_sets_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => 1);
  }
  elseif ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function flickr_feeds_sets_node_info() {
  $items = array(
    'flickr_item' => array(
      'name' => t('Flickr Item'),
      'module' => 'features',
      'description' => t('A Flickr Feed item'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
    'flickr_set' => array(
      'name' => t('Flickr Set'),
      'module' => 'features',
      'description' => t('Feed of Flickr Set'),
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

/**
 * Implementation of hook_views_api().
 */
function flickr_feeds_sets_views_api() {
  return array(
    'api' => '2',
  );
}
