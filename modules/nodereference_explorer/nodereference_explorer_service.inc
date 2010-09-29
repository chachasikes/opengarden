<?php 

/**
 * get server domain name (for cookies)
 */
function nodereference_explorer_service_domain_name() {
	$domain = $_SERVER['SERVER_NAME'];
	return drupal_json($domain);
}

/**
 * Menu callback for retrieving all available taxonomy terms
 * TO-DO: return real json including rendering on client side
 * @return json string containing html drop-down code (injected)
 */
function nodereference_explorer_service_taxonomy() {
	  //get all taxonomy terms
	  $options = module_invoke('taxonomy', 'form_all');
	  
	  //add all terms option in first place
	  array_unshift($options, t('All'));
 	
	 //build drop-down widget
	 $element_taxonomy['selection_search']['taxonomy'] = array(
	 	//'#title' => 'Taxonomy filter',\
	 	'#id' => 'taxonomy_terms',
	 	'#type' => 'select',
	 	'#options' => $options,
	 );
	 //return html code as json string (to be inserted on client side)
	$output = theme_select($element_taxonomy['selection_search']['taxonomy']);
	return drupal_json($output);
}

/**
 * Menu callback for retrieving all nodes which can be related to
 * the specified term ids.
 * @return json string of node ids
 */
function nodereference_explorer_service_get_related_nodes_of_term() {
	
	//term id send by JavaScript widget
	$term_id = $_GET['tid'];
	if (!$term_id) $term_id = 3; //this should not happen
	
	//get all nodes which are related to this term
	$tax_result = taxonomy_select_nodes(array($term_id));
	
	//extract nodes ids (nids) and return it via json
	$nids = array();
	while (($node = db_fetch_object($tax_result)) != null) {
		array_push($nids, $node->nid);
	}
	return drupal_json($nids);
}

/**
 * Menu call back retrieving relevant nodes allowed for this field. 
 * @param $field_name
 *   name of the field instance
 * @return
 *   json string of nodes
 */
function nodereference_explorer_service_node_data($field_name) {
	//get all fields avaible
	$fields = content_fields();
	
	//get the specified field
	$field = $fields[$field_name];
	
	//get request parameters
	$page = $_POST['page'];
	$rp = $_POST['rp'];
	$sortname = $_POST['sortname'];
	$sortorder = $_POST['sortorder'];	
	$searchword = $_POST['query'];
	$searchfield = $_POST['qtype'];
	$mode = $_POST['mode'];
	
	//if not set, set default values
	if (!$page) $page = 1;
	if (!$rp) $rp = 5;
	if (!$sortname) $sortname = 'changed';
	if (!$sortorder) $sortorder = 'desc';
	if (!$mode) $mode = 'list';

	//compute start index
	$start = (($page-1) * $rp);	
	
	//get all allowed values (configured in administration)
	$nodes = nodereference_allowed_values($field);
	
	//$searchword = 'array: 17,10';
	//$searchfield = 'nid';
	
	//$searchword = 'e';
	//$searchfield = 'title';
	
	//count total number of all nodes
	$count = _nodereference_explorer_count_nodes(array_keys($nodes), $searchword, $searchfield);
	
	//get detailled information about nodes
	$result = _nodereference_explorer_get_nodes(array_keys($nodes), $start, $rp, $sortname, $sortorder, $searchword, $searchfield);
	
	//build a json string as data model to be rendered in flexigrid
	$json = _nodereference_explorer_build_node_data_json($result, $page, $count, $field['widget']['thumbnail_node_fields']);
	return $json;
}

/**
 * Build a json string for the flexigrid table widget from a mysql 
 * dbresult object. Returns a subset of the overall result set
 * @param $dbresult
 * 	 mysql database result object
 * @param $page
 * 	 number of page to be returend
 * @param $count
 *   total amout of items
 * @return 
 * 	 json string for flexigrid tables
 */
function _nodereference_explorer_build_node_data_json($dbresult, $page, $count, $node_field) {
	
	//create list object with page status and total amount of pages
	$node_list = new stdClass();
		$node_list->page = $page;
		$node_list->total = $count;

	//fill rows from db result
	$rows = new stdClass();	
	$rows = array();
	while (($node = db_fetch_object($dbresult)) != null) {
		$row = new stdClass();
		$row->id = $node->nid;
		
		//get type of referred field
		$type = $node->type;
		$fields = content_fields();
		$ref_field = $fields[$node_field];
		
		if ($ref_field['type'] == 'image') {
			
			$image_field =
				nodereference_explorer_thumbnail_field_value($node->nid, $node_field);
			
  			if ($image_field != null) {
  			$image_url = $image_field[0]['filepath'];
  			$thumbnail_url = nodereference_explorer_thumbnail_generate($image_url, "thumbnail");
			$type = '<img id="' . $node->nid . '" src="'.$thumbnail_url.'" alt="/'.$image_url.'"/>';
  			}
  			
			}
		
		$row->cell = array ($node->nid, 
							$type, 
							date("r", $node->changed), 
							$node->title, 
							$node->status);
		array_push($rows, $row);
	}
	$node_list->rows = $rows;
  	return drupal_json($node_list);
}

