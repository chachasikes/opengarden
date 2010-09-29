$MODE = 'list';

$(document).ready(function() {
	initFlexigrid();
	
	$('#edit-field-list-0-nid-nid').keydown(function (event) {
		//alert("Change Listener: "+$(this).val());
		if(event.keyCode==13) {
			startProgress();
			$('.flex1').search($(this).val(), 'title');
			setTimeout("stopProgress()", 500);
			$('#taxonomy_terms').val("0");
			//$("select option:selected").val(0);
		}
	});
	loadTaxonomyList();
	preloadSelectedImage();
	
});

function preloadSelectedImage() {
	
	$.getJSON("/nodereference_explorer/service_domain_name", function(domain) {
	
		//alert(domain);
	$.aqCookie.domain = domain; //'drupal-dev-local.osce.org';
	//alert("After cookie");
	 var node = $.aqCookie.get(['nodereferenece_explorer_id', 
	                              'nodereferenece_explorer_title', 
	                              'nodereferenece_explorer_date',
	                              'nodereference_explorer_image_thumbnail',
	                              'nodereference_explorer_image_full']);
	//alert(node);
	$id = node['nodereferenece_explorer_id'];
    $title = node['nodereferenece_explorer_title'];
    $thumbnail = node['nodereference_explorer_image_thumbnail'];
    $full_image = node['nodereference_explorer_image_full'];
    $date = node['nodereferenece_explorer_date'];
   //  alert($date);
   // alert($thumbnail+","+$full_image);
     if ($thumbnail != null)			
    	 $('#selectedImage').attr('src', node['nodereference_explorer_image_thumbnail']);	  	
    
     if ($full_image != null)	{		
    	 $('#selectedImage').parent().attr('href', node['nodereference_explorer_image_full']);	  	
    	 $('#selectedImage').parent().attr("style", "display:true");
     }
     //$('#url-value').text($date);
   // alert($id +","+$title);
	$('#id-value').text($id);
	$('#name-value').text($title);
	$('#url-value').text($date);
	}
	);
}
	
function loadTaxonomyList() {
	$.getJSON( '/nodereference_explorer/service_taxonomy', //'/photopicker/taxonomy', //'http://drupal-dev-local.osce.org/photopicker/taxonomy', 
				function(json){
					$node = $('#taxonomy_terms');
					$node.replaceWith(json);
					//$node.attr("id", "taxonomy_terms");
					$('#taxonomy_terms').change(function (event) {
						if ($("select option:selected").val() == 0) {
							//alert('All');
							$('.flex1').search('', '');
						}
						else {
						$.getJSON( '/nodereference_explorer/service_get_related_nodes_of_term',
								{ tid: $("select option:selected").val()}, function(json2) {
									//alert(json2[0]);
									//alert('array: '+json2);
							$('.flex1').search('array: '+json2, "nid");
							//reset search field
							$('#edit-field-list-0-nid-nid').val('');
						});
						}
					});
				} );
	
}

function startProgress() {
	$('#edit-field-list-0-nid-nid').attr("class", "form-text form-autocomplete text throbbing");
}

function stopProgress() {
	$('#edit-field-list-0-nid-nid').attr("class", "form-text form-autocomplete text");
}

function initFlexigrid() {
	
	$.getJSON("/nodereference_explorer/service_domain_name", function(domain) {
	
	$.aqCookie.domain = domain; //$('#server-info').text(); //'drupal-dev-local.osce.org';
	 var field = $.aqCookie.get(['nodereference_explorer_service_url']);
	   
	$url = field['nodereference_explorer_service_url'];
//	alert($field_name);
	
	$('.flex1').flexigrid({
		url: $url, //"/nodereference_explorer/service_node_data/field_links", 
		dataType: "json",
		colModel: [
	{display: 'ID', name : 'nid', width : 25, sortable : true, align: 'center'},
	{display: 'Type', name : 'type', width : 90, sortable : true, align: 'center'},
	{display: 'Date', name : 'changed', width : 150, sortable : true, align: 'center'},
	{display: 'Title', name : 'title', width : 200, sortable : true, align: 'center'},
	{display: 'Status', name : 'status', width : 35, sortable : true, align: 'center'}
	],
	//buttons : [
	//{name: 'Thumbnails', bclass: 'thumbnails', onpress : showThumbs},
	//{name: 'List', bclass: 'list', onpress : showTable}],
searchitems : [
	{display: 'ID', name : 'nid'},
	{display: 'Title', name : 'title', isdefault: true}
	],
	title: 'Image Gallery',
	sortname: "changed",
	sortorder: "desc",
	useRp: true,
	rp: 5,
	rpOptions: [5,10,25,50],
	showTableToggleBtn: true,
	usepager: true,
	width: 600,
	height: 200,
	nowrap: false,
	colResize: true,
	singleSelect: true
});
	setListListener();
	});
}



