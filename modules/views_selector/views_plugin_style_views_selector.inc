<?php
// $Id$

/**
 * @file
 *
 * Override a views style for views summary.
 */
class views_plugin_style_views_selector extends views_plugin_style {
  function option_definition() {
    $options = parent::option_definition();
    $options['target_class'] = array('default' => FALSE);
    $options['target_field'] = array('default' => FALSE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['target_class'] = array(
      '#type' => 'textfield',
      '#title' => t('Target Class'),
      '#default_value' => $this->options['target_class'],
    );
    $form['target_field'] = array(
      '#type' => 'textfield',
      '#title' => t('Target Field'),
      '#default_value' => $this->options['target_field'],
    );
    $form['select_box_class'] = array(
      '#type' => 'textfield',
      '#title' => t('Select Box Class'),
      '#default_value' => $this->options['select_box_class'],
    );
  }
}

// no...
//var_dump(drupal_get_path('module', 'views') . '/modules/field.views.inc');

//  include_once(drupal_get_path('module', 'views') . '/modules/field.views.inc');

/*     $field = field_info_field($this->definition['field_name']); */
/*     $formatters = _field_view_formatter_options($field['type']); */

/*
    $form['type'] = array(
      '#type' => 'select',
      '#title' => t('Formatter'),
      '#options' => $formatters,
      '#default_value' => $this->options['type'],
    );
*/