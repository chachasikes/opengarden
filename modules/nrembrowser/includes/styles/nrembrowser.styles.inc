<?php
// $Id: nrembrowser.styles.inc,v 1.1.2.4 2010/08/18 15:41:46 aaron Exp $

/**
 * @file includes/styles/nrembrowser.styles.inc
 * Implementations of various Styles hooks.
 */

/**
 * Implementation of Styles module hook_styles_default_containers().
 */
function nrembrowser_styles_default_containers() {
  $containers = array();
  foreach (node_get_types('types', NULL, TRUE) as $type) {
    $containers[$type->type] = array(
      'class' => 'NrembrowserStyles',
    );
  }
  return array(
    'nodereference' => array(
      'filter callback' => 'nrembrowser_styles_filter',
      'containers' => $containers,
    ),
  );
}

/**
 * Implementation of Styles module hook_styles_default_styles().
 */
function nrembrowser_styles_default_styles() {
  return array(
    'nodereference' => array(
      'styles' => array(
        'thumbnail' => array(
          'label' => 'Thumbnail',
          'description' => 'Representative thumbnails linking to the content page.',
        ),
        'teaser' => array(
          'label' => 'Teaser',
          'description' => 'A short summary of the content.',
          'default theme' => 'node',
          'default theme arguments' => array(TRUE),
        ),
      ),
    ),
  );
}

/**
 * Implementation of Styles module hook_styles_default_presets().
 */
function nrembrowser_styles_default_presets() {
  $containers = array();
  foreach (node_get_types('types', NULL, TRUE) as $type) {
    $containers[$type->type] = array(
      'default preset' => 'unlinked_original',
      'styles' => array(
        'thumbnail' => array(
          'default preset' => 'linked_nrembrowser_thumbnail',
        ),
        'teaser' => array(
          'default preset' => 'teaser',
        ),
      ),
      'presets' => array(
        'unlinked_original' => array(
          array(
            'name' => 'thumbnail',
            'settings' => array(),
          ),
        ),
        'linked_original' => array(
          array(
            'name' => 'link_to_node',
            'settings' => array(),
          ),
          array(
            'name' => 'thumbnail',
            'settings' => array(),
          ),
        ),
        'linked_nrembrowser_thumbnail' => array(
          array(
            'name' => 'link_to_node',
            'settings' => array(),
          ),
          array(
            'name' => 'imagecache',
            'settings' => array(
              'preset' => 'nrembrowser_thumbnail',
            ),
          ),
        ),
        'teaser' => array(
          array(
            'name' => 'teaser',
            'settings' => array(),
          ),
        ),
      ),
    );
  }
  return array(
    'nodereference' => array(
      'containers' => $containers,
    ),
  );
}
