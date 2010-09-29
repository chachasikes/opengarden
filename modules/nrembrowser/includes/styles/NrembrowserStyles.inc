<?php
// $Id: NrembrowserStyles.inc,v 1.1.2.7 2010/08/30 21:41:06 aaron Exp $

/**
 * @file
 * Styles definitions for nrembrowser.
 */

class NrembrowserStyles extends StylesDefault {
  public $nid;
  public $title;
  public $alt;

  public $width;
  public $height;

  public $float;

  public $imagecache_preset = '';
  public $link;

  public $prefix = '<span class="styles nrembrowser-styles">';
  public $suffix = '</span>';

  function get_nid() {
    return $this->get('nid');
  }
  function set_nid($value) {
    return $this->set('nid', $value);
  }
  function get_title() {
    return $this->get('title');
  }
  function set_title($value) {
    // @TODO: Token support.
    return $this->set('title', $value);
  }
  function get_alt() {
    return $this->get('alt');
  }
  function set_alt($value) {
    return $this->set('alt', $value);
  }
  function get_width() {
    return $this->get('width');
  }
  function set_width($value) {
    return $this->set('width', $value);
  }
  function get_height() {
    return $this->get('height');
  }
  function set_height($value) {
    return $this->set('height', $value);
  }
  function get_imagecache_preset() {
    return $this->get('imagecache_preset');
  }
  function set_imagecache_preset($value) {
    return $this->set('imagecache_preset', $value);
  }
  function get_link() {
    return $this->get('link');
  }
  function set_link($value) {
    return $this->set('link', $value);
  }
  function get_float() {
    return $this->get('float');
  }
  function set_float($value) {
    if ($value) {
      $this->set_prefix('<span class="styles nrembrowser-styles nrembrowser-styles-float-'. filter_xss($value) .'">');
    }
    else {
      $this->set_prefix('<span class="styles nrembrowser-styles">');
    }
    return $this->set('float', $value);
  }

  // Effect callbacks when rendering.
  function thumbnail($effect) {
    $attributes = array();
    $width = $this->get_width();
    $height = $this->get_height();
    if (isset($width)) {
      $attributes['width'] = $width;
    }
    if (isset($height)) {
      $attributes['height'] = $height;
    }

    // Set any WYSIWYG prescribed styles.
    $styles = array();
    foreach (array('border-width', 'border-style', 'margin', 'margin-top', 'margin-right', 'margin-bottom', 'margin-left') as $attribute) {
      $value = $this->get($attribute);
      if (isset($value)) {
        $styles[$attribute] = $attribute .':'. check_plain($value);
      }
    }

    if (!empty($styles)) {
      $attributes['style'] = implode(';', $styles);
    }

    $this->set_output(theme('nrembrowser_thumbnail', $this->get_nid(), $this->get_alt(), $this->get_title(), FALSE, NULL, $this->get_imagecache_preset(), $attributes, $this->get_link()));
  }

  function resize($effect) {
    if (isset($effect['width'])) {
      $this->set_width($effect['width']);
    }
    if (isset($effect['height'])) {
      $this->set_height($effect['height']);
    }
  }

  function float($effect) {
    $this->set_float($effect['float']);
  }

  function imagecache($effect) {
    $this->set_imagecache_preset($effect['preset']);
    $this->thumbnail($effect);
  }

  function link_to_node($effect) {
    $this->set_link(TRUE);
    if (!$this->get_output && $this->get_title()) {
      $this->set_output(l($this->get_title, 'node/'. $this->get_nid()));
    }
  }

  function link_to_path($effect) {
    $this->set_link($effect['path']);
    if (!$this->get_output && $this->get_title()) {
      $this->set_output(l($this->get_title, $effect['path']));
    }
  }

  function teaser($effect) {
    $this->set('node', node_load($this->get_nid()));
    $this->set_output(node_view($this->get('node')));
  }

}
