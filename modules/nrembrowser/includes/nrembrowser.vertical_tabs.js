// $Id: nrembrowser.vertical_tabs.js,v 1.1.2.1 2010/07/01 20:16:01 aaron Exp $

/**
 * @file
 * Vertical tabs support for /admin/settings/nrembrowser.
 */

// Add this to the jQuery namespace.
(function ($) {
  // The following line will prevent a JavaScript error if this file is included and vertical tabs are disabled.
  Drupal.verticalTabs = Drupal.verticalTabs || {};

  Drupal.behaviors.nrembrowserReport = function(context) {
    for (var type in Drupal.settings.nrembrowser.types) {
      // Note the name here matches the name of the fieldset ID.
      Drupal.verticalTabs[type] = function() {
        if (this.callback) {
          $element = $('.vertical-tabs-' + this.callback).data('type', this.callback);
        }
        else {
          $element = $(this).parents('fieldset.vertical-tabs-pane');
        }
        var raw_type = $element.data('type');
        var type = raw_type.replace('_', '-');
        var allowed;
        if ($('#edit-nrembrowser--wysiwyg-type-allowed-' + type + '-wrapper input').attr('checked')) {
          allowed = 'Allowed in WYSIWYG';
        }
        else {
          allowed = 'Not allowed in WYSIWYG';
        }
        return allowed + '<br />Thumbnail from ' + $('.vertical-tabs-' + raw_type + ' .nrembrowser-browser-image input:checked').parent().text();
      }
    }
  };

})(jQuery);
