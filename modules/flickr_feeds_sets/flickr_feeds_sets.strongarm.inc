<?php

/**
 * Implementation of hook_strongarm().
 */
function flickr_feeds_sets_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_flickr_item';
  $strongarm->value = array(
    'title' => '-5',
    'revision_information' => '2',
    'author' => '1',
    'options' => '3',
    'menu' => '0',
    'taxonomy' => '-1',
  );

  $export['content_extra_weights_flickr_item'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_flickr_set';
  $strongarm->value = array(
    'title' => '-5',
    'revision_information' => '-1',
    'author' => '-2',
    'options' => '0',
    'menu' => '-3',
  );

  $export['content_extra_weights_flickr_set'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'default_feeds_importer';
  $strongarm->value = array(
    'flickr_set' => FALSE,
    'flickr_feed_tags_lists_' => TRUE,
    'feed' => FALSE,
    'node' => TRUE,
    'opml' => TRUE,
    'user' => TRUE,
  );

  $export['default_feeds_importer'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_flickr_item';
  $strongarm->value = array(
    0 => 'status',
  );

  $export['node_options_flickr_item'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_flickr_set';
  $strongarm->value = array(
    0 => 'status',
  );

  $export['node_options_flickr_set'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_flickr_item';
  $strongarm->value = '0';

  $export['upload_flickr_item'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_flickr_set';
  $strongarm->value = '0';

  $export['upload_flickr_set'] = $strongarm;
  return $export;
}
