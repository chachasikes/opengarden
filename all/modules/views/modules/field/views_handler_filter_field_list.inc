<?php
// $Id: views_handler_filter_field_list.inc,v 1.1.2.1 2010/08/23 14:09:58 dereine Exp $

class views_handler_filter_field_list extends views_handler_filter_in_operator {
  function get_value_options() {
    $field = field_info_field($this->definition['title']);
    $this->value_options = list_allowed_values($field);
  }
}