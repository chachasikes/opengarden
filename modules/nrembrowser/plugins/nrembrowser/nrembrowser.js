// $Id: nrembrowser.js,v 1.1.2.13 2010/08/15 15:28:29 aaron Exp $
(function ($) {

// @todo Array syntax required; 'break' is a predefined token in JavaScript.
Drupal.wysiwyg.plugins['nrembrowser'] = {

  /**
   * Return whether the passed node belongs to this plugin.
   */
  isNode: function(node) {
    return ($(node).is('img.wysiwyg-nrembrowser'));
  },

  /**
   * Execute the button.
   *
   * This is called when we first launch the dialog browser.
   */
  invoke: function(data, settings, instanceId) {
    if (data.format == 'html') {
      $('#' + instanceId).data('element', $(this)).data('fieldName', 'wysiwyg').data('insertElement', Drupal.wysiwyg.instances[instanceId]);
      // Launch the browser.
      Drupal.nrembrowser.dialog($('#' + instanceId), '');
    }
  },

  /**
   * Replace all [[nid:123]] tags with images.
   *
   * This is called when the WYSIWYG is first enabled, and after a selction
   * is made and passed to the textarea.
   */
  attach: function(content, settings, instanceId) {
    return content.replace(/\[\[nid:(\d+);?(.*?)\]\]/gi, function(match, nid, style) { return Drupal.wysiwyg.plugins.nrembrowser._getPlaceholder(settings, nid, style); });
  },

  /**
   * Replace images with [[nid:123]] tags in content upon detaching editor.
   */
  detach: function(content, settings, instanceId) {
    return Drupal.wysiwyg.plugins.nrembrowser._markup(content, settings);
  },

  /**
   * Replace images with [[nid:123; width: 300px; height: 580px]] tags in
   * content upon detaching editor.
   */
  _markup: function(content, settings) {
    var $content = $('<div>' + content + '</div>');
    $.each($('img.nrembrowser-thumbnail-image', $content), function (i, elem) {
      var _style = $(elem).attr('style');
      var _rel = $(elem).attr('rel');

      // Grab the styleName from the rel tag so it's preserved later.
      if (_rel) {
        _style += '; styleName:' + _rel;
      }
      if (_style) {
        $(elem).replaceWith($(elem).attr('alt').replace(']]', '; ' + _style + ']]'));
      }
      else {
        $(elem).replaceWith($(elem).attr('alt'));
      }
    });
    return $content.html();
  },

  _placeholderCount: 0,

  /**
   * Helper function to return a HTML placeholder.
   */
  _getPlaceholder: function (settings, nid, style) {
    if (nid) {
      // Grab source of thumbnail from nrembrowser.
      var appendToURL = '';
      if (settings.global.imagecachePreset) {
        appendToURL = '/' + settings.global.imagecachePreset;
      }

      var _rel = '';
      var _attributes = new Array();

      if (style) {
        var _styles = style.split(';');
        for (var _style in _styles) {
          var _attribute = _styles[_style].split(':');
          for (var i in _attribute) {
            _attribute[i] = $.trim(_attribute[i]);
          }
          if (_attribute[0] && _attribute[1]) {
            _attributes[_attribute[0]] = _attribute[1];
          }
        }
      }

      if (_attributes.styleName != undefined) {
        _rel = _attributes.styleName;
        delete _attributes.styleName;
        appendToURL = appendToURL + '?styleName=' + _rel;
      }

      // We preserve the styleName in the rel tag.
      _rel = _rel ? 'rel=' + _rel : '';

      var _src = settings.global.thumbnailURL + '/' + nid + appendToURL;

      return '<img src="' + _src + '" style="'+ style +'" '+ _rel +' class="nrembrowser-thumbnail-image drupal-content" alt="[[nid:' + nid + ']]" title="[[nid:' + nid + ']]" />'
    }
  }
};

})(jQuery);
