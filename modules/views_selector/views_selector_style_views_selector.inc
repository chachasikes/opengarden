<?php
// $Id$

/**
 * @file
 *
 * Override a views style for views summary.
 */
class views_selector_style_views_selector extends views_plugin_style_summary {
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
      '#title' => t('Separator'),
      '#default_value' => $this->options['separator'],
    );
    $form['target_field'] = array(
      '#type' => 'textfield',
      '#title' => t('Separator'),
      '#default_value' => $this->options['separator'],
    );
  }
}
