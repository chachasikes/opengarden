<?php

/**
 * Implementation of hook_menu_default_menu_links().
 */
function alphabet_presentation_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-creator:<front>
  $menu_links['menu-creator:<front>'] = array(
    'menu_name' => 'menu-creator',
    'link_path' => '<front>',
    'router_path' => '',
    'link_title' => 'Home',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '1',
    'external' => '1',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Exported menu link: menu-creator:index
  $menu_links['menu-creator:index'] = array(
    'menu_name' => 'menu-creator',
    'link_path' => 'index',
    'router_path' => 'index',
    'link_title' => 'Index',
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
    'weight' => '-47',
  );
  // Exported menu link: menu-creator:node/357
  $menu_links['menu-creator:node/357'] = array(
    'menu_name' => 'menu-creator',
    'link_path' => 'node/357',
    'router_path' => 'node/%',
    'link_title' => 'Start',
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
  // Exported menu link: menu-creator:node/add/flickr-set
  $menu_links['menu-creator:node/add/flickr-set'] = array(
    'menu_name' => 'menu-creator',
    'link_path' => 'node/add/flickr-set',
    'router_path' => 'node/add/flickr-set',
    'link_title' => 'Add Flickr Set',
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
    'weight' => '-48',
    'parent_path' => 'slides',
  );
  // Exported menu link: menu-creator:node/add/item
  $menu_links['menu-creator:node/add/item'] = array(
    'menu_name' => 'menu-creator',
    'link_path' => 'node/add/item',
    'router_path' => 'node/add/item',
    'link_title' => 'Add Item',
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
    'parent_path' => 'slides',
  );
  // Exported menu link: menu-creator:slides
  $menu_links['menu-creator:slides'] = array(
    'menu_name' => 'menu-creator',
    'link_path' => 'slides',
    'router_path' => 'slides',
    'link_title' => 'Slides',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '1',
    'expanded' => '1',
    'weight' => '-48',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add Flickr Set');
  t('Add Item');
  t('Home');
  t('Index');
  t('Slides');
  t('Start');


  return $menu_links;
}