/**
 * Count the number of the total nodes set. *
 * @param $nids
 *   node ids
 * @param $searchword
 *   word searched for (value)
 * @param $searchfield
 *   name of db table field (key)
 * @return
 *   number of nodes
 */
function _nodereference_explorer_count_nodes($nids, $searchword, $searchfield) {
	$count_sql = 'count';
	$result = _nodereference_explorer_execute_query($count_sql, $nids, 0, count($nids), NULL, NULL, $searchword, $searchfield);
	$data = db_fetch_array($result);
	return $data['COUNT(*)'];

}

/**
 * Get detailled information about nodes.
 * @param $nids
 *   node ids
 * @param $from
 *   start index of result set
 * @param $count
 *   number of items per page
 * @param $sortname
 *   name of db table field to be sorted (key)
 * @param $sortorder
 *   order of sorting either asc or desc
 * @param $searchword
 *   word searched for (value)
 * @param $searchfield
 *   name of db table field (key)
 * @return
 *   db result of nodes
 */
function _nodereference_explorer_get_nodes($nids, $from, $count, $sortname, $sortorder, $searchword, $searchfield) { //, $search = array('key' => 'files.filepath', 'value' => '')) {
	return _nodereference_explorer_execute_query('query', $nids, $from, $count, $sortname, $sortorder, $searchword, $searchfield);
}

/**
 * Execute a db query to get detailled node information
 * @param $table_fields
 *   table field, e. g. '*', 'COUNT(*) or 'nid'
 * @param $nids
 *   nodes ids
 * @param $from
 *   start index of result set
 * @param $count
 *   number of items per page
 * @param $sortname
 *   name of db table field to be sorted (key)
 * @param $sortorder
 *   order of sorting either asc or desc
 * @param $searchword
 *   word searched for (value)
 * @param $searchfield
 *   name of db table field (key)
 * @return
 */
function _nodereference_explorer_execute_query($mode, $nids, $from, $count, $sortname, $sortorder, $searchword, $searchfield) { //, $search = array('key' => 'files.filepath', 'value' => '')) {
	
	$node_id = 'nid';
	
	//Build the query step by step
	//TO-DO: There must be a more efficient way to build queries, drupal db abstraction layer?
	if ($mode == 'query') { //query
		$query = 'SELECT * FROM {node} ';
	}
	else { // count
		$query = 'SELECT COUNT(*) FROM {node} ';
	}
	
	$args = array();
	//get all nodes by nids
	if (count($nids) > 0) {
		$query .= "WHERE $node_id IN (".db_placeholders($nids, 'int').") ";
		$args = $nids;
	}
	else { //otherwise return all items
		$query .= "WHERE 1=1 ";
	}
	
	if (isset($searchword) and isset($searchfield)) {
		$index = strpos($searchword, ':');
		if ($index == false) { //one searchword
			$words = array($searchword);
		}	
		else { //more searchwords
			$id_string = 'array:';
			$start = strpos($searchword, $id_string); //pos if delimiter
			$searchword_trimmed = substr($searchword, $start + strlen($id_string));
			$words = explode(",", $searchword_trimmed);
		}
		if ($searchfield != $node_id) {//like search
			for ($i = 0; $i < count($words); $i++) { //add wild cards
				$words[$i] = '%'.$words[$i].'%';
			}
				
			$query .= "AND %s LIKE ".db_placeholders($words, 'text')." ";
			$args = array_merge($args, array($searchfield), $words);
		}
		else { //exact search
			$query .= "AND %s IN (".db_placeholders($words, 'int').") ";
			$args = array_merge($args, array($searchfield), $words);
		}
	}
	
	//order results by field
	if (isset($sortname) and isset($sortorder)) {
		$query .= "ORDER BY %s %s";
	    $args = array_merge($args, array($sortname), array($sortorder));
	}
	//$query = db_rewrite_sql($query);
	return db_query_range($query, $args, $from, $count);
}
