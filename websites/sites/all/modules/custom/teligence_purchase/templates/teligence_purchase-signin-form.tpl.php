<?php
/**
 * $form['email'] = array(
		'#type' => 'textfield',
		'#title' => t('Email'),
		'#required' => true,
		'#pre_render' => array('teligence_purchase_email_prerender'),
		'#element_validate' => array('teligence_purchase_validate_email'),
	);
	$form['password'] = array(
		'#type' => 'password',
		'#title' => t('Password'),
		'#required' => true,
		'#pre_render' => array('teligence_purchase_password_prerender'),
		'#element_validate' => array('teligence_purchase_validate_password'),
	);
	$form['keep'] = array(
		'#type' => 'checkbox',
		'#title' => t('Keep me logged in on this computer'),
	);
	
	$form['signin'] = array(
		'#type' => 'submit',
		'#value' => t('Sign in'),
		'#pre_render' => array('teligence_purchase_button_prerender'),
	);
 */
?>
<?php drupal_add_css(drupal_get_path('module', 'teligence_purchase') . '/teligence_purchase-styles.css'); ?>
<table>
	<tr>
		<td width="50%">
			<h1>
				Sign in
			</h1>
			<div>
				Text specific for the brand here
			</div>
			<div>
				<?php print drupal_render($form['email']) ?>
				<?php print drupal_render($form['password']) ?>
				<?php print drupal_render($form['keep']) ?>
				<div>
					<?php print l(t('Forgot Password'), 'cart/forgot-password') ?>
				</div>
				<div>
					<?php print l(t('Forgot Email'), 'cart/forgot-email') ?>
				</div>
				<div class="textAlignRight">
					<?php print drupal_render($form['signin']) ?>
				</div>
			</div>
		</td>
		<td>
			<div class="textAlignCenter">
				<div>
					Not Registered Yet?
				</div>
				<div>
					Text specific for the brand here
				</div>
				<div>
					<?php print l(t('Sign Up'), 'purchase/sign-up') ?>
				</div>
			</div>
		</td>
	</tr>
</table>

<?php print drupal_render($form) ?>