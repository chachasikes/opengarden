// $Id: README.txt,v 1.1.2.2 2010/07/09 14:05:56 sreynen Exp $

Welcome to @font-your-face.

Installing @font-your-face:
---------------------------

- Place the entirety of this directory in sites/all/modules/fontyourface
- Navigate to administer >> build >> modules. Enable @font-your-face and one or more of the submodules (font providers) in the group.

Using @font-your-face:
----------------------

- Navigate to administer >> build >> themes >> @font-your-face.
- Click the "Add a new font" link.
- Click the name of a font.
- Enter a CSS selector for the content you want to use the font (or leave it as "body" to use it everywhere)
- Click "Add font"

WARNING:
--------

Internet Explorer has a limit of 32 CSS files, so using @font-your-face on CSS-heavy sites may require turning on CSS aggregation under administer >> site configuration >> performance.