<?php

/*******************************************************
 * 3.1 Customers with no web account (not signed in)
 */
function teligence_purchase_buypackage31_form($form_state)
{
	if($form_state['storage']['step'] == 'verifyorder')
	{
		drupal_set_title(t('Review Purchase'));
		$form['verifyorder31'] = array(
			'#theme'=> 'teligence_purchase_verifyorder',
			'#value' => $form_state['storage']['values'],
		);
		$form['packages'] = array(
			'#type' => 'hidden',
			'#default_value' => $form_state['storage']['values']['packages'],
		);
		$form['back'] = array(
			'#type' => 'submit',
			'#value' => t('Go Back'),
			'#pre_render' => array('teligence_purchase_button_prerender'),
		);
		$form['placeorder'] = array(
			'#type' => 'submit',
			'#value' => t('Place Order'),
			'#pre_render' => array('teligence_purchase_button_prerender'),
		);
		return $form;
	}
	
	$form['#pre_render'] = array('teligence_purchase_buypackage_form_prerender');
	$form['#after_build'] = array('teligence_purchase_buypackage_form_afterbuild');
	
	// debug logging	
	if(variable_get('teligence_purchase_debug', 0))
		watchdog('debug',"SESSION['localization']: @loc",array('@loc'=>print_r($_SESSION['localization'],TRUE)));
	
	// get markets
	// find default region and market; localization
	$region = key((array)$_SESSION['stateprovincecity']['city']);
	if(key_exists(strtoupper(filter_var($_SESSION['localization']->Region,FILTER_SANITIZE_URL)), $_SESSION['stateprovincecity']['city']))
		$region = $_SESSION['localization']->Region;
	$sanitizedRegion = strtoupper(filter_var($region,FILTER_SANITIZE_URL));
	$form['location']['stateprovince'] = array(
		'#type' => 'select',
		'#title' => t('State/Province'),
		'#default_value' => isset($form_state['storage']['values']['stateprovince'])?$form_state['storage']['values']['stateprovince']:$sanitizedRegion,
		'#options' => (array)$_SESSION['stateprovincecity']['stateprovince'],
	);
	$marketId = key((array)$_SESSION['stateprovincecity']['city'][$sanitizedRegion]);
	if(key_exists($_SESSION['localization']->MarketId, (array)$_SESSION['stateprovincecity']['city'][$sanitizedRegion]))
		$marketId = $_SESSION['localization']->MarketId;
	$form['location']['city'] = array(
		'#type' => 'select',
		'#title' => t('City'),
		'#default_value' => isset($form_state['storage']['values']['city'])?$form_state['storage']['values']['city']:$marketId,
	);
	
	// get packages
	$form['packages'] = array(
		'#type' => 'radios',
		'#theme' => 'teligence_purchase_packagesradios',
		'#default_value' => $form_state['storage']['values']['packages'],
	);
	
	// account information
	$form['account']['email'] = array(
		'#type' => 'textfield',
		'#title' => t('Email'),
		'#pre_render' => array('teligence_purchase_email_prerender'),
		'#default_value' => $form_state['storage']['values']['email'],
	);
	$form['account']['password'] = array(
		'#type' => 'password',
		'#title' => t('Password'),
		'#pre_render' => array('teligence_purchase_password_prerender'),
		'#description' => t('Password must be at least 6 characters long.'),
		'#default_value' => $form_state['storage']['values']['password'],
	);
	$form['account']['confirm'] = array(
		'#type' => 'password',
		'#title' => t('Confirm Password'),
		'#pre_render' => array('teligence_purchase_password_prerender'),
		'#description' => t('Password must be at least 6 characters long.'),
		'#default_value' => $form_state['storage']['values']['confirm'],
	);
	
	// payment information
	$form['payment']['paymethods'] = array(
		'#type' => 'radios',
		'#options' => array('pp'=>'PayPal', 'cc'=>t('Credit Card')),
		'#default_value' => $form_state['storage']['values']['paymethods'],
	);
	$form['payment']['cardholdername'] = array(
		'#type' => 'textfield',
		'#title' => t("Cardholder's Name"),
		'#default_value' => $form_state['storage']['values']['cardholdername'],
	);
	$form['payment']['cardnumber'] = array(
		'#type' => 'textfield',
		'#title' => t('Card Number'),
		'#default_value' => $form_state['storage']['values']['cardnumber'],
		'#pre_render' => array('teligence_purchase_ccn_prerender'),
	);
	$form['payment']['securitycode'] = array(
		'#type' => 'textfield',
		'#title' => t('Security Code'),
		'#default_value' => $form_state['storage']['values']['securitycode'],
		'#pre_render' => array('teligence_purchase_cvv_prerender'),
	);
	$form['payment']['zippostal'] = array(
		'#type' => 'textfield',
		'#title' => t('Billing ').($_SESSION['localization']->Country == 'Canada' ? t('Postal Code') : t('Zip Code')),
		'#default_value' => $form_state['storage']['values']['zippostal'],
	);
	$form['payment']['cc_expiration'] = array (
    	'#type'=>'date',
    	'#title'=>t('Expiration Date'),
    	'#theme' => 'teligence_purchase_ccexpirationdate',
    	'#description'=>t('Enter expiration date on card'),
    	'#default_value' => $form_state['storage']['values']['cc_expiration'],
    );
	
	$form['submitpurchase'] = array(
		'#type' => 'submit',
		'#value' => t('Complete My Purchase'),
		'#pre_render' => array('teligence_purchase_button_prerender'),
	);
	
	return $form;
}
function teligence_purchase_buypackage31_form_validate($form, &$form_state)
{
	if($form_state['clicked_button']['#id'] == 'edit-submitpurchase')
	{
		// packages
		if(!isset($form_state['values']['packages']) || empty($form_state['values']['packages']))
		{
			form_error($form['packages'], t('Please select a package.'));
		}
		
		// email
		$form_state['values']['email'] = trim($form_state['values']['email']);
		if(!valid_email_address($form_state['values']['email']))
		{
			form_error($form['account']['email'], t('Invalid email address.'));
		}
		
		// confirm passwords
		if(($form_state['values']['password'] <> $form_state['values']['confirm']) || empty($form_state['values']['confirm']))
		{
			form_error($form['account']['password'], t('Passwords do not match.'));
			form_error($form['account']['confirm'], t('Passwords do not match.'));
			array_pop($_SESSION['messages']['error']);
		}
		
		// paymethods
		if(empty($form_state['values']['paymethods']))
		{
			form_error($form['payment']['paymethods'], t("Please select one payment method."));
		}
		
		// credit card validation
		if($form_state['values']['paymethods'] == 'cc')
		{
			// cardholder name
			$form_state['values']['cardholdername'] = trim($form_state['values']['cardholdername']);
			if(empty($form_state['values']['cardholdername']))
			{
				form_error($form['payment']['cardholdername'], t("Cardholder's Name is required."));
			}
			
			// card number
			$form_state['values']['cardnumber'] = trim($form_state['values']['cardnumber']);
			if(!teligence_cart_valid_card_number($form_state['values']['cardnumber']))
			{
				form_error($form['payment']['cardnumber'], t('Invalid Credit Card Number.'));
			}
			
			// security code
			$form_state['values']['securitycode'] = trim($form_state['values']['securitycode']);
			if(!ctype_digit($form_state['values']['securitycode']) || strlen($form_state['values']['securitycode']) < 3)
			{
				form_error($form['payment']['securitycode'], t('Invalid Security Code.'));
			}
			
			// zip/postal
			$form_state['values']['zippostal'] = trim($form_state['values']['zippostal']);
			if(!teligence_purchase_validate_zippostal($form_state['values']['zippostal']))
			{
				form_error($form['payment']['zippostal'],t('Invalid Zip/Postal Code.'));
			}
			
			// expiration date
			teligence_purchase_validate_expirationdate($form['payment']['cc_expiration'], $form_state);
		}
		
		// make form persistent
		$form_state['storage']['values'] = $form_state['values'];
		$flat = teligence_purchase_array_flatten($form['location']['stateprovince']['#options'], FALSE);
		$form_state['storage']['values']['stateprovincename'] = $flat[$form_state['values']['stateprovince']];
	}
	
	// drupal_set_message('<pre>'.check_plain(print_r($form['location']['city']['#options'],1)).'</pre>');
}
function teligence_purchase_buypackage31_form_submit($form, &$form_state)
{
	// after filling up the form go to confirmation
	if($form_state['clicked_button']['#id'] == 'edit-submitpurchase')
	{
		// parse package elements; id, price, minutes
		$package = explode('|',$form_state['values']['packages']);
		
		// credit card
		if($form_state['storage']['values']['paymethods'] == 'cc')
		{
			// ValidateAsuNotSignedIn
			$params = new stdClass ();
		    $params->ivrBrandId = variable_get('teligence_purchase_brandid', 1);
			$params->email = $form_state['values']['email'];
			$params->password = $form_state['values']['password'];
			$params->marketId = $form_state['values']['city'];
			$params->packageId = $package[0];
			$params->creditCardNumber = $form_state['values']['cardnumber'];
			$params->expiryDateMmYy = str_pad($form_state['values']['cc_expiration']['month'].$form_state['values']['cc_expiration']['year'],4,"0",STR_PAD_LEFT);
			$params->cardholderName = $form_state['values']['cardholdername'];
			$params->zip = $form_state['values']['zippostal'];
			$result = teligence_purchase_soap_call($params, 'ValidateAsuNotSignedIn', variable_get('teligence_purchase_wsdl_ordermanagement',''),TRUE);
			switch ($result->ValidateAsuNotSignedInResult->ResponseCode) 
			{
				case 'Success':
					$form_state['storage']['values']['ValidateResult'] = $result->ValidateAsuNotSignedInResult;
					$form_state['storage']['step'] = 'verifyorder';
					break;
				case 'ExistingMembershipBrandHub': 
					// signin as ivr_user, send validation email and redirect to 3.3				
					
					// send validation email
					$tokens = teligence_purchase_tokens('emailValidateAccount');
					$tokens['[email]'] = $form_state['storage']['values']['email'];
					$tokens['[password]'] = $form_state['storage']['values']['password'];
					$tokens['[url]'] = url('cart/validate-web-account/' . 
						$result->ValidateAsuNotSignedInResult->ValidationCode . '/' . 
						$form_state['storage']['values']['email'] . '/' . 
						$form_state['storage']['values']['password'], array('absolute' => TRUE)
					);
					drupal_mail('teligence_purchase', 'emailValidateAccount', $form_state['storage']['values']['email'], language_default(), $tokens);
					drupal_set_message(t('We have sent you an email with a validation link. Please click it to validate your account.'));
					
					// load user
					global $user;
					
					// update drupal user
					$form_state['WebActiveMemberships'] = $result->ValidateAsuNotSignedInResult->WebActiveMemberships;
					$user = teligence_purchase_drupaluser($form_state);
					
					// save values in the session
					$sessionValues = $result->ValidateAsuNotSignedInResult;
					teligence_purchase_setsessionvalues($sessionValues);
					
					// message to user
					drupal_set_message(t('We found you in our system. You can select from the packages below.'));
					
					// redirect to success page
					drupal_goto('cart/add-time');
					break;
				case 'InactivePaymethod':
				case 'EmailLinkedToWebAccount':
				case 'CreditCardBelongsToOtherMember':
				case 'CreditCardLinkedToWebAccount':
					drupal_set_message(t('We found you in our system already. Please !sign', array('!sign' => l(t('click here to sign-in'),'cart/login'))),'error');
					break;
				case 'NegativeCreditStatus':
				case 'NoSalesPaymentRestriction':
				case 'DebtOrPaymentRestriction':
				case 'OlderExpirationDate':
				case 'DuplicateRequestGuid':
				case 'FraudulentPaymethod':
					drupal_set_message(t('!callcs', array('!callcs' => variable_get('teligence_purchase_customerservice',''))),'error');
					break;
				case 'InvalidRequestParams':
				case 'TechnicalError':
				default:
					drupal_set_message(t('!error',array('!error'=>$result->ValidateAsuNotSignedInResult->ErrMsg)),'error');
					break;
			}
		}

		// paypal
		if($form_state['storage']['values']['paymethods'] == 'pp')
		{
			// send request to paypal.teligence.net
			module_load_include('inc', 'teligence_purchase', 'teligence_purchase-paypal');
			$urlquery = array(
				// 'areaCode' => '', // from previous implementation
				// 'Ani' => '', // from previous implementation
				'SequenceId' => teligence_cart_uuid(TRUE),
				'Password' => $form_state['storage']['values']['password'],
				'Email' => $form_state['storage']['values']['email'],
				'PackageId' => $package[0],
				'VendorPass' => md5(variable_get('teligence_cart_paypal_vendor_pass_asu', '')),
				'lang' => $GLOBALS['language']->language,
				'IvrBrandId' => variable_get('teligence_purchase_brandid', 1),
			);
			if(!teligence_purchase_paypalSetSessionData($urlquery, variable_get('teligence_cart_paypal_vendor_id_asu', '')))
			{
				// could not connect to paypal.teligence.net
				drupal_set_message(t('!callcs', array('!callcs' => variable_get('teligence_purchase_customerservice',''))),'error');
			}
		}
	}
	
	// place order
	if($form_state['clicked_button']['#id'] == 'edit-placeorder')
	{
		// drupal_set_message('<pre>'.check_plain(print_r($form_state['storage']['values'],1)).'</pre>');
		// credit card
		if($form_state['storage']['values']['paymethods'] == 'cc')
		{
			// ProcessPayment
			$params = new stdClass ();
			$params->orderId = $form_state['storage']['values']['ValidateResult']->OrderId;
			$params->paymethodId = $form_state['storage']['values']['ValidateResult']->PaymethodId;
			$params->cvn = $form_state['storage']['values']['securitycode'];
			$params->email = $form_state['storage']['values']['email'];
			$params->password = $form_state['storage']['values']['password'];
			$result = teligence_purchase_soap_call($params, 'ProcessPayment', variable_get('teligence_purchase_wsdl_ordermanagement',''));
			switch ($result->ProcessPaymentResult->ResponseCode) 
			{
				case 'Success':
					// send validation email
					$tokens = teligence_purchase_tokens('emailValidateAccount');
					$tokens['[email]'] = $form_state['storage']['values']['email'];
					$tokens['[password]'] = $form_state['storage']['values']['password'];
					$tokens['[url]'] = url('cart/validate-web-account/' . 
						$result->ProcessPaymentResult->ValidationCode . '/' . 
						$form_state['storage']['values']['email'] . '/' . 
						$form_state['storage']['values']['password'], array('absolute' => TRUE)
					);
					drupal_mail('teligence_purchase', 'emailValidateAccount', $form_state['storage']['values']['email'], language_default(), $tokens);
					drupal_set_message(t('We have sent you an email with a validation link. Please click it to validate your account.'));
					
					// drupal_set_message('<pre>'.check_plain(print_r($result->ProcessPaymentResult->WebActiveMemberships,1)).'</pre>');
					// redirect to success page
					$querystring = array(
						'City' => trim(str_replace("2", "",$result->ProcessPaymentResult->WebActiveMemberships->MarketName)),
						'Email' => $form_state['storage']['values']['email'],
						'TotalAmountCents' => $form_state['storage']['values']['ValidateResult']->TotalAmountCents,
						'PackageMinutes' => $form_state['storage']['values']['ValidateResult']->PackageMinutes,
						'IvrMembershipNumber' => $result->ProcessPaymentResult->IvrMembershipNumber,
						'IvrPasscode' => $result->ProcessPaymentResult->IvrPasscode,
						'LocalAccessNumber' => $result->ProcessPaymentResult->LocalAccessNumber,
					);
					drupal_goto('cart/result/creditcardasu',$querystring);
					break;
				case 'AuthorizationDeclined':
				case 'RiskScoreReject':
				case 'RiskScoreReview':
				case 'AuthorizationTechnicalIssue':
				case 'RtmFailure':
					drupal_set_message(t('!callcs', array('!callcs' => variable_get('teligence_purchase_customerservice',''))),'error');
					break;
				case 'InvalidRequestParams':
				case 'TechnicalError':
				default:
					drupal_set_message(t('!error',array('!error'=>$result->ProcessPaymentResult->ErrMsg)),'error');
					break;
			}
					
		}
	}
	
	// go back to modify a value
	if($form_state['clicked_button']['#id'] == 'edit-back')
	{
		unset($form_state['storage']['step']);
		$form_state['storage']['values']['packages'] = $form_state['values']['packages'];
		
	}
}



