<?php
// $Id: nrembrowser.admin.inc,v 1.1.2.8 2010/08/26 13:48:53 aaron Exp $

/**
 * @file
 * Administrative pages for Node Reference/Embed Media Browser (nrembrowser).
 */

/**
 * Page callback for admin/settings/nrembrowser.
 */
function nrembrowser_settings() {
  $form = array();

  $form['global'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global settings'),
    '#description' => t('Miscellaneous settings to configure the browser globally.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['global']['thumbnail_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Thumbnail settings'),
    '#description' => t('These settings affect the thumbnails for individual nodes when displayed in the dialog browser.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['global']['thumbnail_settings'][nrembrowser_variable_name('thumbnail_width')] = array(
    '#type' => 'textfield',
    '#title' => t('Thumbnail width'),
    '#description' => t('Please enter an integer for the thumbnail width. All thumbnails appearing in the browser will be scaled to this setting. Note that if you have the !imagecache module installed, a preset will be created using this value.', array('!imagecache' => l(t('Imagecache'), 'http://drupal.org/project/imagecache', array('attributes' => array('target' => '_blank'))))),
    '#default_value' => nrembrowser_variable_get('thumbnail_width'),
  );
  $form['global']['thumbnail_settings'][nrembrowser_variable_name('thumbnail_height')] = array(
    '#type' => 'textfield',
    '#title' => t('Thumbnail height'),
    '#description' => t('Please enter an integer for the thumbnail height. All thumbnails appearing in the browser will be scaled to this setting. Note that if you have the !imagecache module installed, a preset will be created using this value.', array('!imagecache' => l(t('Imagecache'), 'http://drupal.org/project/imagecache', array('attributes' => array('target' => '_blank'))))),
    '#default_value' => nrembrowser_variable_get('thumbnail_height'),
  );

  if (module_exists('imagecache')) {
    // Clear the Imagecache preset -- if we are using the default preset
    // created by the module, then changing the values above will need to
    // be reflected in the preset, assuming it hasn't been overridden.
    $default_preset = nrembrowser_variable_get('imagecache_preset');
    if ($default_preset == nrembrowser_variable_default('imagecache_preset')) {
      imagecache_preset_flush(imagecache_preset_by_name($default_preset));
    }

    // Create the option list for the select drop-down.
    $options = array();
    foreach (imagecache_presets(TRUE) as $preset) {
      $options[$preset['presetname']] = $preset['presetname'];
    }
    $form['global']['thumbnail_settings'][nrembrowser_variable_name('imagecache_preset')] = array(
      '#type' => 'select',
      '#title' => t('Imagecache preset'),
      '#description' => t('Please select the !imagecache preset to use in the browser. All thumbnails of local images appearing in the browser will be rendered using this setting. Note that if you override the default preset, and that preset\'s width and height don\'t match the settings above, you may experience inconsistencies in the browser if a node references an external image.', array('!imagecache' => l(t('Imagecache'), 'http://drupal.org/project/imagecache', array('attributes' => array('target' => '_blank'))))),
      '#options' => $options,
      '#default_value' => $default_preset,
    );
  }

  $form['global']['thumbnail_settings'][nrembrowser_variable_name('wysiwyg_default_icon')] = array(
    '#type' => 'textfield',
    '#title' => t('Path to default icon'),
    '#description' => t('Please enter the path to the default icon to be displayed in the browser or WYSIWYG if there is no image associated with a node.'),
    '#default_value' => nrembrowser_variable_get('wysiwyg_default_icon'),
  );

  // @TODO: Change image on path textfield change.
  $form['global']['thumbnail_settings']['wysiwyg_default_icon_preview'] = array(
    '#type' => 'item',
    '#value' => theme('image', nrembrowser_variable_get('wysiwyg_default_icon'), '', '', array('width' => nrembrowser_variable_get('thumbnail_width'), 'height' => nrembrowser_variable_get('thumbnail_height')), FALSE),
    '#prefix' => '<div id="nrembrowser-wysiwyg-default-icon-preview">',
    '#suffix' => '</div>',
  );

  $form['global']['wysiwyg_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('WYSIWYG settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  if (module_exists('styles')) {
    $styles = styles_default_styles('nodereference');
    $options = array();
    if (!empty($styles['styles'])) {
      foreach ($styles['styles'] as $style) {
        $options[$style['name']] = $style['label'];
      }
      $form['global']['wysiwyg_settings'][nrembrowser_variable_name('default_wysiwyg_style')] = array(
        '#type' => 'select',
        '#title' => t('Default WYSIWYG style'),
        '#options' => $options,
        '#default_value' => nrembrowser_variable_get('default_wysiwyg_style'),
      );
    }
  }

  $form['types'] = array(
    '#type' => 'fieldset',
    '#title' => t('Node type settings'),
    '#description' => t('Determine whether various node types will appear in the WYSIWYG browser, and where to select thumbnails for each type, regardless of whether for WYSIWYG or field browsers.'),

    // Add vertical tabs display if available.
    '#pre_render' => array('vertical_tabs_form_pre_render'),
    '#attributes' => array(
      'id' => 'nrembrowser-types',
    ),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $types = content_types();

  foreach (node_get_types('names') as $type => $name) {
    $form['types'][$type] = array(
      '#type' => 'fieldset',
      '#title' => check_plain($name),
      '#prefix' => '<div id="nrembrowser-type-'. $type .'" class="nrembrowser-type"></div>',
      // This is D7-style attached properties that will only work if vertical tabs is installed.
      '#attached' => array(
        'js' => array(
          'vertical-tabs' => drupal_get_path('module', 'nrembrowser') . '/includes/nrembrowser.vertical_tabs.js',
        ),
      ),
    );

    $form['types'][$type][nrembrowser_variable_name('wysiwyg_type_allowed_'. $type)] = array(
      '#type' => 'checkbox',
      '#title' => t('Allowed in WYSIWYG'),
      '#description' => t('When checking this box, if you have !WYSIWYG installed, you may then reference and display content of the %type type inline.', array('%type' => $name, '!WYSIWYG' => l(t('WYSIWYG'), 'http://drupal.org/project/wysiwyg', array('attributes' => array('target' => '_blank'))))),
      '#default_value' => nrembrowser_variable_get('wysiwyg_type_allowed_'. $type),
    );

    $options = array(
      'teaser' => t('Node teaser'),
      'full' => t('Full node'),
    );

    foreach ($types[$type]['fields'] as $field) {
      if (in_array($field['type'], array('text', 'filefield', 'link', 'emvideo', 'emimage', 'emaudio'))) {
        $options[$field['field_name']] = t('@label (%type)', array('@label' => $field['widget']['label'], '%type' => $field['type'] .' field'));
      }
    }

    $form['types'][$type][nrembrowser_variable_name('browser_image_'. $type)] = array(
      '#type' => 'radios',
      '#title' => t('Select browser thumbnail from'),
      '#description' => t('This selection will determine from where to select the dialog browser thumbnail from the content of the %type type. This will affect browsers in all fields and WYSIWYG editors.', array('%type' => $name)),
      '#options' => $options,
      '#default_value' => nrembrowser_variable_get('browser_image_'. $type),
      '#attributes' => array(
        'class' => 'nrembrowser-browser-image',
      ),
    );
  }

  drupal_add_js(drupal_get_path('module', 'nrembrowser') .'/includes/nrembrowser.admin.js');
  drupal_add_js(array('nrembrowser' => array('types' => node_get_types('names'))), 'setting');

  return system_settings_form($form);
}