function showTable() {
	$MODE = 'list';
	$('.hDiv').show();
	$('.flex1').flexOptions({
		rp: 5,
		rpOptions: [5,10,25,50],
		params: 
			[{name: "mode", value: $MODE}]
	});
	
	//Hack for Thumbnail view - TODO implement in flexigrid.js
	$("th>div", ".hDiv").attr("style", "text-align: center; width: 100px;");
	$("th:first>div", ".hDiv").attr("style", "text-align: center; width: 40px;");
	$("th:eq(1)>div", ".hDiv").attr("style", "text-align: left; width: 80px;");
	$("th:eq(2)>div", ".hDiv").attr("style", "text-align: left; width: 180px;");
	$("th:eq(3)>div", ".hDiv").attr("style", "text-align: left; width: 230px;");
	$("th:last>div", ".hDiv").attr("style", "text-align: right; width: 80px;");
	
	$(".flex1").flexReload(); 
}

function showThumbs() {
	$MODE = 'thumbs';
	$('.hDiv').hide();
	$('.flex1').flexOptions({
		rp: 25,
		rpOptions: [25,50,100,250],
		params: 
			[{name: "mode", value: $MODE}]
		});
	
	$(".flex1").flexReload(); 
	
	
	//Hack for Thumbnail view - TODO implement in flexigrid.js
	//$("th>div", ".hDiv").text("Image");
	$("th", ".hDiv").attr("align", "center");
	$("th>div", ".hDiv").attr("style", "text-align: center; width: 100px;");
	
	$("th>div>img", ".hDiv").click(function() {alert('hllo;')});
}

function setListListener() {
	
	$(".flex1").css("cursor", "pointer");
	$(".flex1").unbind("click");
	$(".flex1").click(function(e) {
		if ($MODE == 'list') {
			
			var id = $(".trSelected").attr('id');
			
			var table_headers = $(".hDivBox > table > thead > tr > th"); //.parent("axis").text();
			$title_index = parseInt($($(table_headers)).index($(".hDivBox > table > thead > tr > th[abbr = 'title']")))+1;
			$date_index = parseInt($($(table_headers)).index($(".hDivBox > table > thead > tr > th[abbr = 'changed']")))+1;
			$type_index = parseInt($($(table_headers)).index($(".hDivBox > table > thead > tr > th[abbr = 'type']")))+1;
			
			$title = $(".trSelected > *:nth-child("+$title_index+") > *:first-child").html();
			$date = $(".trSelected > *:nth-child("+$date_index+") > *:first-child").html();
			$src = $(".trSelected > *:nth-child("+$type_index+") > *:first-child > *:first-child").attr("src");
			$alt = $(".trSelected > *:nth-child("+$type_index+") > *:first-child > *:first-child").attr("alt");
			
			$id = id.substr(3);
			showSelectedItem($id, $title, $date, $src, $alt);
		}
		else {  //TO-DO: Not Working
			$id = $(this).children(0).children(".trSelected").children(1).children(0).children(0).attr("id");
			$src =$(this).children(0).children(".trSelected").children(2).children(0).children(0).attr("src");
			$alt =$(this).children(0).children(".trSelected").children(2).children(0).children(0).attr("alt");
			alert("Id: "+$id +" Src: "+$src +" Coord.: "+e.x +", "+e.y);
			showSelectedItem($src, $alt);
		}
	});
}

function showSelectedItem($id, $title, $date, $src, $alt) {
	//Set link to image
	//$('#selectedImage').attr("src", $src);
	$('#url-value').text($date);
	$('#id-value').text($id);
	$('#name-value').text($title);
	
	$.getJSON("/nodereference_explorer/service_domain_name", function(domain) {
	
	$.aqCookie.domain = domain; //$('#server-info').text(); //'drupal-dev-local.osce.org';
	$.aqCookie.set('nodereferenece_explorer_id',$id);
	$.aqCookie.set('nodereferenece_explorer_title',$title);
	$.aqCookie.set('nodereferenece_explorer_date',$date);
		
	
	 if ($src != undefined) {
		 $.aqCookie.set('nodereferenece_explorer_image_thumbnail',$src);
		 $('#selectedImage').attr("src", $src);
	 }
	 else {
		 //alert($src);
		 $.aqCookie.set('nodereferenece_explorer_image_thumbnail', undefined);
		 $('#selectedImage').attr("src", '');
		 $('#selectedImage').parent().attr("style", "display:none");
	 }
     if ($alt != undefined)	{	
    	 $.aqCookie.set('nodereferenece_explorer_image_full', $alt);
    	 $('#selectedImage').parent().attr("href", $alt);
    	 $('#selectedImage').parent().attr("style", "display:true");
     }
     else {
    	 $.aqCookie.set('nodereferenece_explorer_image_full', undefined);
    	 $('#selectedImage').parent().attr("href", '');
    	 $('#selectedImage').parent().attr("style", "display:none");
     }
	});
}
			