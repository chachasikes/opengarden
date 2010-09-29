<?php
// $Id: nrembrowser.views.inc,v 1.1.2.3 2010/08/10 14:56:28 aaron Exp $

/**
 * @file nrembrowser.views.inc
 *
 * Functions implementing various Views hooks for nrembrowser.
 */

/**
 * Implementation of hook_views_pre_build().
 */
function nrembrowser_views_pre_build(&$view) {
  // Possibly modify any views from the browser tabs.
  if (arg(0) == 'nrembrowser' && arg(1) == 'media' && arg(2) == 'tab') {
    // Only modify the view if allowed.
    if ((($view->name == 'nrembrowser_user') && nrembrowser_variable_get('modify_default_view')) || (($view->name != 'nrembrowser_user') && nrembrowser_variable_get('modify_other_views'))) {
      // If this view has a node 'type' filter...
      if (isset($view->filter['type'])) {
        // ... Grab the field's allowed types.
        $allowed_types = nrembrowser_field_allowed_types($_GET['field_name']);

        // If we have allowed types for the field, then apply them to the view.
        // This ensures exposed widgets are built properly,
        // but we'll still need to apply the filter in the query alter later.
        if (is_array($allowed_types)) {
          // Reset the type filter.
          $view->filter['type']->value_options = array();

          // Add the types to the filter.
          foreach ($allowed_types as $type) {
            // Make sure we add the type name for any exposed filters.
            $view->filter['type']->value_options[$type] = node_get_types('name', $type);
          }
        }
      }
    }
  }
}

/**
 * Implementation of hook_views_query_alter().
 */
function nrembrowser_views_query_alter(&$view, &$query) {
  // Possibly modify any view queries from the browser tabs.
  if (arg(0) == 'nrembrowser' && arg(1) == 'media' && arg(2) == 'tab') {
    // Only modify the view query if allowed.
    if ((($view->name == 'nrembrowser_user') && nrembrowser_variable_get('modify_default_view')) || (($view->name != 'nrembrowser_user') && nrembrowser_variable_get('modify_other_views'))) {
      // If this view has a node 'type' filter...
      if (isset($view->filter['type'])) {
        // If we have any allowed types set earlier, apply them to the query.
        if (is_array($view->filter['type']->value_options)) {
          // Now we'll alter the query to only return allowed types,
          // but only if we haven't already selected a type in the filter.
          $found = FALSE;
          if (!empty($query->where)) {
            foreach ($query->where[0]['clauses'] as $clause) {
              if (strstr($clause, 'node.type') !== FALSE) {
                $found = TRUE;
              }
            }
          }
          if (!$found) {
            // There is no node.type in the filter, so we'll do that now.
            $query->where[0]['clauses'][] = 'node.type in ('. db_placeholders($view->filter['type']->value_options, 'varchar') .')';
            $query->where[0]['args'] = array_merge((array)$query->where[0]['args'], array_keys($view->filter['type']->value_options));
          }
        }
      }
    }
  }
}
