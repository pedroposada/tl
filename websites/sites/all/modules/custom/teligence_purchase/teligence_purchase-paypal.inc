<?php

/**
 * paypalSetSessionData
 * set sesssion data
 * redirects to paypal.teligence.net on success
 * returns false on failure
 */
function teligence_purchase_paypalSetSessionData($urlquery,$vendorId)
{
	/**
	 * Implement similar solution as with PAYPAL API,
	 * use cURL to send query parameters, this will authenticate this vendor 
	 * and store parameters in SessionData table
	 * then get SessionID back and direct user to display package details.
	 * At the end, the URL at the payment web-site will look cleaner and more secure
	 */
	$url = url(variable_get('teligence_cart_paypal_gateway_url','') . 
		'/paypal/setsessiondata/' . $vendorId, array('query' => $urlquery));
	$parsedResponse = teligence_cart_paypal_curl($url);
	if($parsedResponse['Action'] == 'Success' && strlen($parsedResponse['Token']))
	{
		drupal_goto(variable_get('teligence_cart_paypal_gateway_url','') . 
			'/paypal/package-details', array('Token' => $parsedResponse['Token']));
		
	}
	else
	{
		watchdog('teligence_purchase','002 - cURL brand websites cannot connect to paypal.teligence.net; connection times out or response is invalid !res', array('!res'=>'<pre>'.check_plain(print_r($parsedResponse,1)).'</pre>'),WATCHDOG_ERROR);
		return FALSE;
	}
}


/**
 * handler for paypal
 * request comes back from paypal to here
 */
