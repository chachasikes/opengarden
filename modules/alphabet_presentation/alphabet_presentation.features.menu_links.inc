<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function alphabet_presentation_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-creator:abc
  $menu_links['menu-creator:abc'] = array(
    'menu_name' => 'menu-creator',
    'link_path' => 'abc',
    'router_path' => 'abc',
    'link_title' => 'All Items',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
  );
  // Exported menu link: menu-creator:abc-slides
  $menu_links['menu-creator:abc-slides'] = array(
    'menu_name' => 'menu-creator',
    'link_path' => 'abc-slides',
    'router_path' => 'abc-slides',
    'link_title' => 'All Items (presentation)',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('All Items');
  t('All Items (presentation)');


  return $menu_links;
}
