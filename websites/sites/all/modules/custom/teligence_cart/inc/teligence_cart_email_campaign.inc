<?php 

/*
 * email campaign form
 */
function teligence_cart_email_campaign($form_state)
{
	$form['#theme'] = 'teligence_cart_autosignup';

    $form['web_account'] = array (
	    '#type'=>'fieldset',
	    '#title'=>t('Web Account Info'),
		'#attributes' => array('class' => 'left-label'),
    	'#weight'=>1,
    );
    $form['web_account']['email'] = array (
	    '#type'=>'textfield',
	    '#title'=>t('Email'),
	    '#required'=>true,
    );
	$form['ivr_account'] = array (
    	'#type'=>'fieldset',
    	'#title'=>t('IVR Account Info'),
		'#attributes' => array('class' => 'left-label'),
		'#weight'=>2,
    );
	$form['ivr_account']['group'] = array(
		'#type' => 'fieldset',
		'#description' => t('Enter your phone number.'),
		'#weight'=>4,
	);
    $form['ivr_account']['group']['area_code'] = array (
        '#prefix' => '<div class="ani"><div class="parenthesys">(</div>',
        '#suffix' => '<div class="parenthesys">)</div>',
        '#type'=>'textfield',
        '#size'=>4,
        '#maxlength'=>3,
    );
    $form['ivr_account']['group']['phone_number'] = array (
        '#suffix' => '</div>',
        '#type'=>'textfield',
        '#size'=>8,
        '#maxlength'=>7,
    );
    $form['ivr_account']['ivr_number'] = array (
    	'#type'=>'textfield',
    	'#title'=>t('Membership Number'),
    	'#required'=>true,
    	'#size'=>10,
    	'#maxlength'=>5,
    );
    $form['ivr_account']['ivr_passcode'] = array (
	    '#type'=>'password',
	    '#title'=>t('Passcode'),
	    '#required'=>true,
	    '#size'=>6,
	    '#maxlength'=>4,
	    '#description'=>t('Must be a 4 digit number with no spaces or extra characters'),
    );

    $form['submit'] = array (
	    '#type'=>'submit',
	    '#value'=>t('Sign Up'),
    	'#weight'=>5,
    );

    return $form;
}

/*
 * validate email campaign form
 */
function teligence_cart_email_campaign_validate($form, &$form_state)
{
	$form_state['values']['email'] = trim($form_state['values']['email']);
    if (!teligence_cart_check_email($form_state['values']['email']))
    {
        form_set_error('email', t('Invalid email address'));
    }
    if (strlen($form_state['values']['area_code']) < 3 || !is_numeric($form_state['values']['area_code']))
    {
        form_set_error('area_code', t('Area Code must be 3 digits long'));
    }
	if (strlen($form_state['values']['phone_number']) < 7 || !is_numeric($form_state['values']['phone_number']))
    {
        form_set_error('phone_number', t('Phone Number must be 7 digits long'));
    }
    if (strlen($form_state['values']['ivr_number']) < 5)
    {
        form_set_error('ivr_number', t('Membership Number must be 5 digits long'));
    }
	if (strlen($form_state['values']['ivr_passcode']) < 4)
    {
        form_set_error('password', t('Passcode is too short.'));
    }
	if (!is_numeric($form_state['values']['ivr_passcode']))
    {
        form_set_error('password', t('Passcode must be a number.'));
    }
}

/*
 * submit email campaign form
 */
