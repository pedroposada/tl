<style>
	input#edit-keywords {
		font-size: 18px;
		width: 200px;
		float: left;
	}
</style>

<?php unset($form['keywords']['#title']) ?>
<?php print drupal_render($form['keywords']) ?>
<?php print drupal_render($form) ?>
<div style="clear: both;">&nbsp;</div>