/***************************************************************
 * 3.2 Customer with web account (signed in) but no active linked membership
 */
function teligence_purchase_buypackage32_form($form_state)
{
	if($form_state['storage']['step'] == 'verifyorder')
	{
		drupal_set_title(t('Review Purchase'));
		$form['verifyorder32'] = array(
			'#theme'=> 'teligence_purchase_verifyorder',
			'#value' => $form_state['storage']['values'],
		);
		$form['packages'] = array(
			'#type' => 'hidden',
			'#default_value' => $form_state['storage']['values']['packages'],
		);
		$form['back'] = array(
			'#type' => 'submit',
			'#value' => t('Go Back'),
			'#pre_render' => array('teligence_purchase_button_prerender'),
		);
		$form['placeorder'] = array(
			'#type' => 'submit',
			'#value' => t('Place Order'),
			'#pre_render' => array('teligence_purchase_button_prerender'),
		);
		return $form;
	}
	
	$form['#pre_render'] = array('teligence_purchase_buypackage_form_prerender');
	$form['#after_build'] = array('teligence_purchase_buypackage_form_afterbuild');
	
	// get markets
	// find default region and market; localization
	$region = key((array)$_SESSION['stateprovincecity']['city']);
	if(key_exists(strtoupper(filter_var($_SESSION['localization']->Region,FILTER_SANITIZE_URL)), $_SESSION['stateprovincecity']['city']))
		$region = $_SESSION['localization']->Region;
	$sanitizedRegion = strtoupper(filter_var($region,FILTER_SANITIZE_URL));
	$form['location']['stateprovince'] = array(
		'#type' => 'select',
		'#title' => t('State/Province'),
		'#default_value' => isset($form_state['storage']['values']['stateprovince'])?$form_state['storage']['values']['stateprovince']:$sanitizedRegion,
		'#options' => (array)$_SESSION['stateprovincecity']['stateprovince'],
	);
	$marketId = key((array)$_SESSION['stateprovincecity']['city'][$sanitizedRegion]);
	if(key_exists($_SESSION['localization']->MarketId, (array)$_SESSION['stateprovincecity']['city'][$sanitizedRegion]))
		$marketId = $_SESSION['localization']->MarketId;
	$form['location']['city'] = array(
		'#type' => 'select',
		'#title' => t('City'),
		'#default_value' => isset($form_state['storage']['values']['city'])?$form_state['storage']['values']['city']:$marketId,
	);
	
	// get packages
	$form['packages'] = array(
		'#type' => 'radios',
		'#theme' => 'teligence_purchase_packagesradios',
		'#default_value' => $form_state['storage']['values']['packages'],
	);
	
	// payment information
	$form['payment']['paymethods'] = array(
		'#type' => 'radios',
		'#options' => array('pp'=>'PayPal', 'cc'=>t('Credit Card')),
		'#default_value' => $form_state['storage']['values']['paymethods'],
	);
	$form['payment']['cardholdername'] = array(
		'#type' => 'textfield',
		'#title' => t("Cardholder's Name"),
		'#default_value' => $form_state['storage']['values']['cardholdername'],
	);
	$form['payment']['cardnumber'] = array(
		'#type' => 'textfield',
		'#title' => t('Card Number'),
		'#default_value' => $form_state['storage']['values']['cardnumber'],
		'#pre_render' => array('teligence_purchase_ccn_prerender'),
	);
	$form['payment']['securitycode'] = array(
		'#type' => 'textfield',
		'#title' => t('Security Code'),
		'#default_value' => $form_state['storage']['values']['securitycode'],
		'#pre_render' => array('teligence_purchase_cvv_prerender'),
	);
	$form['payment']['zippostal'] = array(
		'#type' => 'textfield',
		'#title' => t('Billing ').($_SESSION['localization']->Country == 'Canada' ? t('Postal Code') : t('Zip Code')),
		'#default_value' => $form_state['storage']['values']['zippostal'],
	);
	$form['payment']['cc_expiration'] = array (
    	'#type'=>'date',
    	'#title'=>t('Expiration Date'),
    	'#theme' => 'teligence_purchase_ccexpirationdate',
    	'#description'=>t('Enter expiration date on card'),
    	'#default_value' => $form_state['storage']['values']['cc_expiration'],
    );
	
	$form['submitpurchase'] = array(
		'#type' => 'submit',
		'#value' => t('Complete My Purchase'),
		'#pre_render' => array('teligence_purchase_button_prerender'),
	);
	
	return $form;
}
function teligence_purchase_buypackage32_form_validate($form, &$form_state)
{
	if($form_state['clicked_button']['#id'] == 'edit-submitpurchase')
	{
		// packages
		if(!isset($form_state['values']['packages']) || empty($form_state['values']['packages']))
		{
			form_error($form['packages'], t('Please select a package.'));
		}
		
		// paymethods
		if(empty($form_state['values']['paymethods']))
		{
			form_error($form['payment']['paymethods'], t("Please select one payment method."));
		}
		
		// credit card validation
		if($form_state['values']['paymethods'] == 'cc')
		{
			// cardholder name
			$form_state['values']['cardholdername'] = trim($form_state['values']['cardholdername']);
			if(empty($form_state['values']['cardholdername']))
			{
				form_error($form['payment']['cardholdername'], t("Cardholder's Name is required."));
			}
			
			// card number
			$form_state['values']['cardnumber'] = trim($form_state['values']['cardnumber']);
			if(!teligence_cart_valid_card_number($form_state['values']['cardnumber']))
			{
				form_error($form['payment']['cardnumber'], t('Invalid Credit Card Number.'));
			}
			
			// security code
			$form_state['values']['securitycode'] = trim($form_state['values']['securitycode']);
			if(!ctype_digit($form_state['values']['securitycode']) || strlen($form_state['values']['securitycode']) < 3)
			{
				form_error($form['payment']['securitycode'], t('Invalid Security Code.'));
			}
			
			// zip/postal
			$form_state['values']['zippostal'] = trim($form_state['values']['zippostal']);
			if(!teligence_purchase_validate_zippostal($form_state['values']['zippostal']))
			{
				form_error($form['payment']['zippostal'],t('Invalid Zip/Postal Code.'));
			}
			
			// expiration date
			teligence_purchase_validate_expirationdate($form['payment']['cc_expiration'], $form_state);
		}
		
		// make form persistent
		$form_state['storage']['values'] = $form_state['values'];
		$flat = teligence_purchase_array_flatten($form['location']['stateprovince']['#options'], FALSE);
		$form_state['storage']['values']['stateprovincename'] = $flat[$form_state['values']['stateprovince']];
	}
	
	// drupal_set_message('<pre>'.check_plain(print_r($form['location']['city']['#options'],1)).'</pre>');
}
function teligence_purchase_buypackage32_form_submit($form, &$form_state)
{
	// after filling up the form go to confirmation
	if($form_state['clicked_button']['#id'] == 'edit-submitpurchase')
	{
		// parse package elements; id, price, minutes
		$package = explode('|',$form_state['values']['packages']);
		
		// credit card
		if($form_state['storage']['values']['paymethods'] == 'cc')
		{
			// ValidateAsuSignedInNewCreditCard
			$params = new stdClass ();
			$params->webMemberId = $_SESSION['WebMemberId'];
			$params->marketId = $form_state['values']['city'];
			$params->packageId = $package[0];
			$params->creditCardNumber = $form_state['values']['cardnumber'];
			$params->expiryDateMmYy = str_pad($form_state['values']['cc_expiration']['month'].$form_state['values']['cc_expiration']['year'],4,"0",STR_PAD_LEFT);
			$params->cardholderName = $form_state['values']['cardholdername'];
			$params->zip = $form_state['values']['zippostal'];
			$result = teligence_purchase_soap_call($params, 'ValidateAsuSignedInNewCreditCard', variable_get('teligence_purchase_wsdl_ordermanagement',''),TRUE);
			switch ($result->ValidateAsuSignedInNewCreditCardResult->ResponseCode) 
			{
				case 'Success':
					$form_state['storage']['values']['ValidateResult'] = $result->ValidateAsuSignedInNewCreditCardResult;
					$form_state['storage']['step'] = 'verifyorder';
					break;
				case 'ExistingMembershipBrandHub': 
					// signin as ivr_user, send validation email and redirect to 3.3				
					
					// load user
					global $user;
					
					// update drupal user
					$form_state['WebActiveMemberships'] = $result->ValidateAsuSignedInNewCreditCardResult->WebActiveMemberships;
					$form_state['values']['email'] = $user->mail;
					$user = teligence_purchase_drupaluser($form_state);
					
					// save values in the session
					$sessionValues = $result->ValidateAsuSignedInNewCreditCardResult;
					teligence_purchase_setsessionvalues($sessionValues);
					
					// message to user
					drupal_set_message(t('We found you in our system. You can select from the packages below.'));
					
					// redirect to success page
					drupal_goto('cart/add-time');
					break;
				case 'InactivePaymethod':
				case 'EmailLinkedToWebAccount':
				case 'CreditCardBelongsToOtherMember':
				case 'CreditCardLinkedToWebAccount':
					drupal_set_message(t('We found you in our system already. Please !sign', array('!sign' => l(t('click here to sign-in'),'cart/login'))),'error');
					break;
				case 'NegativeCreditStatus':
				case 'NoSalesPaymentRestriction':
				case 'DebtOrPaymentRestriction':
				case 'OlderExpirationDate':
				case 'DuplicateRequestGuid':
				case 'FraudulentPaymethod':
					drupal_set_message(t('!callcs', array('!callcs' => variable_get('teligence_purchase_customerservice',''))),'error');
					break;
				case 'InvalidRequestParams':
				case 'TechnicalError':
				default:
					drupal_set_message(t('!error',array('!error'=>$result->ValidateAsuSignedInNewCreditCardResult->ErrMsg)),'error');
					break;
			}
		}

		// paypal
		if($form_state['storage']['values']['paymethods'] == 'pp')
		{
			// send request to paypal.teligence.net
			module_load_include('inc', 'teligence_purchase', 'teligence_purchase-paypal');
			$urlquery = array(
				// 'areaCode' => '', // from previous implementation
				// 'Ani' => '', // from previous implementation
				// 'Password' => $form_state['storage']['values']['password'],
				// 'Email' => $GLOBALS['user']->mail,
				'SequenceId' => teligence_cart_uuid(TRUE),
				'PackageId' => $package[0],
				'VendorPass' => md5(variable_get('teligence_cart_paypal_vendor_pass_asu', '')),
				'lang' => $GLOBALS['language']->language,
				'WebMemberId' => $_SESSION['WebMemberId'],
				'IvrBrandId' => variable_get('teligence_purchase_brandid', 1),
			);
			if(!teligence_purchase_paypalSetSessionData($urlquery,variable_get('teligence_cart_paypal_vendor_id_asu', '')))
			{
				// could not connect to paypal.teligence.net
				drupal_set_message(t('!callcs', array('!callcs' => variable_get('teligence_purchase_customerservice',''))),'error');
			}
		}
	}
	
	// place order
	if($form_state['clicked_button']['#id'] == 'edit-placeorder')
	{
		// credit card
		if($form_state['storage']['values']['paymethods'] == 'cc')
		{
			// ProcessPayment
			$params = new stdClass ();
			$params->orderId = $form_state['storage']['values']['ValidateResult']->OrderId;
			$params->paymethodId = $form_state['storage']['values']['ValidateResult']->PaymethodId;
			$params->cvn = $form_state['storage']['values']['securitycode'];
			$result = teligence_purchase_soap_call($params, 'ProcessPayment', variable_get('teligence_purchase_wsdl_ordermanagement',''));
			switch ($result->ProcessPaymentResult->ResponseCode) 
			{
				case 'Success':
					// add drupal role 'ivr_user' to this user
					// load user
					global $user;
					
					// update drupal user
					$form_state['WebActiveMemberships'] = $result->ProcessPaymentResult->WebActiveMemberships;
					$form_state['values']['email'] = $user->mail;
					$user = teligence_purchase_drupaluser($form_state);
					
					// save values in the session
					$sessionValues = $result->ProcessPaymentResult;
					teligence_purchase_setsessionvalues($sessionValues);
					
					// redirect to success page
					$querystring = array(
						'City' => trim(str_replace("2", "",$result->ProcessPaymentResult->WebActiveMemberships->MarketName)),
						'Email' => $GLOBALS['user']->mail,
						'TotalAmountCents' => $form_state['storage']['values']['ValidateResult']->TotalAmountCents,
						'PackageMinutes' => $form_state['storage']['values']['ValidateResult']->PackageMinutes,
						'IvrMembershipNumber' => $result->ProcessPaymentResult->IvrMembershipNumber,
						'IvrPasscode' => $result->ProcessPaymentResult->IvrPasscode,
						'LocalAccessNumber' => $result->ProcessPaymentResult->LocalAccessNumber,
					);
					drupal_goto('cart/result/creditcardasu',$querystring);
					break;
				case 'AuthorizationDeclined':
				case 'RiskScoreReject':
				case 'RiskScoreReview':
				case 'AuthorizationTechnicalIssue':
				case 'RtmFailure':
					drupal_set_message(t('!callcs', array('!callcs' => variable_get('teligence_purchase_customerservice',''))),'error');
					break;
				case 'InvalidRequestParams':
				case 'TechnicalError':
				default:
					drupal_set_message(t('!error',array('!error'=>$result->ProcessPaymentResult->ErrMsg)),'error');
					break;
			}
					
		}
	}
	
	// go back to modify a value
	if($form_state['clicked_button']['#id'] == 'edit-back')
	{
		unset($form_state['storage']['step']);
		$form_state['storage']['values']['packages'] = $form_state['values']['packages'];
		
		// drupal_set_message('<pre>'.check_plain(print_r($form_state['storage']['values'],1)).'</pre>');
	}
}