function teligence_cart_email_campaign_submit($form, & $form_state)
{
	if(module_exists('teligence_purchase'))
	{
		$MEMBER_CREDENTIALS = variable_get('teligence_purchase_wsdl_membercredentials','');
		$ORDER_MANAGEMENT = variable_get('teligence_purchase_wsdl_ordermanagement','');
	}
	else 
	{
		$MEMBER_CREDENTIALS = variable_get('wsdl_url_3', '');
		$ORDER_MANAGEMENT = variable_get('wsdl_url_5', '');	
	}
	
	$params = new stdClass ();
    $params->ivrBrandId = variable_get('teligence_cart_brand', 1);
    $params->ivrMembershipNumber = $form_state['values']['ivr_number'];
    $params->ivrPasscode = $form_state['values']['ivr_passcode'];
    $params->areaCode = $form_state['values']['area_code'];
    $result = teligence_cart_soap_call($params, 'CheckFreeTimeEligibility', $MEMBER_CREDENTIALS);
    switch($result['result']->CheckFreeTimeEligibilityResult->ResponseCode)
    {
        case 'NotFound':
            drupal_set_message(
            	t("Sorry, you are not eligible for this promotion. You can !purchase for your account !here.", 
	        		array(
	        			'!purchase' => l(t('purchase more minutes'), 'cart/buy'), 
	        			'!here' => l(t('here'), 'cart/buy'),
					)
				)
            );
        break;

        case 'FoundEligibleWithWebAccount':
        case 'FoundEligibleWithWebAccountEmailNeedsValidation':
            $validationurl = array();
            $validationurl[] = $result['result']->CheckFreeTimeEligibilityResult->ValidationCode;
            $validationurl[] = $form_state['values']['email'];
            $validationurl[] = variable_get('teligence_cart_free_minutes', 10);
            $validationurl[] = $result['result']->CheckFreeTimeEligibilityResult->EmsMembershipId;
            $validationurl[] = $form_state['values']['area_code'] . $form_state['values']['phone_number'];
            $validationurl[] = 0;
	        $validationurl[] = 1;
	        $validationurl[] = user_password(8);
	        $validationurl[] = $form_state['values']['ivr_passcode'];
	        $validationurl[] = $form_state['values']['ivr_number'];
        	
	        // prepare tokens for email and page
            $tokens = teligence_cart_tokens();
		    $tokens['tokens']['[url]'] = url('cart/validate-campaign/' . implode(',', $validationurl), array ('absolute'=>true));
		    $tokens['tokens']['[url]'] = l(urldecode($tokens['tokens']['[url]']), $tokens['tokens']['[url]']);
		    $tokens['tokens']['[ivr-number]'] = $form_state['values']['ivr_number'];
		    $tokens['tokens']['[ivr-passcode]'] = $form_state['values']['ivr_passcode'];
		    $tokens['tokens']['[web-password]'] = $validationurl[7];
		    $tokens['tokens']['[user-email]'] = $form_state['values']['email'];
		    $tokens['tokens']['[promo-minutes]'] = variable_get('teligence_cart_free_minutes', 10);
			
			if($result['result']->CheckFreeTimeEligibilityResult->ResponseCode == 'FoundEligibleWithWebAccount')
			    $tokens['tokens']['[web-password]'] = '*********';
			
			// send email 
        	drupal_mail('teligence_cart', 'email_campaign', $form_state['values']['email'], language_default(), $tokens);
			
		    // show success screen
            $_SESSION['teligence_cart_email_campaign_success'] = true;
			$_SESSION['teligence_cart_email_campaign_success_tokens'] = $tokens['tokens'];
            drupal_goto('cart/email-campaign/success');
        break;

        case 'FoundEligibleNoWebAccount':
			$params->email = $form_state['values']['email'];
            $params->password = $form_state['values']['password'] = user_password(8);
            $params->emsMemberId = $result['result']->CheckFreeTimeEligibilityResult->EmsMemberId;
			$params->ivrBrandId = variable_get('teligence_cart_brand', 1);
			(module_exists('teligence_purchase') ? $params->gender = 'M' : NULL);
            $resultSignUp = teligence_cart_soap_call($params, 'SignUp', $MEMBER_CREDENTIALS);
            switch($resultSignUp['result']->SignUpResult->ResponseCode)
            {
                case 'Success':
            		$validationurl = array();
            		$validationurl[] = $resultSignUp['result']->SignUpResult->ValidationCode;
            		$validationurl[] = $form_state['values']['email'];
            		$validationurl[] = variable_get('teligence_cart_free_minutes', 10);
            		$validationurl[] = $result['result']->CheckFreeTimeEligibilityResult->EmsMembershipId;
            		$validationurl[] = $form_state['values']['area_code'] . $form_state['values']['phone_number'];
            		$validationurl[] = 0;
	        		$validationurl[] = 1;
	        		$validationurl[] = $form_state['values']['password'];
					$validationurl[] = $form_state['values']['ivr_passcode'];
			        $validationurl[] = $form_state['values']['ivr_number'];

			        // prepare tokens for email and page
	            	$tokens = teligence_cart_tokens();
				    $tokens['tokens']['[url]'] = url('cart/validate-campaign/' . implode(',', $validationurl), array ('absolute'=>true));
				    $tokens['tokens']['[url]'] = l(urldecode($tokens['tokens']['[url]']), $tokens['tokens']['[url]']);
				    $tokens['tokens']['[ivr-number]'] = $form_state['values']['ivr_number'];
				    $tokens['tokens']['[ivr-passcode]'] = $form_state['values']['ivr_passcode'];
				    $tokens['tokens']['[web-password]'] = $form_state['values']['password'];
				    $tokens['tokens']['[user-email]'] = $form_state['values']['email'];
					$tokens['tokens']['[promo-minutes]'] = variable_get('teligence_cart_free_minutes', 10);
				    drupal_mail('teligence_cart', 'email_campaign', $form_state['values']['email'], language_default(), $tokens);
                    
				    // show success screen
					$_SESSION['teligence_cart_email_campaign_success'] = true;
					$_SESSION['teligence_cart_email_campaign_success_tokens'] = $tokens['tokens'];
                    drupal_goto('cart/email-campaign/success');
                    break;

                case 'WebAcountAlreadyExists':
                    drupal_set_message(variable_get('teligence_cart_error_existing_account', 'You already have an account with us. Did you forget your password?'));
                    drupal_goto('cart/login', array ('email'=>$form_state['values']['email']));
                    break;

                case 'TechnicalError':
                    drupal_set_message(variable_get('teligence_cart_error_existing_account', 'You already have an account with us. Did you forget your password?'), 'error');
                    drupal_goto('cart/login', array ('forgot_email'=>$form_state['values']['email']));
                    break;

                default:
                    drupal_set_message($result['debug']);
                    break;
        	}
        break;
        
        case 'FoundNotEligible':
        case 'NotEligible':
        	drupal_set_message(t("Sorry, our records indicate that you already have an account with us and are not eligible for this promotion. 
				To login to your account click !here", array('!here' => l('here', 'cart/login'))));
        break;

	    default:
	        drupal_set_message($result['debug']);
	    break;
	}
}

/*
 * validate email campaign web account and process free time order
 */
function teligence_cart_validate_email_campaign_account($url_values)
{
	// debug and logging
	// watchdog('emailcampaign', 'url params received by teligence_cart_validate_email_campaign_account <pre>'.print_r($url_values, true).'</pre>');
	
	if(module_exists('teligence_purchase'))
	{
		$MEMBER_CREDENTIALS = variable_get('teligence_purchase_wsdl_membercredentials','');
		$ORDER_MANAGEMENT = variable_get('teligence_purchase_wsdl_ordermanagement','');
	}
	else 
	{
		$MEMBER_CREDENTIALS = variable_get('wsdl_url_3', '');
		$ORDER_MANAGEMENT = variable_get('wsdl_url_5', '');	
	}
	
	$params = new stdClass ();
    $params->validationCode = $url_values[0];
    $result = teligence_cart_soap_call($params, 'ValidateWebAccount', $MEMBER_CREDENTIALS);
    if ($result['result']->ValidateWebAccountResult->ResponseCode == 'Success')
    {
        $params = new stdClass ();
    	$params->emsMembershipId = $url_values[3];
    	$params->email = $url_values[1];
    	$params->freeMinutes = $url_values[2];
    	$result = teligence_cart_soap_call($params, 'ProcessFreeTimeOrder', $ORDER_MANAGEMENT, true);
    	switch($result['result']->ProcessFreeTimeOrderResult->ResponseCode)
        {
            case 'Success':
            	drupal_set_message(t('Your free time order has been processed.'));
		        
		        // set contact permissions and log user in
		        if(count($url_values))
		        {    			
		    		$vals['storage']['ani'] = $url_values[4];
					$vals['storage']['email'] = $url_values[1];
					$vals['values']['channels']['sms'] = $url_values[5];
					$vals['values']['channels']['email'] = $url_values[6];
		            teligence_cart_contact_perm_form_submit(array(), $vals);
					array_pop($_SESSION['messages']['status']);
		    	}
				
				if(module_exists('teligence_purchase'))
				{
					// load functions definition 
					module_load_include('inc', 'teligence_purchase', 'teligence_purchase-pages');
					
					// sign users in automatically behind the scenes
					$form_state['values']['email'] = $url_values[1];
	    			$form_state['values']['password'] = trim($url_values[7]);
					$params = new stdClass ();
				    $params->email = $form_state['values']['email'];
				    $params->password = $form_state['values']['password'];
				    $params->ivrBrandId = variable_get('teligence_purchase_brandid', 1);
				    $result = teligence_purchase_soap_call($params, 'SignIn', variable_get('teligence_purchase_wsdl_membercredentials',''));
					switch($result->SignInResult->ResponseCode)
					{
						case 'Success':
							// login user
							global $user;
							
							// load or create new user and then create session
							$form_state['WebActiveMemberships'] = $result->SignInResult->WebActiveMemberships;
							$user = teligence_purchase_drupaluser($form_state);
							
							// log event
							watchdog('teligence_purchase', 'Session opened for %name.', array ('%name'=>$user->name));
						            
							// Regenerate the session ID to prevent against session fixation attacks.
						    sess_regenerate();
							
							// save values in the session
							$sessionValues = new stdClass();
							$sessionValues->WebActiveMemberships = $result->SignInResult->WebActiveMemberships;
							$sessionValues->email = $form_state['values']['email'];
							$sessionValues->password =  $form_state['values']['password'];
							$sessionValues->WebMemberId = $result->SignInResult->WebMemberId;
							$sessionValues->EmsMemberId = $result->SignInResult->EmsMemberId;
							teligence_purchase_setsessionvalues($sessionValues,TRUE);
							
							// message to user
							drupal_set_message(t('Successful sign-in.'));
							break;
							
						case 'Failure':
							drupal_set_message(t('Email & Password combination is NOT correct.'), 'error');
							break;
							
						case 'NotValidated':
							// provide link to send validation email
							$_SESSION['emailValidateAccount']['email'] = $form_state['values']['email'];
							$_SESSION['emailValidateAccount']['password'] = $form_state['values']['password'];
							drupal_set_message(t('This email address is already registered with us but has not been validated yet.'), 'warning');
							drupal_set_message(t('Please !clickhere to receive a validation email message.', 
								array('!clickhere' => l(t('click here'), 'cart/send-validation-email/' . 
								$result->SignInResult->ValidationCode))), 'warning');
							break;
						
						default:
							drupal_set_message(t('!error', array('!error' => $result->SignInResult->ErrMsg)), 'error');
							break;
					}
					
					// link ivr account to web account
	    			$form_state['values']['passcode'] = $url_values[8];
					$form_state['values']['membershipnumber'] = $url_values[9];	
					teligence_purchase_linkivrtoweb_form_submit(array(), $form_state);

					// redirect to web profile page
					drupal_goto('cart/profile');
				}
            break;
            case 'NotEligible':
           		drupal_set_message(t("Sorry, our records indicate that are not eligible for this promotion.")); 
            break;
            case 'RtmAddTimeFailure':
            	drupal_set_message(t("The system couldn't add free minutes to your account."));
            default:
				drupal_set_message($result['debug']);
            break;
        }
    } 
    else
    {
        drupal_set_message(t('It looks like your account was activated and your free time order was processed already.'));
    }
    
    drupal_goto('cart/login');
}

/*
 * show success message to users of email-campaign form
 */
function teligence_cart_emailcampaign_success()
{
	if(isset($_SESSION['teligence_cart_email_campaign_success']) || user_access('administer cart settings'))
	{
		unset($_SESSION['teligence_cart_email_campaign_success']);
		$tokens = $_SESSION['teligence_cart_email_campaign_success_tokens'];
		unset($_SESSION['teligence_cart_email_campaign_success_tokens']);
		return str_replace(array_keys($tokens), array_values($tokens), variable_get('teligence_cart_error_new_account_email_campaign_subject', ''));
	}
	else
	{
		drupal_goto();
	}
}