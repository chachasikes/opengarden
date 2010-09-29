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
        'title' => t('Views Selector'),
        'help' => t('Choose target field.'),
        'handler' => 'views_plugin_style_views_selector',
        'path' => drupal_get_path('module', 'views_selector'),
        'theme' => 'theme_views_selector_style',
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}