<?php
// $Id: nrembrowser.variables.inc,v 1.2.2.13 2010/08/04 21:34:46 aaron Exp $

/**
 * @file
 * Variable defaults for Node Reference/Embed Media Browser (nrembrowser).
 */

/**
 * Define our constants.
 */

/**
 * This is the variable namespace, automatically prepended to module variables.
 */
define('NREMBROWSER_NAMESPACE', 'nrembrowser__');

/**
 * Wrapper for variable_get() using the Node Reference/Embed Media Browser
 * (nrembrowser) variable registry.
 *
 * @param string $name
 *  The variable name to retrieve. Note that it will be namespaced by
 *  pre-pending NREMBROWSER_NAMESPACE, as to avoid variable collisions
 *  with other modules.
 * @param unknown $default
 *  An optional default variable to return if the variable hasn't been set
 *  yet. Note that within this module, all variables should already be set
 *  in the nrembrowser_variable_default() function.
 * @return unknown
 *  Returns the stored variable or its default.
 *
 * @see nrembrowser_variable_set()
 * @see nrembrowser_variable_del()
 * @see nrembrowser_variable_default()
 */
function nrembrowser_variable_get($name, $default = NULL) {
  // Allow for an override of the default.
  // Useful when a variable is required (like $path), but namespacing is still
  // desired.
  if (!isset($default)) {
    $default = nrembrowser_variable_default($name);
  }
  // Namespace all variables.
  $variable_name = NREMBROWSER_NAMESPACE . $name;
  return variable_get($variable_name, $default);
}

/**
 * Wrapper for variable_set() using the Node Reference/Embed Media Browser
 * (nrembrowser) variable registry.
 *
 * @param string $name
 *  The variable name to set. Note that it will be namespaced by
 *  pre-pending NREMBROWSER_NAMESPACE, as to avoid variable collisions with
 *  other modules.
 * @param unknown $value
 *  The value for which to set the variable.
 * @return unknown
 *  Returns the stored variable after setting.
 *
 * @see nrembrowser_variable_get()
 * @see nrembrowser_variable_del()
 * @see nrembrowser_variable_default()
 */
function nrembrowser_variable_set($name, $value) {
  $variable_name = NREMBROWSER_NAMESPACE . $name;
  return variable_set($variable_name, $value);
}

/**
 * Wrapper for variable_del() using the Node Reference/Embed Media Browser
 * (nrembrowser) variable registry.
 *
 * @param string $name
 *  The variable name to delete. Note that it will be namespaced by
 *  pre-pending NREMBROWSER_NAMESPACE, as to avoid variable collisions with
 *  other modules.
 *
 * @see nrembrowser_variable_get()
 * @see nrembrowser_variable_set()
 * @see nrembrowser_variable_default()
 */
function nrembrowser_variable_del($name) {
  $variable_name = NREMBROWSER_NAMESPACE . $name;
  variable_del($variable_name);
}

/**
 * The default variables within the Node Reference/Embed Media Browser
 * (nrembrowser) namespace.
 *
 * @param string $name
 *  Optional variable name to retrieve the default. Note that it has not yet
 *  been pre-pended with the NREMBROWSER_NAMESPACE namespace at this time.
 * @return unknown
 *  The default value of this variable, if it's been set, or NULL, unless
 *  $name is NULL, in which case we return an array of all default values.
 *
 * @see nrembrowser_variable_get()
 * @see nrembrowser_variable_set()
 * @see nrembrowser_variable_del()
 */
function nrembrowser_variable_default($name = NULL) {
  static $defaults;

  if (!isset($defaults)) {
    $defaults = array(
      'thumbnail_width' => '120',
      'thumbnail_height' => '120',
      'wysiwyg_default_icon' => drupal_get_path('module', 'nrembrowser') .'/plugins/nrembrowser/images/icon-image.png',
      'imagecache_preset' => 'nrembrowser_thumbnail',
      'wysiwyg_imagecache_preset' => '',

      // IFrame variables for the embedded node add form.
      'iframe_width' => '100%',
      'iframe_height' => '300',
      'no_iframe' => 'Your browser does not support iframes.',

      'wysiwyg_tabs_views' => array(
        array(
          'view_name' => 'nrembrowser_user',
          'view_display_id' => 'default',
          'view_arguments' => '',
        ),
      ),

      // Default browser options.
      'header' => '',
      'header_empty' => FALSE,
      'footer' => '',
      'footer_empty' => FALSE,
      'empty_message' => '',
      'use_pager' => TRUE,
      'items_per_page' => 12,
      'pager_element' => 0,

      // If TRUE, then modify browser views to filter by field allowed types.
      'modify_default_view' => TRUE,
      'modify_other_views' => TRUE,

      // If TRUE, then display a formatter dialog when selecting from WYSIWYG.
      'wysiwygStyleFormatterSelect' => TRUE,
      'default_wysiwyg_style' => 'thumbnail',
      'default_wysiwyg_imagecache' => 'nrembrowser_thumbnail',
    );

    // Add node type defaults for browser thumbnails.
    foreach (node_get_types() as $type => $object) {
      $defaults['browser_image_'. $type] = 'teaser';
      $defaults['wysiwyg_type_allowed_'. $type] = FALSE;
    }
  }

  if (!isset($name)) {
    return $defaults;
  }

  if (isset($defaults[$name])) {
    return $defaults[$name];
  }
}

/**
 * Return the fully namespace variable name.
 *
 * @param string $name
 *  The variable name to retrieve the namespaced name.
 * @return string
 *  The fully namespace variable name, prepended with
 *  NREMBROWSER_NAMESPACE.
 */
function nrembrowser_variable_name($name) {
  return NREMBROWSER_NAMESPACE . $name;
}

