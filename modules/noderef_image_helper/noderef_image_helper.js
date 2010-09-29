// $Id: noderef_image_helper.js,v 1.1 2009/08/09 08:40:36 roetzi Exp $

Drupal.behaviors.noderef_image_helper = function(context) {
  $('.noderef_image_helper_field').not('.processed').each(function (i) {
    $(this).addClass('processed');
    $(this).parent().append(Drupal.theme('noderef_image_helper_buttons', $(this)));
    $(this).change(noderef_image_helper_onchange);
    noderef_image_helper_update(this);
  });
}

Drupal.theme.prototype.noderef_image_helper_buttons = function(el) {
  var upload_text = Drupal.t('Upload...');
  var browse_text = Drupal.t('Browse...');
  var id = el.attr('id');
  var html = '<div class="noderef_image_helper-buttons">';
  if (Drupal.settings.noderef_image_helper.can_upload) {
    html += '<input type="button" value="' + upload_text + '" onclick="noderef_image_helper_open_upload_popup(\'' + id + '\');"/>';
  }
  if (Drupal.settings.noderef_image_helper.can_browse) {
    html += '<input type="button" value="' + browse_text + '" onclick="noderef_image_helper_open_browse_popup(\'' + id + '\')"/>';
  }
  html += '</div>';
  return html;
}

function noderef_image_helper_open_upload_popup(id) {
  window.open(Drupal.settings.noderef_image_helper.upload_url + '/' + id, 'noderef_image_helper_popup', 'width=600,height=600,scrollbars=yes,status=yes,resizable=yes,toolbar=no,menubar=no');
}

function noderef_image_helper_open_browse_popup(id) {
  window.open(Drupal.settings.noderef_image_helper.browse_url + '/' + id, 'noderef_image_helper_popup', 'width=600,height=600,scrollbars=yes,status=yes,resizable=yes,toolbar=no,menubar=no');
}

function insert_image_reference(field_id, node_id) {
  $('#' + field_id).each(function () {
    this.value = '[nid: ' + node_id + ']';
    noderef_image_helper_update(this);
  });
}

function noderef_image_helper_onchange() {
  noderef_image_helper_update(this);
}

function noderef_image_helper_update(element) {
  
  var index = element.value.search(/\[nid:/i);
  if (index == -1) {
    $('#' + element.id + '-preview').html('');
  }
  else {
    var start = index + 5;
    var end = element.value.indexOf(']', start);
    var nid = element.value.substring(start, end);
    var cached = noderef_image_helper_cache(nid, null);
    if (cached != null) {
      $('#' + element.id + '-preview').html(cached);
    }
    else {
      $.get(Drupal.settings.noderef_image_helper.preview_url + '/' + nid, null, function(data) {
        noderef_image_helper_cache(nid, data);
        $('#' + element.id + '-preview').html(data);
      });
    }
  }
  
}

function noderef_image_helper_cache(nid, data) {
  if ( typeof noderef_image_helper_cache.cache == 'undefined' ) {
    noderef_image_helper_cache.cache = new Object();
  }
  if (data != null) {
    noderef_image_helper_cache.cache['nid' + nid] = data;
  }
  else {
    return noderef_image_helper_cache.cache['nid' + nid];
  }
}
