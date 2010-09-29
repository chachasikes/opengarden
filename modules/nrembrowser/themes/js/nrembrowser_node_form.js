// $Id: nrembrowser_node_form.js,v 1.1.2.5 2010/08/24 20:01:42 aaron Exp $

/**
 * @file
 * JavaScript for the Node Reference/Embed Media Browser (nrembrowser) node
 * form alter.
 */

// Add this to the jQuery namespace.
(function ($) {

  // Define the nrembrowser object.
  Drupal.nrembrowser = Drupal.nrembrowser || {};

  // Our 'global' variable for the parent page's dialog jQuery object.
  Drupal.nrembrowser.$editDialog = this.parent.jQuery('#nrembrowser-dialog');
  Drupal.nrembrowser.editMarkup = this.parent.Drupal.nrembrowser.markup;
  Drupal.nrembrowser.editDialogOK = this.parent.Drupal.nrembrowser.dialogOK;

  Drupal.behaviors.nrembrowserViewNodeJsWrapper = function(context) {
    $('#nrembrowser-view-node-js-wrapper:not(.nrembrowserViewNodeJsWrapper-processed)', context)
      .addClass('nrembrowserViewNodeJsWrapper-processed')
      .each(function() {
        var thumbnail = $('.nrembrowser-thumbnail', $(this)).html();

        // Insert the new node to the dialog browser.
        Drupal.nrembrowser.$editDialog.data('currentThumbnail', thumbnail);
        Drupal.nrembrowser.editDialogOK();
    });

    // FF3 won't display vertical tabs unless you open the 'Add' fieldset.
    $('.vertical-tabs:not(.nrembrowserViewNodeJsWrapper-processed)', context)
      .addClass('nrembrowserViewNodeJsWrapper-processed')
      .each(function() {
        // Using .show() doesn't work for some reason.
        $(this).css('display', 'block');
      });
  }

})(jQuery);
