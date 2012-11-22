<?php drupal_add_css(drupal_get_path('module', 'teligence_purchase') . '/teligence_purchase-styles.css'); ?>
<table>
	<tr>
		<td width="50%">
			<h1>
				Sign up
			</h1>
			<div>
				Text specific for the brand here
			</div>
			<div>
				<?php print drupal_render($form['email']) ?>
				<?php print drupal_render($form['password']) ?>
				<?php print drupal_render($form['confirm']) ?>
				<?php print drupal_render($form['gender']) ?>
				<?php print drupal_render($form['captcha']) ?>
				<div class="textAlignRight">
					<?php print drupal_render($form['signup']) ?>
				</div>
			</div>
		</td>
		<td>
			<div class="textAlignCenter">
				<div>
					Already a member?
				</div>
				<div>
					Text specific for the brand here
				</div>
				<div>
					<?php print l(t('Sign In'), 'purchase/sign-in') ?>
				</div>
			</div>
		</td>
	</tr>
</table>

<?php print drupal_render($form) ?>