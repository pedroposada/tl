<!-- 3.2 Customer with web account (signed in) but no active linked membership -->

<?php if(isset($form['location'])){?>
	
	<!--  STEP ONE	-->
	
	<h2>Create Membership</h2>
	<table>
		<tr>
			<td><?php print drupal_render($form['location']['stateprovince']); ?></td>
			<td><?php print drupal_render($form['location']['city']); ?></td>
		</tr>
	</table>
	
	<h2>Packages</h2>
	<?php print drupal_render($form['packages']); ?>
	
	<h2>Payment Info</h2>
	<?php print drupal_render($form['payment']['paymethods']); ?>
	<div id="ccFieldsWrapperAsu">
		<?php print drupal_render($form['payment']['cardholdername']); ?>
		<?php print drupal_render($form['payment']['cardnumber']); ?>
		<?php print drupal_render($form['payment']['securitycode']); ?>
		<?php print drupal_render($form['payment']['zippostal']); ?>
		<?php print drupal_render($form['payment']['cc_expiration']); ?>
	</div>


<?php }else{ ?>
	
	<!--  STEP TWO	-->

	<?php print drupal_render($form['verifyorder32']) ?>
	<?php print drupal_render($form['packages']) ?>
	<?php print drupal_render($form['back']) ?>
	<?php print drupal_render($form['placeorder']) ?>

<?php } ?>


<?php print drupal_render($form); ?>