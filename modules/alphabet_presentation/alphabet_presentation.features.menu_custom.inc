<?php

/**
 * Implementation of hook_menu_default_menu_custom().
 */
function alphabet_presentation_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-creator
  $menus['menu-creator'] = array(
    'menu_name' => 'menu-creator',
    'title' => 'Content',
    'description' => 'Add ',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add ');
  t('Content');


  return $menus;
}
