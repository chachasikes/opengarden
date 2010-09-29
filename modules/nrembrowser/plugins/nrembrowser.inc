<?php
// $Id: nrembrowser.inc,v 1.1.2.6 2010/07/09 19:28:05 aaron Exp $

/**
 * @file
 * Wysiwyg API integration of Node Reference / Embed Media Browser.
 */

/**
 * Implementation of hook_wysiwyg_plugin().
 */
function nrembrowser_nrembrowser_plugin() {
  nrembrowser_add_js();
  $plugins['nrembrowser'] = array(
    'title' => t('Node embed media browser'),
    'vendor url' => 'http://drupal.org/project/nrembrowser',
    'icon file' => 'nrembrowser.gif',
    'icon title' => t('Embed content'),
    'settings' => array(
      'global' => array(
        'types' => nrembrowser_variable_get('wysiwyg_allowed_types'),
        'defaultIcon' => url(nrembrowser_variable_get('wysiwyg_default_icon')),
        'thumbnailURL' => url('nrembrowser/browser/thumbnail'),
        'imagecachePreset' => nrembrowser_variable_get('wysiwyg_imagecache_preset'),
      ),
    ),
  );
  return $plugins;
}
