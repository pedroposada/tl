<?php variable_get('teligence_purchase_debug',0) ? watchdog('debug','@print',array('@print'=>print_r($form,1))) : NULL ?>
<?php
	// drupal_set_message('<pre>'.check_plain(print_r($form['#value'],1)).'</pre>');
	// drupal_set_message('<pre>'.check_plain(print_r($form,1)).'</pre>');

	$output = '';
	$package = explode('|',$form['#value']['packages']);
	$city = $_SESSION['stateprovincecity']['city'][$form['#value']['stateprovince']][$form['#value']['city']];
	$stateprovince = ', '.$form['#value']['stateprovincename'];
	$promo = $form['#value']['ValidateResult']->PromoAmountCents;
	$tax = $form['#value']['ValidateResult']->TaxesAmountCents;
	$total = $form['#value']['ValidateResult']->TotalAmountCents;
		
	$rows = array();
	
	//verifyorder33
	if($form['#parents'][0] == 'verifyorder33')
	{
		if($form['#value']['memberships'] <> 'newmarket')
		{
			$city = $_SESSION['emsMemberships'][$form['#value']['memberships']]->MarketName;
			$memNum = $form['#value']['memberships'];
			$passcode = $_SESSION['emsMemberships'][$form['#value']['memberships']]->IvrPasscode;
			$stateprovince = '';
			$rows[] = array(array('data' => '<h2>'.t('Membership Information').'</h2>','colspan' => 2));
			$rows[] = array(array('data' => t('Minutes will be added to your membership number !num (Passcode !pass)',
						array('!num' => $memNum, '!pass' => $passcode)),'colspan' => 2));
		}
	}
	
	
	$rows[] = array(array('data' => '<h2>'.t('Package Information').'</h2>','colspan' => 2));
	$rows[] = array(t('City'),': '.trim($city).$stateprovince);
	$rows[] = array(t('Package Details'),': '.$package[1].t(' minutes'));
	$rows[] = array(t('Price'),': '.'$'.substr($package[2],0,-2).'.'.substr($package[2],-2));
	($promo ? $rows[] = array(t('Promo'),': '.'$'.substr($promo,0,-2).'.'.substr($promo,-2)) : NULL);
	($tax ? $rows[] = array(t('Tax'),': '.'$'.substr($tax,0,-2).'.'.substr($tax,-2)) : NULL);
	$rows[] = array(t('Total'),': '.'$'.substr($total,0,-2).'.'.substr($total,-2));
	
	if($form['#parents'][0] == 'verifyorder31')
	{
		$rows[] = array(array('data' => '<h2>'.t('Account Information').'</h2>','colspan' => 2));
		$rows[] = array(t('Email'),': '.$form['#value']['email']);
	}
	
	$rows[] = array(array('data' => '<h2>'.t('Payment Information').'</h2>','colspan' => 2));
	// verifyorder33
	if($form['#parents'][0] == 'verifyorder33' && $form['#value']['paymethods'] <> 'addcc')
	{
		$cc = explode('|',$form['#value']['creditcardslist']);
		$rows[] = array(t('Card Number'),': '.$cc[1]);
		$rows[] = array(t('Expiry Date'),': '.substr($cc[2],0,2).'/'.substr($cc[2],-2));
	}
	else 
	{
		$rows[] = array(t('Card Number'),': '.substr_replace($form['#value']['cardnumber'], '**** **** **** **** ', 0, -4));
		$rows[] = array(t('Security Code'),': '.substr_replace($form['#value']['securitycode'], '**', 0, -1));
		$rows[] = array(t('Expiry Date'),': '.$form['#value']['cc_expiration']['month'].'/'.$form['#value']['cc_expiration']['year']);
	}
	
	$output = theme('table',array(),$rows,array('id'=>$form['#id'].'Table'));
	print $output;
?>