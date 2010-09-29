// $Id: noderef_image_helper.insert.js,v 1.1 2009/08/09 08:40:36 roetzi Exp $

Drupal.behaviors.noderef_image_helper_insert = function(context) {
  var url = window.location.href.split('/');
  var field_id = url[url.length-2];
  var node_id = url[url.length-1];
  
  window.opener.insert_image_reference(field_id, node_id);
  close();
}
