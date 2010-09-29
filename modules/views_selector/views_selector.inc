<?php
// $Id$

/**
 * @file
 *
 * Views integration code for Alphabet Summary Icons module.
 */

/**
 * Implementation of hook_views_plugins().
 */
function views_selector_views_plugins() {
  return array(
    'module' => 'views_selector',
    'style' => array(
      'views_selector' => array(
        'title' => t('Make a view into a selection field selector'),
        'help' => t('Choose target field.'),
        'handler' => 'views_plugin_style_views_selector',
        'path' => drupal_get_path('module', 'views_selector'),
/*         'parent' => 'default_summary', */
/*         'theme' => 'views_views_selector', */
/*         'type' => 'summary', // only shows up as a summary style */
        'uses options' => TRUE,
/*         'help topic' => 'style-views-selector', */
      ),
    ),
  );
}

// @TODO pick the style of the view