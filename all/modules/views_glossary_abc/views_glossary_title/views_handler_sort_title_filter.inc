<?php
// $Id$

/**
 * @file
 *
 * Override a views style for views summary.
 */
class views_handler_sort_title_filter extends views_handler_sort {
  function init(&$view, &$options) {
    parent::init($view, $options);

    // Initialize the original handler.
    $this->handler = views_get_handler($options['table'], $options['field'], 'sort');
    $this->handler->init($view, $options);
  }

  /**
   * Called to add the field to a query.
   */
  function query() {
    $params = array(
      'function' => $this->options['group_type'],
    );

    $this->query->add_orderby($this->table, $this->field, $this->options['order'], NULL, $params);
  }

  function query() {
    // Build nested trim statement to filter out numbers and selected punctuation from the glossary index.
    $trim_array = array();
    $trim_punctuation = array();
    $trim_numeric = array();

    if (!empty($this->options['filter_punctuation'])) {
      $trim_punctuation = explode(' ', $this->options['filter_punctuation']);
    }
    if ($this->options['filter_numeric']) {
      $trim_numeric = array('0', '1', '2', '3', '4', '5', '6', '7', '8', '9');
    }
    $trim_array = array_merge($trim_punctuation, $trim_numeric);

    $trim_left = '';
    $trim_right = '';

    foreach ($trim_array as $key => $value) {
      $trim_left .= 'TRIM(LEADING \'' . $value . '\' FROM ';
      $trim_right .= ') ';
    }

    $query = "SUBSTR(" . $trim_left . "
      $this->table_alias.$this->real_field "
      . $trim_right . ", 1, " . intval($this->options['limit']) . ")";


    if (!empty($formula)) {
      $this->query->add_orderby(NULL, $formula, $this->options['order'], '_' . $this->field);
    }
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['filter_punctuation'] = array('default' => '');
    $options['filter_numeric'] = array('default' => FALSE);
    $options['glossary'] = array('default' => 1);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['filter_punctuation'] = array(
      '#type' => 'textfield',
      '#title' => t('Strip punctuation'),
      '#description' => t('Enter characters to remove, separated by spaces. Example: , . *'),
      '#default_value' => $this->options['filter_punctuation'],
    );
    $form['filter_numeric'] = array(
      '#type' => 'checkbox',
      '#title' => t('Strip Numbers'),
      '#description' => t('If checked, numbers will be removed from title.'),
      '#default_value' => $this->options['filter_numeric'],
    );
  }
}
