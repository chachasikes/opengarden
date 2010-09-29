// $Id: nrembrowser.admin.js,v 1.1.2.1 2010/07/21 18:09:06 aaron Exp $

/**
 * @file nrembrowser.admin.js
 *
 * Behaviors to add to the admin pages of the nrembrowser module.
 */

// Add this to the jQuery namespace.
(function ($) {
  // Change the preview image when the default icon or w/h is changed.
  Drupal.behaviors.nrembrowserAdminThumbnail = function(context) {
    $('#edit-nrembrowser--wysiwyg-default-icon:not(nrembrowserAdminThumbnail-processed), #edit-nrembrowser--thumbnail-width:not(nrembrowserAdminThumbnail-processed), #edit-nrembrowser--thumbnail-height:not(nrembrowserAdminThumbnail-processed)')
      .addClass('nrembrowserAdminThumbnail-processed')
      .bind('change', function() {
        var _src = $('#edit-nrembrowser--wysiwyg-default-icon').val();
        if (_src.indexOf('://') == -1) {
          // If this is not an external image, then append the base path.
          _src = Drupal.settings.basePath + _src;
        }

        // Change the image appropriately
        $('#nrembrowser-wysiwyg-default-icon-preview img')
          .attr('src', _src)
          .attr('width', $('#edit-nrembrowser--thumbnail-width').val())
          .attr('height', $('#edit-nrembrowser--thumbnail-height').val());
      });
  }

})(jQuery);
