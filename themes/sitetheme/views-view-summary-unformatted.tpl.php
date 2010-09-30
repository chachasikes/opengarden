<?php
  if($view->name == 'glossary_title_slideshow') :
    // Create an array of the entire alphabet.
    $letters = range ('A', 'Z');
    foreach($rows as $id => $row){
      // Create an array of the existing letters, from the view output.
      $existing_letters[] = $row->title_truncated; 
    }
    // Loop through the alphabet, creating links that work with views active classes.
    $i = 0;
    foreach($letters as $letter) {
      $class = !empty($classes[$i]) ? ' class="'. $classes[$i] .' glossary-button"' : '"glossary-button"';
      // $style = 'height=' . ($view->result[$i]->count * 5) . 'px; width=20px'; 
      // $chart_style = 'style="width:20px; height:20px;background-color:white"';
      // $count = '<span class="tiny-count"' . $chart_style . '>' . $view->result[$i]->count . '</span>';
      $count = '';

      // If value exists, create a span with a link.
      if(in_array($letter, array_values($existing_letters))) {
        print '<span class="views-summary views-summary-unformatted">';
        print '<a href="' . $view->result[$i]->url . '" ' . $class . '>' . $view->result[$i]->link . '</a>' . $count;
        print '</span>';
        $i++;
      }
      else {
        print '<span class="views-summary views-summary-unformatted unlinked">';
        print '<a href="' . $view->display["page"]->display_options["path"] . '/' . strtolower($letter)  . '" ' . $class . '">' . $letter . '</a>' . $count;
        print '</span>';      
      }
    }
?>
<?php else :?>
  <?php foreach ($rows as $id => $row): ?>
    <?php print (!empty($options['inline']) ? '<span' : '<div') . ' class="views-summary views-summary-unformatted">'; ?>
      <?php if (!empty($row->separator)) { print $row->separator; } ?>
      <a href="<?php print $row->url; ?>"<?php print !empty($classes[$id]) ? ' class="'. $classes[$id] .'"' : ''; ?>><?php print $row->link; ?></a>
      <?php if (!empty($options['count'])): ?>
        (<?php print $row->count; ?>)
      <?php endif; ?>
    <?php print !empty($options['inline']) ? '</span>' : '</div>'; ?>
  <?php endforeach; ?>
<?php endif; ?>