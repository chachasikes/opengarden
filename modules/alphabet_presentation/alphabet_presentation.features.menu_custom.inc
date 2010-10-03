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
    'description' => 'ABC Presentation Menu',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('ABC Presentation Menu');
  t('Content');


  return $menus;
}
