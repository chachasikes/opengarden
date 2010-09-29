<?php

/**
 * Implementation of hook_feeds_importer_default().
 */
function flickr_feeds_sets_feeds_importer_default() {
  $export = array();
  $feeds_importer = new stdClass;
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'flickr_set';
  $feeds_importer->config = array(
    'name' => 'Flickr Set',
    'description' => 'Import a Flickr Set',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsFlickrParser',
      'config' => array(),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'content_type' => 'flickr_item',
        'input_format' => '1',
        'update_existing' => '0',
        'expire' => '-1',
        'mappings' => array(
          0 => array(
            'source' => 'title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'description',
            'target' => 'field_teaser',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'description',
            'target' => 'field_content',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'tags',
            'target' => 'taxonomy:1',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'enclosures',
            'target' => 'field_image',
            'unique' => FALSE,
          ),
        ),
        'author' => 0,
      ),
    ),
    'content_type' => 'flickr_set',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
  );

  $export['flickr_set'] = $feeds_importer;
  return $export;
}
