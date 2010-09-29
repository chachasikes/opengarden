<?php
// $Id: nrembrowser-iframe.tpl.php,v 1.1.2.2 2010/09/22 19:59:51 jerseycheese Exp $

/**
 * @file nrembrowser-iframe.tpl.php
 *
 * Theme function to display iframe for nrembrowser/node/add/%node-type.
 *
 * Available variables:
 * - $id: A unique number for this instance.
 * - $url: The URL of the source for the iframe.
 * - $width: The width attribute.
 * - $height: The height attribute.
 * - $no_iframe: The message to display when the browser doesn't support iframe.
 */

?>
<iframe id="nrembrowser-iframe-<?php print $id; ?>" class="nrembrowser-iframe" src ="<?php print $url; ?>" width="<?php print $width; ?>" height="<?php print $height; ?>" frameborder="no"><p><?php print $no_iframe; ?></p></iframe>