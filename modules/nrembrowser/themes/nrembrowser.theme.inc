<?php
// $Id: nrembrowser.theme.inc,v 1.1.2.13 2010/08/16 20:00:57 aaron Exp $

/**
 * @file nrembrowser/themes/nrembrowser.theme.inc
 *
 * Theme preprocessing for Node Reference / Embed Media Browser (nrembrowser).
 */

function template_preprocess_nrembrowser_node_add_page(&$variables) {
  global $user;

  // Set required headers.
  drupal_set_header('Content-Type: text/html; charset=utf-8');

  $types = node_get_types();
  $type = isset($variables['type']) ? str_replace('-', '_', $variables['type']) : NULL;
  // If a node type has been specified, validate its existence.
  if (isset($types[$type]) && node_access('create', $type)) {
    // Include node_form().
    module_load_include('inc', 'node', 'node.pages');

    // Initialize settings:
    $node = array('uid' => $user->uid, 'name' => (isset($user->name) ? $user->name : ''), 'type' => $type, 'language' => '');

    $variables['content'] = drupal_get_form($type .'_node_form', $node);

    drupal_set_title(t('Create @name', array('@name' => $types[$type]->name)));

    $head_title = array(strip_tags(drupal_get_title()), variable_get('site_name', 'Drupal'));
    $variables['head_title'] = implode(' | ', $head_title);
    $variables['head'] = drupal_get_html_head();

    $variables['styles'] = drupal_get_css();
    $variables['scripts'] = drupal_get_js();

    $variables['language'] = $GLOBALS['language'];
    $variables['language']->dir = $GLOBALS['language']->direction ? 'rtl' : 'ltr';

    $variables['messages'] = theme('status_messages');

    $body_classes = array(
      'page-nrembrowser',
    );
    $variables['body_classes'] = implode(' ', $body_classes);
  }
}


/**
 * FAPI themes for nrembrowser_browser.
 *
 * The select, checkboxes or radios are already rendered by the
 * select, checkboxes, or radios themes and the HTML output
 * lives in $element['#children']. Override this theme to
 * make custom changes to the output.
 *
 * $element['#field_name'] contains the field name
 * $element['#delta]  is the position of this element in the group
 */
function theme_nrembrowser_browser($element) {
  $output = '<div class="nrembrowser-widget">';
  $output .= $element['#children'];

  // Add a thumbnail (or placeholder) for the node media.
  $output .= '<div class="widget-preview">';
  $output .= theme('nrembrowser_thumbnail', $element['#default_value']['nid'], '', '', FALSE, $element['#id'] .'-nid-nid-wrapper-nrembrowser-thumbnail', nrembrowser_variable_get('imagecache_preset'));
  $output .= '</div>';

  $output .= '</div>';
  return $output;
}

/**
 * Display the thumbnail associated with a specific node.
 */
function theme_nrembrowser_thumbnail($nid, $alt = '', $title = '', $selected = FALSE, $id = NULL, $imagecache_preset = NULL, $attributes = array(), $link = NULL) {
  static $count = 0;

  $id = $id ? $id : 'nrembrowser-thumbnail-'. ($count++);

  if ($nid) {
    $count++;

    $selected = $selected ? 'selected' : '';

    $output = theme('nrembrowser_thumbnail_image', $nid, $alt, $title, $attributes, $imagecache_preset);

    if (isset($link)) {
      if ($link === TRUE) {
        $link = 'node/'. $nid;
      }
      $output = l($output, $link, array('html' => TRUE));
    }
    return '<span id="'. $id .'" class="nrembrowser-thumbnail '. $selected .'">'. $output .'</span>';
  }

  // Ensure we have a placeholder square in the improbable case of no nid.
  return '<span id="'. $id .'" class="nrembrowser-thumbnail"></span>';
}

function theme_nrembrowser_thumbnail_image($nid, $alt, $title, $attributes, $imagecache_preset) {
  // Automatically derive image from proper field or body/teaser as needed.
  $image = nrembrowser_node_image($nid);

  $default_class = 'nrembrowser-thumbnail-image';
  $attributes['class'] = isset($attributes['class']) ? $attributes['class'] .' '. $default_class : $default_class;

  if (!isset($imagecache_preset)) {
    $imagecache_preset = nrembrowser_variable_get('imagecache_preset');
  }

  $local = (stripos($image, '://') === FALSE);
  if (module_exists('imagecache') && $local && $imagecache_preset) {
    $getsize = (!isset($attributes['width']) && !isset($attributes['height'])) ? TRUE : FALSE;
    $output = theme('imagecache', $imagecache_preset, $image, $alt, $title, $attributes, $getsize);
  }
  else {
    if ($imagecache_preset && ($imagecache_preset === nrembrowser_variable_get('imagecache_preset'))) {
      $attributes['width'] = isset($attributes['width']) ? $attributes['width'] : nrembrowser_variable_get('thumbnail_width');
      $attributes['height'] = isset($attributes['height']) ? $attributes['height'] : nrembrowser_variable_get('thumbnail_height');
    }
    $getsize = ($local && !isset($attributes['width']) && !isset($attributes['height'])) ? TRUE : FALSE;
    $output = theme('image', $image, $alt, $title, $attributes, $getsize);
  }
  return $output;
}

/**
 * Wrapper for JS insertion of thumbnail when creating a node with the dialog.
 */
function theme_nrembrowser_view_node_js_wrapper($thumbnail) {
  return '<div id="nrembrowser-view-node-js-wrapper">'. $thumbnail .'</div>';
}

/**
 * IFrame to wrap the node add form.
 */
function template_preprocess_nrembrowser_iframe(&$variables) {
  $variables['url'] = url($variables['url']);
  $variables['width'] = check_plain(nrembrowser_variable_get('iframe_width'));
  $variables['height'] = check_plain(nrembrowser_variable_get('iframe_height'));
  $variables['no_iframe'] = filter_xss(nrembrowser_variable_get('no_iframe'));
}
