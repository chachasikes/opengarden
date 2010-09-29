<?php
// $Id: views_plugin_row_noderef_image.inc,v 1.1 2009/08/09 08:40:36 roetzi Exp $
/**
 * @file
 * TODO
 */


/**
 * Views plugin to render an upcoming game entry.
 */
class views_plugin_row_noderef_image extends views_plugin_row {
  function render($row) {
    drupal_add_css(drupal_get_path('module', 'noderef_image_helper') . '/noderef_image_helper.css');
    if (arg(0) == 'noderef_image_helper') {
      $field_id = arg(2);
      $url = 'noderef_image_helper/insert/' . $field_id . '/' . $row->nid;
    }
    else {
      $url = 'node/' . $row->nid;
    }
    
    $node = node_load($row->nid);
    $image = noderef_image_helper_image_from_nid($row->nid);
    $dim = getimagesize($image['filepath']);
    $size = format_size($image['filesize']);
    
    $output = '<div class="noderef-browse-element">';
    $output .= '<h2>' . l($node->title, $url) . '</h2>';
    $output .= l(theme('noderef_image_helper', $row->nid, noderef_image_helper_preview_preset()), $url, array('html' => TRUE));
    $output .= '<div class="info">';
    $output .= format_date($node->created, 'short') . ' / ' . theme('username', user_load($node->uid)) . '<br/>';
    $output .= $dim[0] . 'x' . $dim[1] .' px / ' . $size;
    $output .= '</div>';    
    $output .= '</div>';
    
    return $output;
  }
}

