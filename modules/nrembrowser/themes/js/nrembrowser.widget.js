// $Id: nrembrowser.widget.js,v 1.11.2.26 2010/09/22 20:12:36 jerseycheese Exp $

/**
 * @file
 * JavaScript for the Node Reference/Embed Media Browser (nrembrowser) widget.
 */

// Add this to the jQuery namespace.
(function ($) {

  // Define the nrembrowser object.
  Drupal.nrembrowser = Drupal.nrembrowser || {};

  // Our 'global' variable for the dialog jQuery object.
  Drupal.nrembrowser.$dialog = null;

  /**
   * Display the Drupal throbber.
   *
   * @param $element
   *  The jQuery element to append the throbber to.
   * @param boolean throbber
   *  If TRUE, then display the throbber element.
   */
  Drupal.nrembrowser.throbber = function($element, throbber) {
    if (throbber) {
      $element.after('<div class="ahah-progress ahah-progress-throbber"><div class="throbber">&nbsp;</div></div>');
    }
    else {
      $element.siblings('.ahah-progress').remove();
    }
  }

  /**
   * Helper function to build the browser.
   *
   * @param $link
   *  The jQuery object for the field link we're launching from.
   * @param _current
   *  The currently selected media node. In a form that may be parsed by
   *  nodereference autocomplete, such as 'Title [nid:XY]' or '[nid:NN]'.
   */
  Drupal.nrembrowser.dialog = function($link, _current) {
    var element =  $link.data('element');
    var fieldName = $link.data('fieldName');
    // Create our media browser dialog.
    Drupal.nrembrowser.$dialog = $('<div id="nrembrowser-dialog"></div>')
      .dialog({
        autoopen: false,
        modal: true,
        width: 642,
        height: 'auto',
        title: 'Add media'
      })
      // Remove the dialog entirely from the DOM after closing.
      .bind( "dialogclose", function(event, ui) {
        $(this).remove();
      })
      // Store the passed parameters.
      .data('link', $link)
      .data('current', _current)
      // Store the referenced element to the dialog jquery data.
      .data('element', element)
      .data('fieldName', fieldName)
      .data('insertElement', $link.data('insertElement'))
      // Store the HTML of the original thumbnail.
      .data('currentThumbnail', $link.parent().siblings('.nrembrowser-thumbnail').html());
    // Grab the remote output for the browser.
    Drupal.nrembrowser.throbber(Drupal.nrembrowser.$dialog, true);
    $.ajax({
      type: 'POST',
      dataType: 'json',
      url: Drupal.settings.nrembrowser.mediaBrowserUrl,
      data: { js: true, current: _current, field_name: fieldName },
      success: function(data, textStatus, XMLHttpRequest) {
        Drupal.nrembrowser.throbber(Drupal.nrembrowser.$dialog, false);
        if (data.status) {
          // Open the browser.
          Drupal.nrembrowser.$dialog.html(data.data).dialog('open');
          // Attach any required behaviors to the browser.
          Drupal.attachBehaviors(Drupal.nrembrowser.$dialog);
        }
        else {
          // Failure...
          alert(Drupal.t('Unknown error in Drupal.nrembrowser.dialog.'));
        }
      },
      error: function(XMLHttpRequest, textStatus, errorThrown) {
        // Failure...
        Drupal.nrembrowser.throbber(Drupal.nrembrowser.$dialog, false);
        alert(Drupal.t('Error in Drupal.nrembrowser.dialog: @error', { '@error': textStatus }));
      }
    });
  }

  Drupal.nrembrowser.insert = function(nidWrapper) {
    // Also the newly selected thumbnail, if it was changed.
    var _thumbnail = Drupal.nrembrowser.$dialog.data('currentThumbnail');

    // We need the field element to change. The 'title' has [nid:123].
    var _value = $(_thumbnail).attr('title');

    // Change the value and thumbnail of the associated field, and ensure we
    // run the correct behaviors again.
    var $field = $(Drupal.nrembrowser.$dialog.data('element'));
    $field.val(_value).removeClass('nrembrowserReplaceTextfields-processed');
    $('#' + $field.attr('id') + '-wrapper-nrembrowser-thumbnail').html(_thumbnail).show()
    .children('a').removeClass('nrembrowserReplaceTextfields-processed');

    // Run the behaviors on the new thumbnail.
    Drupal.attachBehaviors($field.parent().parent());
  }

  /**
   * Replace the textfields with links to the browser.
   */
  Drupal.behaviors.nrembrowserReplaceTextfields = function(context) {
    for (var id in Drupal.settings.nrembrowser) {
      var textfield = '#' + id + '-nid-nid';
      var wrapper = textfield + '-wrapper';

      // Hide the autocomplete textfield.
      $(textfield, context).not('.nrembrowserReplaceTextfields-processed').addClass('nrembrowserReplaceTextfields-processed').hide();

      // Add a link to launch the browser.
      $(wrapper, context).not('.nrembrowserReplaceTextfields-processed').addClass('nrembrowserReplaceTextfields-processed').append(Drupal.settings.nrembrowser[id].launchLink);

      // Launch the browser when clicking the new link.
      $(wrapper + ' .nrembrowser-launch-link', context).not('.nrembrowserReplaceTextfields-processed').addClass('nrembrowserReplaceTextfields-processed').each(function() {
        $(this).attr('id', id + '-nid-nid-nrembrowser-link').bind('click', function() {
          // Launch the browser: @params $link, _current ('title [nid:NID]').
          Drupal.nrembrowser.dialog($(this), $(this).siblings('input').val());
          // Halt further processing.
          return false;
        })
        // Add the field we're adding media to.
        .data('element', textfield)
        .data('insertElement', Drupal.nrembrowser)
        .data('fieldName', Drupal.settings.nrembrowser[id].fieldName);
      });

      if (!$(wrapper + '-nrembrowser-thumbnail').html()) {
        $(wrapper + '-nrembrowser-thumbnail').hide();
      }

      // Link the thumbnail to that same link.
      $(wrapper + '-nrembrowser-thumbnail img:not(.nrembrowserReplaceTextfields-processed)').addClass('nrembrowserReplaceTextfields-processed').each(function() {
        // We have a thumbnail, so hide the launch link.
        $launchLink = $(wrapper + ' .nrembrowser-launch-link').hide();

        // Store the launch link to data for later reference.
        $(this).data('launchLink', $launchLink);

        // When we click the thumbnail, launch the browser.
        $(this).bind('click', function() {
          // Trigger the browser link.
          $(this).data('launchLink').click();
          // Halt further processing.
          return false;
        });
      });
    }
  }

  /**
   * Replace images with [[nid:123]] tags in content upon detaching editor.
   */
  Drupal.nrembrowser.markup = function(image) {
    var $content = $('<div>' + image + '</div>');
    $.each($('img.nrembrowser-thumbnail-image', $content), function (i, elem) {
      $(elem).replaceWith($(elem).attr('alt'));
    });
    return $content.html();
  }

  /**
   * Clicking the OK on the dialog will either insert the node into the field,
   * or replace the form with the Styles dialog when enable for WYSIWYG.
   */
  Drupal.nrembrowser.dialogOK = function() {
    nidWrapper = Drupal.nrembrowser.markup(Drupal.nrembrowser.$dialog.data('currentThumbnail'));

    // Somehow nidWrapper is coming to us initially as 'null'.
    if ((nidWrapper === undefined) || (nidWrapper === null) || (nidWrapper === 'null')) {
      nidWrapper = false;
    }

    // If this is for WYISYWG & we have the Styles module enabled, then we need
    // to determine the Style to display the content.
    if (nidWrapper && Drupal.nrembrowser.$dialog.data('fieldName') == 'wysiwyg' && Drupal.settings.nrembrowser.getStyleURL) {
      // Load up the Styles select form.
      $.ajax({
        beforeSend: function(XMLHttpRequest) {
          // Add a throbber to the OK button.
          Drupal.nrembrowser.throbber($('#nrembrowser-add-media-page-form .form-submit'), true);
        },
        url: Drupal.settings.nrembrowser.getStyleURL,
        cache: false,
        data: 'nid=' + nidWrapper,
        dataType: 'json',
        error: function(XMLHttpRequest, textStatus, errorThrown) {
          Drupal.nrembrowser.throbber($('#nrembrowser-add-media-page-form .form-submit'), false);
          alert(Drupal.t('Error in Drupal.nrembrowser.dialogOK: @error', { '@error': textStatus }));
        },
        success: function(data, textStatus, XMLHttpRequest) {
          // Remove the throbber.
          Drupal.nrembrowser.throbber($('#nrembrowser-add-media-page-form .form-submit'), false);

          // If we have received the Styles form, then display it.
          if (data.status) {
            // Replace the form with the new Styles select form.
            Drupal.nrembrowser.$dialog.html(data.data);

            // Attach any required behaviors to the browser.
            Drupal.attachBehaviors(Drupal.nrembrowser.$dialog);

            // Set the default style value.
            var _value = $('#nrembrowser-style-formatter-selector-form select').val();
            if ((_value != undefined) && (_value != '0')) {
              Drupal.nrembrowser.$dialog.data('styleName', _value);
            }
          }
          else {
            alert(Drupal.t('Unknown error in Drupal.nrembrowser.dialogOK.'));
          }
        },
        type: 'GET'
      });
      return false;
    }
    else if (nidWrapper) {
      // Simply insert our node into the field or WYSIWYG browser.
      Drupal.nrembrowser.$dialog.data('insertElement').insert(nidWrapper);

      // Close the dialog.
      Drupal.nrembrowser.$dialog.dialog('close');
      Drupal.nrembrowser.$dialog.remove();
    }
  }

  // Behaviors added to the basic media browser dialog form elements.
  Drupal.behaviors.nrembrowserPassSelection = function(context) {
      $('#nrembrowser-tabs ul#nrembrowser-tabs-list', context).parent().not('.nrembrowserPassSelection-processed')
        .addClass('nrembrowserPassSelection-processed')
        .tabs({
          load: function(event, ui) {
            // Attach any required behaviors to the browser.
            Drupal.attachBehaviors(ui.panel);
          },
          ajaxOptions: {
            beforeSend: function (XMLHttpRequest) {
              Drupal.nrembrowser.throbber($('#nrembrowser-tabs-list .ui-state-processing a'), true);
            },
            error: function(XMLHttpRequest, textStatus, errorThrown) {
              Drupal.nrembrowser.throbber($('#nrembrowser-tabs-list .ui-corner-top a'), false);
              alert(Drupal.t('Error in Drupal.nrembrowser.nrembrowserPassSelection (tabs list): @error', { '@error': textStatus }));
            },
            success: function(data) {
              Drupal.nrembrowser.throbber($('#nrembrowser-tabs-list .ui-corner-top a'), false);
            }
          }
        });

    // Bind AJAX to pager links.
    $('#nrembrowser-add .pager a:not(.nrembrowserPassSelection-processed)', context)
      .addClass('nrembrowserPassSelection-processed')
      .bind('click', function(e) {
          var serialized = $(this).serialize();
          serialized += '&js=1';
          var $this = $(this);
          Drupal.nrembrowser.throbber($(this), true);
          $.ajax({
            url: $(this).attr('href'),
            cache: false,
            data: serialized,
            dataType: 'json',
            error: function(XMLHttpRequest, textStatus, errorThrown) {
              Drupal.nrembrowser.throbber($('#nrembrowser-tabs .pager-item a'), false);
              alert(Drupal.t('Error in Drupal.nrembrowser.nrembrowserPassSelection (binding pager links): @error', { '@error': textStatus }));
            },
            success: function(data, textStatus, XMLHttpRequest) {
              Drupal.nrembrowser.throbber($('#nrembrowser-tabs .pager-item a'), false);
              if (data.status) {
                $this.parents('#nrembrowser-tab-wrapper').parent().html(data.data);
                // Attach any required behaviors to the browser.
                Drupal.attachBehaviors(Drupal.nrembrowser.$dialog);
              }
              else {
                alert(Drupal.t('Unknown error in Drupal.nrembrowser.nrembrowserPassSelection (binding pager links).'));
              }
            },
            type: 'GET'
          });
          return false;
      });

    $('#nrembrowser-exposed-widgets form:not(.nrembrowserPassSelection-processed)', context)
      .addClass('nrembrowserPassSelection-processed')
      .bind('submit', function(e) {
        var serialized = $(this).serialize();
        serialized += '&js=1';
        var $this = $(this);
        $.ajax({
          beforeSend: function(XMLHttpRequest) {
            Drupal.nrembrowser.throbber($('#nrembrowser-exposed-widgets form .views-exposed-widgets .form-submit'), true);
          },
          url: $(this).attr('action'),
          cache: false,
          data: serialized,
          dataType: 'json',
          error: function(XMLHttpRequest, textStatus, errorThrown) {
            Drupal.nrembrowser.throbber($('#nrembrowser-exposed-widgets form .views-exposed-widgets .form-submit'), false);
            alert(Drupal.t('Error in Drupal.nrembrowser.nrembrowserPassSelection (exposed widgets): @error', { '@error': textStatus }));
          },
          success: function(data, textStatus, XMLHttpRequest) {
            Drupal.nrembrowser.throbber($('#nrembrowser-exposed-widgets form .views-exposed-widgets .form-submit'), false);
            if (data.status) {
              $this.parents('#nrembrowser-tab-wrapper').parent().html(data.data);
              // Attach any required behaviors to the browser.
              Drupal.attachBehaviors(Drupal.nrembrowser.$dialog);
            }
            else {
              alert(Drupal.t('Unknown error in Drupal.nrembrowser.nrembrowserPassSelection (exposed widgets).'));
            }
          },
          type: 'GET'
        });
        return false;
      });

    // After hitting OK, we need to change the value of the field.
    $('#nrembrowser-add-media-page-form:not(.nrembrowserPassSelection-processed)', context)
      .addClass('nrembrowserPassSelection-processed')
      .bind('submit', function() {
        Drupal.nrembrowser.dialogOK();

        // Halt further processing.
        return false;
      });

    // Pass the selected node thumbnail data into the field or WYSIWYG.
    $('#nrembrowser-style-formatter-selector-form:not(.nrembrowserPassSelection-processed)', context)
      .addClass('nrembrowserPassSelection-processed')
      .bind('submit', function() {
        nidWrapper = Drupal.nrembrowser.markup(Drupal.nrembrowser.$dialog.data('currentThumbnail'));
        _value = Drupal.nrembrowser.$dialog.data('styleName');
        if ((_value != undefined) && (_value != '0')) {
          nidWrapper = nidWrapper.replace(']]', ';styleName:' + Drupal.nrembrowser.$dialog.data('styleName') + ']]');
        }

        Drupal.nrembrowser.$dialog.data('insertElement').insert(nidWrapper);

        // Close the dialog.
        Drupal.nrembrowser.$dialog.dialog('close');
        Drupal.nrembrowser.$dialog.remove();

        // Halt further processing.
        return false;
      });

    // Bind clicking the thumbnail to selecting the corresponding radio.
    $('#nrembrowser-add .nrembrowser-thumbnail:not(.nrembrowserPassSelection-processed)', context).addClass('nrembrowserPassSelection-processed').each(function() {
      $(this).bind('click', function() {
        // Select the associated radio when clicking the thumbnail.
        $(this).closest('div.form-item').find('input').attr('checked', 1).trigger('change').focus();

        // Draw a rectangle around the selected thumbnail.
        $('#nrembrowser-add .nrembrowser-thumbnail').removeClass('selected');
        $(this).addClass('selected');

        // Halt further processing.
        return false;
      }).bind('dblclick', function() {
        // Double-clicking a thumbnail submits the form.
        $('#nrembrowser-add-media-page-form').submit();
      }).bind('keypress', function(event) {
        // Pressing enter after selecting a thumbnail submits the form.
        if (event.which == 13) {
          $('#nrembrowser-add-media-page-form').submit();
          // Halt further processing.
          return false;
        }
      });
    });

    // Change the selected thumbnail after making a new radio selection.
    $('#nrembrowser-add-media-page-form input[name=media]', context).not('.nrembrowserPassSelection-processed').addClass('nrembrowserPassSelection-processed').each(function() {
      $(this).bind('change', function() {
        // Store the associated thumbnail to the dialog's data.
        Drupal.nrembrowser.$dialog.data('currentThumbnail', $(this).closest('div.form-item').find('.nrembrowser-thumbnail').html());
      })
        // Hide the radio after binding the change function.
        .hide();
    });
  }

  // Load the style formatter selector into the frame for WYSIWYG.
  Drupal.nrembrowser.changeStyleFormatterSelector = function() {
    var _data = 'nid=' + $('#nrembrowser-style-formatter-selector-form #edit-nid').val();
    var _value = $('#nrembrowser-style-formatter-selector-form select').val();
    Drupal.nrembrowser.$dialog.data('styleName', _value);
    if ((_value != undefined) && (_value != '0')) {
      _data += '&styleName=' + _value;
    }
    $.ajax({
      beforeSend: function(XMLHttpRequest) {
        Drupal.nrembrowser.throbber($('#edit-style'), true);
      },
      url: Drupal.settings.nrembrowser.getStylePreviewURL,
      cache: false,
      data: _data,
      dataType: 'json',
      error: function(XMLHttpRequest, textStatus, errorThrown) {
        Drupal.nrembrowser.throbber($('#edit-style'), false);
        alert(Drupal.t('Error in Drupal.nrembrowser.changeStyleFormatterSelector: @error', { '@error': textStatus }));
      },
      success: function(data, textStatus, XMLHttpRequest) {
        Drupal.nrembrowser.throbber($('#edit-style'), false);
        if (data.status) {
          $('#nrembrowser-style-formatter-selector-preview-wrapper').html(data.data);
          // Attach any required behaviors.
          Drupal.attachBehaviors($('#nrembrowser-style-formatter-selector-preview-wrapper'));
        }
        else {
          alert(Drupal.t('Unknown error in Drupal.nrembrowser.changeStyleFormatterSelector.'));
        }
      },
      type: 'GET'
    });
  }

  Drupal.behaviors.nrembrowserStyleFormatterSelector = function(context) {
    $('#nrembrowser-style-formatter-selector-form select:not(.nrembrowserStyleFormatterSelector-processed)')
      .addClass('nrembrowserStyleFormatterSelector-processed')
      .each(function() {
        $(this).bind('change', function(e) {
          Drupal.nrembrowser.changeStyleFormatterSelector();
        });
      });
    $('#nrembrowser-style-formatter-selector-form a:not(.nrembrowserStyleFormatterSelector-processed)')
      .addClass('nrembrowserStyleFormatterSelector-processed')
      .each(function() {
        $(this).bind('click', function(e) {
          // Ensure that clicking a link in a preview teaser doesn't send us away.
          return false;
        });
      })
  }

})(jQuery);
