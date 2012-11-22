<?php 
/**
 * Available variables
 * 
 * $menu_user			menu tree array for menu-bbm-login
 * $userlongname		'Logged in as ' . $_SESSION['userlongname'] 
 * $menu_tabs			menu tree array for menu-bbm-tabs
 * $menu_config_tabs	menu tree array for menu-bbm-tabs
 * $content				drupal_render($vars['form']) 
 */
?>

<div id="bbm-wrapper">

	<div class="bbm-login-menu">
		<?php print theme('links', $menu_user, array('class' => 'links', 'id' => 'navlist')); ?>
	</div>
	
	<div class="tabs">
		<?php print theme('links', $menu_tabs, array('class' => 'tabs primary')); ?>
	</div>
	
	<div class="tabs">
		<?php print theme('links', $menu_config_tabs, array('class' => 'tabs primary')); ?>
	</div>
	
	<div>
		<?php print $content ?>
	</div>
	
</div>