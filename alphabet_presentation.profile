<?php
// $Id$

/**
 * @file
 *
 * Install profile for Alphabet presentation. Loads alphabet presentation feature.
 */

function alphabet_presentation_profile_details() {
  return array(
    'name' => 'Alphabet Presentation',
    'description' => 'Create an interactive presentation, organized by the alphabet.'
  );
}

/**
 * Implementation of hook_profile_modules().
 */
function alphabet_presentation_profile_modules() {
  global $install_locale;
  // Drupal core
  $modules = array(
    'features',
    'alphabet_presentation',
  );
  return $modules;
}

function alphabet_presentation_profile_final() {
  //  db_query("INSERT INTO {blocks} VALUES ('block', '1', 1, 0, 1, 0, 0, 1, 'my*', '')");

  // Enable default theme.
  drupal_system_enable('theme', 'sitetheme');
  variable_set('theme_default', 'sitetheme');

  // Default theme settings.
  variable_set('theme_sitetheme_settings', array(
    'default_logo' => 0,
    'toggle_name' => 1,
    'toggle_slogan' => 0,
    'toggle_mission' => 1,
  ));

}

/**
 * Implementation of hook_profile_task_list().
 */
function alphabet_presentation_profile_task_list() {
  return array(
    'alphabet-presentation-configure' => st('alphabet presentation configuration'),
  );
}

/**
 * Implementation of hook_profile_tasks().
 */
function alphabet_presentation_profile_tasks(&$task, $url) {
  global $install_locale;
  $output = '';
  drupal_set_message(t("Installing Alphabet Presentation feature"));
  // Clear caches.
  drupal_flush_all_caches();
  module_rebuild_cache();
  menu_rebuild();
  return $output;
}