/***************************************************************
 * 3.3 Customer with web account (signed in) and active linked IVR memberships
 */
function teligence_purchase_buypackage33_form($form_state)
{
	if($form_state['storage']['step'] == 'verifyorder')
	{
		drupal_set_title(t('Review Purchase.'));
		$form['verifyorder33'] = array(
			'#theme'=> 'teligence_purchase_verifyorder',
			'#value' => $form_state['storage']['values'],
		);
		$form['packages'] = array(
			'#type' => 'hidden',
			'#default_value' => $form_state['storage']['values']['packages'],
		);
		$form['back'] = array(
			'#type' => 'submit',
			'#value' => t('Go Back'),
			'#pre_render' => array('teligence_purchase_button_prerender'),
		);
		$form['placeorder'] = array(
			'#type' => 'submit',
			'#value' => t('Place Order'),
			'#pre_render' => array('teligence_purchase_button_prerender'),
		);
		return $form;
	}
	
	$form['#pre_render'] = array('teligence_purchase_buypackage_form_prerender');
	$form['#after_build'] = array('teligence_purchase_buypackage_form_afterbuild');
	
	// existing memberships
	$form['memberships'] = array(
		'#type' => 'radios',
		'#theme' => 'teligence_purchase_memberships',
		'#default_value' => isset($form_state['storage']['values']['memberships'])?
							$form_state['storage']['values']['memberships']:
							$_SESSION['IvrMembershipNumber'],
	);
	
	// get markets
	// find default region and market; localization
	$region = key((array)$_SESSION['stateprovincecity']['city']);
	if(key_exists(strtoupper(filter_var($_SESSION['localization']->Region,FILTER_SANITIZE_URL)), $_SESSION['stateprovincecity']['city']))
		$region = $_SESSION['localization']->Region;
	$sanitizedRegion = strtoupper(filter_var($region,FILTER_SANITIZE_URL));
	$form['location']['stateprovince'] = array(
		'#type' => 'select',
		'#title' => t('State/Province'),
		'#default_value' => isset($form_state['storage']['values']['stateprovince'])?
							$form_state['storage']['values']['stateprovince']:$sanitizedRegion,
		'#options' => (array)$_SESSION['stateprovincecity']['stateprovince'],
	);
	$marketId = key((array)$_SESSION['stateprovincecity']['city'][$sanitizedRegion]);
	if(key_exists($_SESSION['localization']->MarketId, (array)$_SESSION['stateprovincecity']['city'][$sanitizedRegion]))
		$marketId = $_SESSION['localization']->MarketId;
	$form['location']['city'] = array(
		'#type' => 'select',
		'#title' => t('City'),
		'#default_value' => isset($form_state['storage']['values']['city'])?
							$form_state['storage']['values']['city']:$marketId,
	);
	
	// get packages
	$form['packages'] = array(
		'#type' => 'radios',
		'#theme' => 'teligence_purchase_packagesradios',
		'#default_value' => $form_state['storage']['values']['packages'],
	);
	
	// payment information
	$form['paymethods'] = array(
		'#type' => 'radios',
		'#options' => array('pp'=>'Pay with PayPal', 'cc'=>t('Pay with an existing credit card:'), 'addcc' => t('Pay with a new credit card:')),
		'#default_value' => $form_state['storage']['values']['paymethods'],
	);
	
	// existing credit cards
	$form['creditcardslist'] = array(
		'#type'=>'radios',
		'#theme'=>'teligence_purchase_creditcardslist',
		'#default_value'=> $form_state['storage']['values']['creditcardslist'],
	);
	
	// Add new credit card
	$form['payment']['cardholdername'] = array(
		'#type' => 'textfield',
		'#title' => t("Cardholder's Name"),
		'#default_value' => $form_state['storage']['values']['cardholdername'],
	);
	$form['payment']['cardnumber'] = array(
		'#type' => 'textfield',
		'#title' => t('Card Number'),
		'#default_value' => $form_state['storage']['values']['cardnumber'],
		'#pre_render' => array('teligence_purchase_ccn_prerender'),
	);
	$form['payment']['securitycode'] = array(
		'#type' => 'textfield',
		'#title' => t('Security Code'),
		'#default_value' => $form_state['storage']['values']['securitycode'],
		'#pre_render' => array('teligence_purchase_cvv_prerender'),
	);
	$form['payment']['zippostal'] = array(
		'#type' => 'textfield',
		'#title' => t('Billing ').($_SESSION['localization']->Country == 'Canada' ? t('Postal Code') : t('Zip Code')),
		'#default_value' => $form_state['storage']['values']['zippostal'],
	);
	$form['payment']['cc_expiration'] = array (
    	'#type'=>'date',
    	'#title'=>t('Expiration Date'),
    	'#theme' => 'teligence_purchase_ccexpirationdate',
    	'#description'=>t('Enter expiration date on card'),
    	'#default_value' => $form_state['storage']['values']['cc_expiration'],
    );
	
	$form['submitpurchase'] = array(
		'#type' => 'submit',
		'#value' => t('Complete My Purchase'),
		'#pre_render' => array('teligence_purchase_button_prerender'),
	);
	
	return $form;
}
function teligence_purchase_buypackage33_form_validate($form, &$form_state)
{
	
	// $form_state['storage']['values'] = $form_state['values'];
	
	if($form_state['clicked_button']['#id'] == 'edit-submitpurchase')
	{
		// packages
		if(!isset($form_state['values']['packages']) || empty($form_state['values']['packages']))
		{
			form_error($form['packages'], t('Please select a package.'));
		}
		
		// memberships
		$marketids = array();
		foreach ((array)$_SESSION['emsMemberships'] as $key => $value) 
		{
			$marketids[] = $value->MarketId;
		}
		if(in_array($form_state['values']['city'],$marketids) && $form_state['values']['memberships'] == 'newmarket')
		{
			form_error($form['memberships'], t('Please select either an existing membership or a new city; and then a package.'));
		}
		
		// paymethods
		if(empty($form_state['values']['paymethods']))
		{
			form_error($form['paymethods'], t("Please select one payment method."));
		}
		
		// credit card validation
		if($form_state['values']['paymethods'] == 'addcc')
		{
			// cardholder name
			$form_state['values']['cardholdername'] = trim($form_state['values']['cardholdername']);
			if(empty($form_state['values']['cardholdername']))
			{
				form_error($form['payment']['cardholdername'], t("Cardholder's Name is required."));
			}
			
			// card number
			$form_state['values']['cardnumber'] = trim($form_state['values']['cardnumber']);
			if(!teligence_cart_valid_card_number($form_state['values']['cardnumber']))
			{
				form_error($form['payment']['cardnumber'], t('Invalid Credit Card Number.'));
			}
			
			// security code
			$form_state['values']['securitycode'] = trim($form_state['values']['securitycode']);
			if(!ctype_digit($form_state['values']['securitycode']) || strlen($form_state['values']['securitycode']) < 3)
			{
				form_error($form['payment']['securitycode'], t('Invalid Security Code.'));
			}
			
			// zip/postal
			$form_state['values']['zippostal'] = trim($form_state['values']['zippostal']);
			if(!teligence_purchase_validate_zippostal($form_state['values']['zippostal']))
			{
				form_error($form['payment']['zippostal'],t('Invalid Zip/Postal Code.'));
			}
			
			// expiration date
			teligence_purchase_validate_expirationdate($form['payment']['cc_expiration'], $form_state);
		}
		
		// make form persistent
		$form_state['storage']['values'] = $form_state['values'];
		$flat = teligence_purchase_array_flatten($form['location']['stateprovince']['#options'], FALSE);
		$form_state['storage']['values']['stateprovincename'] = $flat[$form_state['values']['stateprovince']];
	}
	
}
function teligence_purchase_buypackage33_form_submit($form, &$form_state)
{
	// after filling up the form go to confirmation
	if($form_state['clicked_button']['#id'] == 'edit-submitpurchase')
	{
		
		// parse package elements; id, price, minutes
		$package = explode('|',$form_state['values']['packages']);
		$cc = explode('|',$form_state['values']['creditcardslist']);
		
		// credit card
		if($form_state['storage']['values']['paymethods'] == 'cc')
		{
			// ValidateSrOldCreditCard
			if($form_state['values']['memberships'] <> 'newmarket')
			{
				$params = new stdClass ();
				$params->emsMembershipId = $_SESSION['emsMemberships'][$form_state['values']['memberships']]->EmsMembershipId;
				$params->packageId = $package[0];
				$params->paymethodId = $cc[0];
				$result = teligence_purchase_soap_call($params, 'ValidateSrOldCreditCard', variable_get('teligence_purchase_wsdl_ordermanagement',''),TRUE);
				switch ($result->ValidateSrOldCreditCardResult->ResponseCode) 
				{
					case 'Success':
						$form_state['storage']['values']['ValidateResult'] = $result->ValidateSrOldCreditCardResult;
						$form_state['storage']['step'] = 'verifyorder';
						break;
					case 'MemberHasDebt':
					case 'CreditCardPaymentRestriction':
					case 'CreditCardBelongsToOtherMember':
					case 'DuplicateRequestGuid':
						drupal_set_message(t('!callcs', array('!callcs' => variable_get('teligence_purchase_customerservice',''))),'error');
						break;
					case 'InvalidRequestParams':
					case 'TechnicalError':
					default:
						drupal_set_message(t('!error',array('!error'=>$result->ValidateSrOldCreditCardResult->ErrMsg)),'error');
						break;
				}
			}
			
			// ValidateAsuSignedInOldCreditCard
			if($form_state['values']['memberships'] == 'newmarket')
			{
				$params = new stdClass ();
				$params->emsMemberId = $_SESSION['EmsMemberId'];
				$params->marketId = $form_state['values']['city'];
				$params->packageId = $package[0];
				$params->paymethodId = $cc[0];
				$result = teligence_purchase_soap_call($params, 'ValidateAsuSignedInOldCreditCard', variable_get('teligence_purchase_wsdl_ordermanagement',''),TRUE);
				switch ($result->ValidateAsuSignedInOldCreditCardResult->ResponseCode) 
				{
					case 'Success':
						$form_state['storage']['values']['ValidateResult'] = $result->ValidateAsuSignedInOldCreditCardResult;
						$form_state['storage']['step'] = 'verifyorder';
						break;
					case 'ExistingMembershipBrandHub':
						drupal_set_message(t('You can use your existing @city membership (@ivr) to chat with local singles in @city2.',
							array(
								'@ivr'=>$_SESSION['IvrMembershipNumber'],
								'@city'=>$_SESSION['emsMemberships'][$_SESSION['IvrMembershipNumber']]->MarketName,
								'@city2'=>$_SESSION['stateprovincecity']['city'][$form_state['values']['stateprovince']][$form_state['values']['city']],
							)),'error');
						$form_state['storage']['values']['memberships']	= $result->ValidateAsuSignedInOldCreditCardResult->IvrMembershipNumber;
						break;
					case 'FraudulentPaymethod':
					case 'DuplicateRequestGuid':
					case 'OlderExpirationDate':
					case 'InactivePaymethod':
					case 'DebtOrPaymentRestriction':
					case 'NegativeCreditStatus':
					case 'NoSalesPaymentRestriction':
					case 'CreditCardBelongsToOtherMember':
						drupal_set_message(t('!callcs', array('!callcs' => variable_get('teligence_purchase_customerservice',''))),'error');
						break;
					case 'InvalidRequestParams':
					case 'TechnicalError':
					default:
						drupal_set_message(t('!error',array('!error'=>$result->ValidateAsuSignedInOldCreditCardResult->ErrMsg)),'error');
						break;
				}
			}
		}

		// add new credit card
		if($form_state['storage']['values']['paymethods'] == 'addcc')
		{
			// ValidateAsuSignedInNewCreditCard
			if($form_state['values']['memberships'] == 'newmarket')
			{
				$params = new stdClass ();
				$params->webMemberId = $_SESSION['WebMemberId'];
				$params->marketId = $form_state['values']['city'];
				$params->packageId = $package[0];
				$params->creditCardNumber = $form_state['values']['cardnumber'];
				$params->expiryDateMmYy = str_pad($form_state['values']['cc_expiration']['month'].$form_state['values']['cc_expiration']['year'],4,"0",STR_PAD_LEFT);
				$params->cardholderName = $form_state['values']['cardholdername'];
				$params->zip = $form_state['values']['zippostal'];
				$result = teligence_purchase_soap_call($params, 'ValidateAsuSignedInNewCreditCard', variable_get('teligence_purchase_wsdl_ordermanagement',''),TRUE);
				switch ($result->ValidateAsuSignedInNewCreditCardResult->ResponseCode) 
				{
					case 'Success':
						$form_state['storage']['values']['ValidateResult'] = $result->ValidateAsuSignedInNewCreditCardResult;
						$form_state['storage']['step'] = 'verifyorder';
						break;
					case 'ExistingMembershipBrandHub':
						drupal_set_message(t('You can use your existing @city (@ivr) membership to chat with local singles in @city2.',
							array(
								'@ivr'=>$_SESSION['IvrMembershipNumber'],
								'@city'=>$_SESSION['emsMemberships'][$_SESSION['IvrMembershipNumber']]->MarketName,
								'@city2'=>$_SESSION['stateprovincecity']['city'][$form_state['values']['stateprovince']][$form_state['values']['city']],
							)),'error');
						$form_state['storage']['values']['memberships']	= $result->ValidateAsuSignedInNewCreditCardResult->IvrMembershipNumber;
						break;
					case 'FraudulentPaymethod':
					case 'DuplicateRequestGuid':
					case 'OlderExpirationDate':
					case 'InactivePaymethod':
					case 'DebtOrPaymentRestriction':
					case 'NegativeCreditStatus':
					case 'NoSalesPaymentRestriction':
					case 'CreditCardBelongsToOtherMember':
						drupal_set_message(t('!callcs', array('!callcs' => variable_get('teligence_purchase_customerservice',''))),'error');
						break;
					case 'InvalidRequestParams':
					case 'TechnicalError':
					default:
						drupal_set_message(t('!error',array('!error'=>$result->ValidateAsuSignedInNewCreditCardResult->ErrMsg)),'error');
						break;
				}
			}

			// ValidateSrNewCreditCard
			if($form_state['values']['memberships'] <> 'newmarket')
			{
				$params = new stdClass ();
				$params->emsMembershipId = $_SESSION['emsMemberships'][$form_state['values']['memberships']]->EmsMembershipId;
				$params->packageId = $package[0];
				$params->creditCardNumber = $form_state['values']['cardnumber'];
				$params->expiryDateMmYy = str_pad($form_state['values']['cc_expiration']['month'].$form_state['values']['cc_expiration']['year'],4,"0",STR_PAD_LEFT);
				$params->cardholderName = $form_state['values']['cardholdername'];
				$params->zip = $form_state['values']['zippostal'];
				$result = teligence_purchase_soap_call($params, 'ValidateSrNewCreditCard', variable_get('teligence_purchase_wsdl_ordermanagement',''),TRUE);
				switch ($result->ValidateSrNewCreditCardResult->ResponseCode) 
				{
					case 'Success':
						$form_state['storage']['values']['ValidateResult'] = $result->ValidateSrNewCreditCardResult;
						$form_state['storage']['step'] = 'verifyorder';
						break;
					case 'MemberHasDebt':
					case 'CreditCardPaymentRestriction':
					case 'CreditCardBelongsToOtherMember':
					case 'DuplicateRequestGuid':
						drupal_set_message(t('!callcs', array('!callcs' => variable_get('teligence_purchase_customerservice',''))),'error');
						break;
					case 'InvalidRequestParams':
					case 'TechnicalError':
					default:
						drupal_set_message(t('!error',array('!error'=>$result->ValidateSrNewCreditCardResult->ErrMsg)),'error');
						break;
				}
			}
		}

		// paypal
		if($form_state['storage']['values']['paymethods'] == 'pp')
		{
			// send request to paypal.teligence.net
			module_load_include('inc', 'teligence_purchase', 'teligence_purchase-paypal');
			$urlquery = array(
				// 'areaCode' => '', // from previous implementation
				// 'Ani' => '', // from previous implementation
				// 'Pass' => $form_state['storage']['values']['password'],
				// 'Email' => $GLOBALS['user']->mail,
				'SequenceId' => teligence_cart_uuid(TRUE),
				'PackageId' => $package[0],
				'lang' => $GLOBALS['language']->language,
				'WebMemberId' => $_SESSION['WebMemberId'],
				'IvrBrandId' => variable_get('teligence_purchase_brandid', 1),
			);
			
			if($form_state['values']['memberships'] == 'newmarket') 
			// ValidateAsuPurchase
			{
				$vendorId = variable_get('teligence_cart_paypal_vendor_id_asu', '');
				$urlquery['VendorPass'] = md5(variable_get('teligence_cart_paypal_vendor_pass_asu', ''));
			}
			else 
			// ValidateSrPurchase
			{
				$vendorId = variable_get('teligence_cart_paypal_vendor_id_sr', '');
				$urlquery['VendorPass'] = md5(variable_get('teligence_cart_paypal_vendor_pass_sr', ''));
				$urlquery['EmsMembershipId'] = $_SESSION['emsMemberships'][$form_state['values']['memberships']]->EmsMembershipId;
			}
			
			if(!teligence_purchase_paypalSetSessionData($urlquery,$vendorId))
			{
				// could not connect to paypal.teligence.net
				drupal_set_message(t('!callcs', array('!callcs' => variable_get('teligence_purchase_customerservice',''))),'error');
			}
		}
	}
	
	// place order
	if($form_state['clicked_button']['#id'] == 'edit-placeorder')
	{
		// credit card
		if($form_state['storage']['values']['paymethods'] == 'cc' || $form_state['storage']['values']['paymethods'] == 'addcc')
		{
			$params = new stdClass ();
			$params->orderId = $form_state['storage']['values']['ValidateResult']->OrderId;
			$params->paymethodId = $form_state['storage']['values']['ValidateResult']->PaymethodId;
			$params->cvn = $form_state['storage']['values']['securitycode'];
			$result = teligence_purchase_soap_call($params, 'ProcessPayment', variable_get('teligence_purchase_wsdl_ordermanagement',''));
			switch ($result->ProcessPaymentResult->ResponseCode) 
			{
				case 'Success':
					// refresh balance
					if($form_state['storage']['values']['memberships'] <> 'newmarket')
						unset($_SESSION['emsMemberships'][$_SESSION['IvrMembershipNumber']]->Balance);
					
					// drupal_set_message('<pre>'.check_plain(print_r($result->ProcessPaymentResult->WebActiveMemberships,1)).'</pre>');
					// refresh session values
					teligence_purchase_setsessionvalues($result->ProcessPaymentResult);
					
					// redirect to success page
					$querystring = array(
						'Email' => $GLOBALS['user']->mail,
						'City' => $_SESSION['emsMemberships'][$_SESSION['IvrMembershipNumber']]->MarketName,
						'IvrMembershipNumber' => $_SESSION['emsMemberships'][$_SESSION['IvrMembershipNumber']]->IvrMembershipNumber,
						'IvrPasscode' => $_SESSION['emsMemberships'][$_SESSION['IvrMembershipNumber']]->IvrPasscode,
						'TotalAmountCents' => $form_state['storage']['values']['ValidateResult']->TotalAmountCents,
						'PackageMinutes' => $form_state['storage']['values']['ValidateResult']->PackageMinutes,
						'LocalAccessNumber' => $result->ProcessPaymentResult->LocalAccessNumber,
					);
					drupal_goto('cart/result/creditcardsr',$querystring);
					break;
				case 'AuthorizationDeclined':
				case 'RiskScoreReject':
				case 'RiskScoreReview':
				case 'AuthorizationTechnicalIssue':
				case 'RtmFailure':
					drupal_set_message(t('!callcs', array('!callcs' => variable_get('teligence_purchase_customerservice',''))),'error');
					break;
				case 'InvalidRequestParams':
				case 'TechnicalError':
				default:
					drupal_set_message(t('!error',array('!error'=>$result->ProcessPaymentResult->ErrMsg)),'error');
					break;
			}
					
		}
	}
	
	// go back to modify a value
	if($form_state['clicked_button']['#id'] == 'edit-back')
	{
		unset($form_state['storage']['step']);
		$form_state['storage']['values']['packages'] = $form_state['values']['packages'];
	}
}