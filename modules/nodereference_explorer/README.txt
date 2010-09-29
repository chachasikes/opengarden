Nodereference Explorer README
---------------------------------------

Current Version
---------------
6.x-0.1

Author
-------
Gottfried Nindl

Company
--------
OSCE (Organisation for Security and Cooperation in Europe)

Release Notes
-------------
While the nodereference module is great about creating internal references of your content's
website its inbuilt widgets (autocomplete, select list or option boxes) for user input aren't 
very comfortable. The purpose of the nodereference explorer module is to provide more user-friendly
input, exploration and search possibilites. It is therefore supplied as an additional widget 
built on-top of the nodereference autocomplete widgets. The autocomplete widget is enhanced 
by an explorer-like selection dialog, where nodes can be picked by simple mouse clicks. Further
keyword searches as well a taxonomy driven search supports the user to find easily the demanded content.
For images it offers a thumbnail generation possibility and a simple preview.

Most features concern the usability of the widget input which are:

- Autocomplete keyword search
- Taxonomy/category-driven search
- Modal selection dialog (resizable & draggable)
- Full-featured selection table with column sorting/toggling/hiding/resizing, 
  result paging, thumbnail and lightbox preview
- Thumbnail and thickbox enabled view of images
- Teaser (content only) themes stripping of header information for front end
- Multiple selection and ordering support
- View support
- ...

This module is developed in scope of the OSCE 3.0 website relaunch.

Quick start Guide
-----------------
1) Enable the nodererence explorer module and dependent modules (see info files for dependencies).
2) You should now be able to select the "Explorer" widget when attaching a nodereference field to 
   a content type.
3) Sepecial configuration of the widget:
	a) Referencing node field name for thumbnail generation: This is the name of the field
	   where a reference is created. This is supposed to be an imagefield field where a thumbnail
	   can be generated. Leave it blank if you don't need to use it.
	b) Thumbnail preset: Create a preset (module: imagecache) for your 
	   thumbnails and choose it from the select box. 
	c) Display fields: The preset 'Teaser (content only)' strips of header information
   Finally save the settings.
4) Now go to the edit page of your content type instance via 'Create Content' or 
   'Content Management->Content'. You should now see one or more enhanced autocomplete
   input fields. Choose your content via the dialog box you open with 'Browse...' and delete the
   reference with 'Clear'. NOTE: You have a keyword search as well as a taxonomy 
   search (select box) in your dialog. They just work seperately now, i. e. no 
   combined search (TO-DO for release version).
5) Finally view your image. You can play around with the teaser of your nodereference explorer field
   and referenced node and display the content as wished.


TO-DOs:
-----------------
- Integration of imagefield for file upload
- Overcome dialog theme problem in Internet Explorer, i. e. dragging
  and resizing of dialog is pretty weird
- Add configuration options for widget, e. g. theme of jquery widgets, 
  layout of table and dialog etc.
- Thumbnail view of table
- Combined key word and taxonomy search
