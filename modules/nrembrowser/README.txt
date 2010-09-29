// $Id: README.txt,v 1.3 2010/06/17 20:38:55 aaron Exp $

Node Reference/Embed Media Browser (nrembrowser).

Provides a media thumbnail browser for editors to select nodes for fields and
inline inserts of embedded nodes.

This module works in conjunction with CCK's Nodereference, Views, and WYSIWYG,
creating a popup widget for editors that displays a browser of nodes installed
on the site, allowing for easy embeds.

Use cases:

* Creating a 'Photo' or 'Video' type node with a FileField or Embedded Media
  Field, then using nodereference to insert the referenced nodes as fields.
* Allowing an easy way to select related blog posts or articles to embed (with
  an inline image) within another post.
* Giving the ability of anonymous users to select from a library of images to
  insert inline to comments.

To use, you'll need to also have either Content + Nodereference (available from
http://drupal.org/project/cck), and/or WYSIWYG with a suitable editor
(available from http://drupal.org/project/wysiwyg) installed on your site. Note
that the module uses the same markup for WYSIWYG filters as does the Node Embed
module, so it's easy to migrate from that as well.

1) Download and Install the module per instructions at
http://drupal.org/getting-started/install-contrib/modules.

2) Install jQuery UI and jQuery Update from http://drupal.org/project/jquery_ui
and http://drupal.org/project/jquery_update respectively. Follow the
instructions contained in the jQuery UI module to install at least jQuery UI 1.7
package from http://code.google.com/p/jquery-ui/downloads/list?can=3&q=1.7
and jQuery Update needs to be at least version 6.x-2.0-alpha1.

2) Configure the global types you wish to expose to the browser from the Node
Reference/Embed Media Browser settings page (admin/settings/nrembrowser). You
will have the option later of limiting types and creating views for specific
fields and filters.

3) For specific Nodereference fields, you'll have the option to specify the
Media browser widget when setting them up. You can safely modify existing fields
in addition to setting up new fields; this only affects the editorial process,
not the actual storage of data. When setting up the field, you can limit the
node types that will appear in the browser -- all checked types will be
displayed, and in addition, tabs to filter by specific allowed types will
appear.

4) Likewise, you can create new browser configurations for use with WYSIWYG.
(@TODO: Add instructions once that has been integrated.)

5) You can specify certain views to be added as filters for the browser, to be
used both with fields and WYSIWYG. These will appear as tabs to the editor.
Additionally, these views will honor exposed filter settings, allowing the
editor to "drill down" through the node media on the site.
