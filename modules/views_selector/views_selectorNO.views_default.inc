<?php
// $Id$

/**
 * @file
 *
 * Provide a default view.
 */

/**
 * Implementation of hook_views_default_views().
 */
function views_selector_views_default_views() {
  // --- Paste default view here:

  // --- End paste.
  $views[$view->name] = $view;
  return $views;
}