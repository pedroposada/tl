<?php 
/*
 *$form['membershipnumber'] = array(
		'#type' => 'select',
		'#title' => t('Membership Number'),
		'#options' => array(),
	);
	$form['passcode'] = array(
		'#type' => 'item',
		'#title' => t('Passcode'),
		'#value' => 'passcode',
	);
	$form['market'] = array(
		'#type' => 'item',
		'#title' => t('Market'),
		'#value' => 'market',
	);
	$form['balance'] = array(
		'#type' => 'item',
		'#title' => t('Balance'),
		'#value' => 'balance',
	); 
 */
?>
<div style="padding: 0 20px;">
	<table cellpadding="0" cellspacing="5" width="100%" border="0">
		<tr>
			<td><?php print drupal_render($form['memberships']) ?></td>
			<td><?php print drupal_render($form['passcode']) ?></td>
			<td><?php print drupal_render($form['market']) ?></td>
			<td><?php print drupal_render($form['balance']) ?></td>
		</tr>
	</table>
</div>

<?php print drupal_render($form) ?>