<?php

/**
 * Implementation of hook_taxonomy_default_vocabularies().
 */
function flickr_feeds_sets_taxonomy_default_vocabularies() {
  return array(
    'tags' => array(
      'name' => 'Tags',
      'description' => 'Assigned keywords.',
      'help' => '',
      'relations' => '1',
      'hierarchy' => '0',
      'multiple' => '0',
      'required' => '0',
      'tags' => '1',
      'module' => 'features_tags',
      'weight' => '0',
      'nodes' => array(
        'flickr_item' => 'flickr_item',
        'item' => 'item',
      ),
    ),
  );
}
