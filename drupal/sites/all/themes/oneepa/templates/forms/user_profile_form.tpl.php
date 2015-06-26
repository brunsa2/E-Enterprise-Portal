<link rel="stylesheet" href="//ajax.googleapis.com/ajax/libs/jqueryui/1.11.2/themes/smoothness/jquery-ui.css" />
<script src="//ajax.googleapis.com/ajax/libs/jqueryui/1.11.2/jquery-ui.min.js"></script>

<div class="edit-user-profile">
<div class="row">
	<div class="col-xs-12">
		<div class="panel panel-default">
		<div class="panel-body">
<h3>User Information</h3>
<?php
print render($form['field_profile_first_name']);
print render($form['field_profile_last_name']);
print render($form['account']['mail']);
?>
</div> <!--panel-body-->
</div> <!--panel-->
</div><!-- col-->
<div class="col-xs-12 col-md-12">
	<div class="panel panel-default">
		<div class="panel-body">
<h3>Locations of Interest</h3>
<p class="eenterprise-utility-form-item-description-p">
	Add your locations of interest to see environmental maps and 
	information relevant to those areas. Please indicate your default 
	location by clicking the key icon. <br />	
	<span class='zip_code_ajax_error'></span>
</p>
<div id='zipcode_description' class='form-group'>
<?php
	
print render($form['field_zip_code']);
?>
</div>

<!--<button id="add-field-zip-code" type="button" class="btn btn-success">+</button>-->
<!--<div class="add_more_holder">
	<button type="button" id="clear_all_zip_codes" class="btn btn-sm btn-danger">Clear All</button>
</div>-->
</div> <!--panel-body-->
</div> <!--panel-->
</div> <!-- col-->
</div>
<div class="col-xs-12 col-md-12">
	<div class="panel panel-default">
		<div class="panel-body">
<h3>Favorite Links</h3>
<p class="eenterprise-utility-form-item-description-p field-title-below">
		Add and manage your favorite links.</p>

<div id='links_description' class='form-group'>
<?php
print render($form['field_profile_favourites']);
?>
</div>

<!--<div class="add_more_holder">
<button type="button" id="clear_all_favorite_links" class="btn btn-sm btn-danger">Clear All</button>
</div>-->
</div> <!--panel-body-->
</div> <!--panel-->
</div><!-- col-->


<div class="col-xs-12">
	<div class="panel panel-default autocomplete-interests" style="display:none">
		<div class="panel-body">
<h3>Topics of Interest</h3>
<p class="eenterprise-utility-form-item-description-p field-title-below">
		What topics are you interested in?
		This information will help us suggest content that is most relevant to you.</p>
<div class="ui-widget">
  <input id="tags"  value="Start typing..." 
 onblur="this.value = 'Start typing...';"
 onfocus="if (this.value == 'Start typing...') {this.value = '';}" />
</div>
<?php
// print render($form['field_profile_interests']);
	print render($form['field_interests2']);	
?>

<?php
// Generate  parent vocab containers	
$vocabs = taxonomy_get_vocabularies();
$initialVocab = array('Environmental Media Topics', 'Health Topics', 'Pollution Prevention Topics', 'Regulatory and Industrial Topics');
foreach ($vocabs as $vid=>$value) {
	if (in_array($value->name, $initialVocab)) {
		$style = '';
	}
	else {
		$style = 'display:none';
	}
	print '<ul ><li style="' . $style . '" id="vocab_holder-' . $vid . '" class="vocab_holder"><h2><span class="label label-primary full-width">' . $value->name . '</span><span class="glyphicon glyphicon-chevron-up"></span></h2></li></ul>';
}	

?>


</div> <!--panel-body-->
</div> <!--panel-->
</div> <!-- col-->
<!--
<div class="col-xs-12">
<div class="panel panel-default">
	<div class="panel-body">
<?php
	// print render($form['field_interests2']);	
?>
	</div>
</div>
	</div>col-->


<div class="col-xs-12">

<?php
	print drupal_render_children($form);
?>

</div> <!--col-->
</div> <!-- row-->



</div> <!-- edit user-profile -->