function teligence_purchase_paypalhandler()
{
	$values = array();
	
	//get session data from payment site
	if(strlen($_REQUEST['Token']))
	{
		$url = url(variable_get('teligence_cart_paypal_gateway_url','') . '/paypal/getsessiondata/' . urldecode($_REQUEST['Token']));
		$values = teligence_cart_paypal_curl($url);
		$values = array_merge($values,$_REQUEST);
	}
	else
	{
		$values['error'] = 'Token missing';
	}
	
	// filter the array
	$v = array();
	$q = '';
	if(isset($values['error']) && !empty($values['error'])) // error coming from back-end through paypal.teligence.net website
	{
		// ExistingMembershipBrandHub
		if(strstr($values['error'],'ExistingMembershipBrandHub'))
		{
			$params = new stdClass();
			$params->webMemberId = $values['WebMemberId'];
			$result = teligence_purchase_soap_call($params, 'GetActiveMemberships', variable_get('teligence_purchase_wsdl_membercredentials',''));
			switch ($result->GetActiveMembershipsResult->ResponseCode) 
			{
				case 'Success':
					// signin as ivr_user, send validation email and redirect to 3.3				
					
					// load user
					global $user;
					
					// update drupal user
					$form_state['values']['email'] = $GLOBALS['user']->mail;
					$form_state['WebActiveMemberships'] = $result->GetActiveMembershipsResult->WebActiveMemberships;
					$user = teligence_purchase_drupaluser($form_state);
					
					// save values in the session
					$sessionValues = $result->GetActiveMembershipsResult;
					teligence_purchase_setsessionvalues($sessionValues);
					
					// message to user
					drupal_set_message(t('We found you in our system. You can select from the packages below.'));
					
					$url = url('cart/add-time');
					// make url language sensitive
					if(array_key_exists($values['lang'], language_list()))
					{
						$languages = language_list();
						$url = url('cart/add-time',array('language'=>$languages[$vars['lang']]));
					}
					drupal_goto($url);
					break;
			}
		}
		
		$errors = array(
			'DoVoid',
			'RtmFailure',
			'InvalidRequestParams',
			'TechnicalError',
			'PackageNotFound',
			'DuplicateRequestGuid',
			'ExistingMembershipBrandHub',
			'DebtOrPaymentRestriction',
			'NoSalesPaymentRestriction',
			'PayPalPayerIdBelongsToOtherMember',
			'PayPalPayerIdLinkedToWebAccount',
			'PayPayPayerIdLinkedToWebAccount',
			'MemberNotFound',
			'TechnicalError',
		);
		foreach ($errors as $error) 
		{
			if(strstr($values['error'],$error))
			{
				$values['error'] = $error;
			}
		}
		$v['ErrorMessage'] = $values['error'];
		$path = 'cart/result/paypalfailure';
	}
	else
	// success 
	{
		// add drupal role 'ivr_user' to this user
		if(isset($values['WebMemberId']) && strlen($values['WebMemberId']))
		{
			$params = new stdClass();
			$params->webMemberId = $values['WebMemberId'];
			$result = teligence_purchase_soap_call($params, 'GetActiveMemberships', variable_get('teligence_purchase_wsdl_membercredentials',''));
			switch ($result->GetActiveMembershipsResult->ResponseCode) 
			{
				case 'Success':
					// load user
					global $user;
					
					// update drupal user
					$form_state['values']['email'] = ($user->uid ? $user->mail : $values['Email']);
					(strlen($values['Password']) ? $form_state['values']['password'] = $values['Password']:NULL);
					$form_state['WebActiveMemberships'] = $result->GetActiveMembershipsResult->WebActiveMemberships;
					$user = teligence_purchase_drupaluser($form_state);
					
					// save values in the session
					$sessionValues = new stdClass();
					$sessionValues->WebActiveMemberships = $result->GetActiveMembershipsResult->WebActiveMemberships;
					$sessionValues->WebMemberId = $values['WebMemberId'];
					teligence_purchase_setsessionvalues($sessionValues);
					break;
			}
		}
		
		// send validation email
		if(strlen($values['ValidationCode']) && !strstr($values['ValidationCode'],'00000000-0000-0000-0000'))
		{
			$tokens = teligence_purchase_tokens('emailValidateAccount');
			$tokens['[email]'] = $values['Email'];
			$tokens['[password]'] = $values['Password'];
			
			// make email language sensitive 
			$lang = language_default();
			$langList = language_list();
			if(array_key_exists($values['lang'], $langList))
				$lang = $langList[$values['lang']];

			$tokens['[url]'] = url('cart/validate-web-account/' . 
				$values['ValidationCode'] . '/' . 
				$values['Email'] . '/' . 
				$values['Password'], 
				array('absolute' => TRUE, 'language'=>$lang)
			);
			$tokens['languagecode'] = $lang->language;
			
			// send email
			drupal_mail('teligence_purchase', 'emailValidateAccount', $values['Email'], $lang, $tokens);
			drupal_set_message(t('We have sent you an email with a validation link. Please click it to validate your account.',array(),$lang->language));
		}
		
		$v['City'] = $_SESSION['emsMemberships'][$_SESSION['IvrMembershipNumber']]->MarketName;
		$v['Email'] = ($values['Email']?$values['Email']:$GLOBALS['user']->mail);
		$v['LocalAccessNumber'] = $values['LocalAccessNumber'];
		$v['TotalAmountDollars'] = $values['TotalAmountDollars'];
		$v['PackageMinutes'] = $values['PackageMinutes'];
		$v['IvrMembershipNumber'] = $_SESSION['IvrMembershipNumber'];
		$v['IvrPasscode'] = $_SESSION['IvrPasscode'];
		
		// differentiate between ASU and SR
		if(isset($values['Email']) && strlen($values['Email']))
		{
			$path = 'cart/result/paypalasu';
		}
		else 
		{
			$path = 'cart/result/paypalsr';
		}
		
		// refresh balance
		unset($_SESSION['emsMemberships'][$_SESSION['IvrMembershipNumber']]->Balance);
	}
	
	// default values for url redirect	
	$url = url($path);

	// make url language sensitive
	if(array_key_exists($values['lang'], language_list()))
	{
		$languages = language_list();
		$url = url($path,array('language'=>$languages[$values['lang']]));
	}
	drupal_goto($url,$v);
}