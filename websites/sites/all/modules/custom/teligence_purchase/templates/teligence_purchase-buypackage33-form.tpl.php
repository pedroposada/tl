<!-- 3.3 Customer with web account (signed in) and active linked IVR memberships -->
<?php if(isset($form['location'])){?>
	
	<!--  STEP ONE	-->
	
	<h2>Select Membership</h2>
	<?php print drupal_render($form['memberships']); ?>
	
	<h2>Create Membership</h2>
	<div id="selectRegionMarketSr">
		<?php print drupal_render($form['location']['stateprovince']); ?>
		<?php print drupal_render($form['location']['city']); ?>
	</div>
	
	<h2>Packages</h2>
	<?php print drupal_render($form['packages']); ?>
	
	<h2>Select a payment method</h2>
	<?php print drupal_render($form['paymethods']['pp']); ?>
	
	<?php if($cclist = drupal_render($form['creditcardslist'])){ ?>
		<?php print drupal_render($form['paymethods']['cc']); ?>
		<?php print $cclist; ?>
	<?php }else{ unset($form['paymethods']['cc']); } ?>
	
	<?php print drupal_render($form['paymethods']['addcc']); ?>
	<!-- Please do not remove this wrapper -->
	<div id="ccFieldsWrapper">
		<?php print drupal_render($form['payment']); ?>
	</div>
	
	
<?php }else{ ?>
	
	<!--  STEP TWO	-->

	<?php print drupal_render($form['verifyorder33']) ?>
	<?php print drupal_render($form['packages']) ?>
	<?php print drupal_render($form['back']) ?>
	<?php print drupal_render($form['placeorder']) ?>

<?php } ?>

<?php print drupal_render($form); ?>