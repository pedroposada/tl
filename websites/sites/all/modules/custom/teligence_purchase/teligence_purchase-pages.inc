<?php

/*****************************
 * sign in form
 */
function teligence_purchase_signin_form($form_state)
{
	$form['email'] = array(
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
		'#description' => t('Password must be at least 6 characters long.'),
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
	
	return $form;
}
function teligence_purchase_signin_form_validate($form, &$form_state)
{
	
}
function teligence_purchase_signin_form_submit($form, &$form_state)
{
	$form_state['values']['email'] = trim($form_state['values']['email']);
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
			
			// set cookie to remember user
			if($form_state['values']['keep'])
				setcookie('keepMeLoggedIn',serialize($form_state),(time()+60*60*24*30),"/",str_replace(array('www','secure'),'',$_SERVER['HTTP_HOST']),0);
				// setcookie('keepMeLoggedIn',serialize($form_state),(time()+60*60*24*30),"/",$_SERVER['HTTP_HOST'],0);
			
			// message to user
			drupal_set_message(t('Successful sign-in.'));
			
			// redirect to web profile page
			drupal_goto('cart/profile');
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
}


/**************************************************
 * forgot email form
 */
function teligence_purchase_forgotemail_form($form_state)
{
	$form['membershipnumber'] = array(
		'#type' => 'textfield',
		'#title' => t('Membership Number'),
		'#required' => true,
		'#pre_render' => array('teligence_purchase_membershipnumber_prerender'),
		'#element_validate' => array('teligence_purchase_validate_membershipnumber'),
		'#description' => t('Membership number must be exactly 5 characters long.'),
	);
	$form['passcode'] = array(
		'#type' => 'password',
		'#title' => t('Passcode'),
		'#required' => true,
		'#pre_render' => array('teligence_purchase_passcode_prerender'),
		'#element_validate' => array('teligence_purchase_validate_passcode'),
		'#description' => t('Passcode must be exactly 4 characters long.'),
	);
	
	$form['signin'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
		'#pre_render' => array('teligence_purchase_button_prerender'),
	);
	
	return $form;
}
function teligence_purchase_forgotemail_form_validate($form, &$form_state)
{
	
}
function teligence_purchase_forgotemail_form_submit($form, &$form_state)
{
	$params = new stdClass ();
    $params->ivrBrandId = variable_get('teligence_purchase_brandid', 1);
    $params->ivrMembershipNumber = $form_state['values']['membershipnumber'];
    $params->ivrPasscode = $form_state['values']['passcode'];
    $result = teligence_purchase_soap_call($params, 'ForgotEmail', variable_get('teligence_purchase_wsdl_membercredentials',''));
	switch($result->ForgotEmailResult->ResponseCode)
	{
		case 'Success':
			drupal_set_message(t('We found you: %email', array('%email' => $result->ForgotEmailResult->Email)));
			break;
			
		case 'NotFound':
			drupal_set_message(t('We could not find you in our system.'), 'warning');
			drupal_set_message(t('!pleasecall', array('!pleasecall' => variable_get('teligence_purchase_customerservice', 'Please call customer service at 1-800-984-6889'))), 'warning');
			break;
			
		case 'FoundExpired':
			drupal_set_message(t('Looks like your account expired.'), 'warning');
			drupal_set_message(t('!pleasecall', array('!pleasecall' => variable_get('teligence_purchase_customerservice', 'Please call customer service at 1-800-984-6889'))), 'warning');
			break;
			
		case 'FoundMultipleMatch':
			drupal_set_message(t('We found multiple email addresses registered with your account.'), 'warning');
			drupal_set_message(t('!pleasecall', array('!pleasecall' => variable_get('teligence_purchase_customerservice', 'Please call customer service at 1-800-984-6889'))), 'warning');
			break;
			
		default:
			drupal_set_message(t('!error', array('!error' => $result->ForgotEmailResult->ErrMsg)), 'error');
			break;
	}
}


/**************************************
 * forgot password form
 */
function teligence_purchase_forgotpassword_form($form_state)
{
	$form['email'] = array(
		'#type' => 'textfield',
		'#title' => t('Email'),
		'#required' => true,
		'#pre_render' => array('teligence_purchase_email_prerender'),
		'#element_validate' => array('teligence_purchase_validate_email'),
	);
	
	$form['signin'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
		'#pre_render' => array('teligence_purchase_button_prerender'),
	);
	
	return $form;
}
function teligence_purchase_forgotpassword_form_validate($form, &$form_state)
{
	
}
function teligence_purchase_forgotpassword_form_submit($form, &$form_state)
{
	$form_state['values']['email'] = trim($form_state['values']['email']);
	$params = new stdClass ();
    $params->email = $form_state['values']['email'];
    $params->ivrBrandId = variable_get('teligence_purchase_brandid', 1);
    $result = teligence_purchase_soap_call($params, 'GetPasswordResetId', variable_get('teligence_purchase_wsdl_membercredentials',''));
	switch($result->GetPasswordResetIdResult->ResponseCode)
	{
		case 'Success':
			$tokens = teligence_purchase_tokens('emailPasswordRecovery');
			$tokens['[url]'] = url('cart/password-reset/' . $result->GetPasswordResetIdResult->PasswordResetId, array('absolute' => TRUE));
			drupal_mail('teligence_purchase', 'emailPasswordRecovery', $form_state['values']['email'], language_default(), $tokens);
			drupal_set_message(t('Email with password reset link was sent successfully.'));
			break;
			
		case 'Failure':
			drupal_set_message(t('Your email address was not recognized.'), 'error');
			break;
					
		default:
			drupal_set_message(t('!error', array('!error' => $result->GetPasswordResetIdResult->ErrMsg)), 'error');
			break;
	}
}


/*************************************
 * reset password form
 */
function teligence_purchase_resetpassword_form($form_state, $PasswordResetId = null)
{	
	$form['password'] = array(
		'#type' => 'password',
		'#title' => t('New Password'),
		'#required' => true,
		'#pre_render' => array('teligence_purchase_password_prerender'),
		'#element_validate' => array('teligence_purchase_validate_password'),
		'#description' => t('Password must be at least 6 characters long.'),
	);
	$form['confirm'] = array(
		'#type' => 'password',
		'#title' => t('Confirm Password'),
		'#required' => true,
		'#pre_render' => array('teligence_purchase_password_prerender'),
		'#description' => t('Password must be at least 6 characters long.'),
	);
	$form['PasswordResetId'] = array(
		'#type' => 'hidden',
		'#default_value' => $PasswordResetId,
	);
	
	$form['signup'] = array(
		'#type' => 'submit',
		'#value' => t('Reset Password'),
		'#pre_render' => array('teligence_purchase_button_prerender'),
	);
	
	return $form;
}
function teligence_purchase_resetpassword_form_validate($form, &$form_state)
{
	if($form_state['values']['password'] <> $form_state['values']['confirm'])
	{
		form_error($form['password'], t('Passwords do not match.'));
		form_error($form['confirm'], t('Passwords do not match.'));
		array_pop($_SESSION['messages']['error']);
	}
}
function teligence_purchase_resetpassword_form_submit($form, &$form_state)
{
	$params = new stdClass ();
    $params->passwordResetId = $form_state['values']['PasswordResetId'];
    $params->password = $form_state['values']['password'];
    $params->ivrBrandId = variable_get('teligence_purchase_brandid', 1);
    $result = teligence_purchase_soap_call($params, 'ResetPassword', variable_get('teligence_purchase_wsdl_membercredentials',''));
	switch($result->ResetPasswordResult->ResponseCode)
	{
		case 'Success':
			drupal_set_message(t('Your password was reset successfully.'));
			drupal_goto('cart/login');
			break;
			
		case 'Failure':
			// TODO: where to redirect the user and what to output on the page
		
			drupal_set_message(t('Your password could not be reset.'), 'error');
			break;
					
		default:
			drupal_set_message(t('!error', array('!error' => $result->ResetPasswordResult->ErrMsg)), 'error');
			break;
	}
}


/************************************
 * sign-up form
 */
function teligence_purchase_signup_form($form_state)
{
	$form['email'] = array(
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
		'#description' => t('Password must be at least 6 characters long.'),
	);
	$form['confirm'] = array(
		'#type' => 'password',
		'#title' => t('Confirm Password'),
		'#required' => true,
		'#pre_render' => array('teligence_purchase_password_prerender'),
		'#description' => t('Password must be at least 6 characters long.'),
	);
	$form['gender'] = array(
		'#type' => 'radios',
		'#title' => t('Gender'),
		'#options' => array(
			'M' => t('Male'),
			'F' => t('Female'), 
		),
		'#required' => true,
	);
	
	#************** captcha field
	$form['captcha'] = array(
		'#type' => 'fieldset',
		'#pre_render' => array('teligence_purchase_captcha_prerender'),
	);
	$form['captcha']['CaptchaImage'] = array(
		'#type' => 'item',
		'#title' => t('Enter these numbers'),
		'#attributes' => array('id' => 'captchaImage'),
	);
	$form['captcha']['CaptchaValue'] = array(
		'#type' => 'textfield',
		'#size' => 3,
		'#maxlength' => 3,
		'#title' => t('in this box'),
		'#element_validate' => array('teligence_purchase_validate_captcha'),
	);
	$form['captcha']['CaptchaHash'] = array(
		'#type' => 'hidden',
		'#name' => 'CaptchaHash',
	);
	$form['captcha']['CaptchaID'] = array(
		'#type' => 'hidden',
		'#name' => 'CaptchaID',
	);
	
	$form['signup'] = array(
		'#type' => 'submit',
		'#value' => t('Sign Up'),
		'#pre_render' => array('teligence_purchase_button_prerender'),
	);
	
	return $form;
}
function teligence_purchase_signup_form_validate($form, &$form_state)
{
	// debug logging	
	if(variable_get('teligence_purchase_debug', 0))
		watchdog('debug','form_validate: !form',array('!form'=>check_plain(print_r($form_state,1))));
	
	if($form_state['values']['password'] <> $form_state['values']['confirm'])
	{
		form_error($form['password'], t('Passwords do not match.'));
		form_error($form['confirm'], t('Passwords do not match.'));
		array_pop($_SESSION['messages']['error']);
	}
	
	if(!in_array($form_state['values']['gender'], array('M','F')))
	{
		form_error($form['gender'], t('Invalid gender.'));
	}
}
function teligence_purchase_signup_form_submit($form, &$form_state)
{
	// debug logging	
	if(variable_get('teligence_purchase_debug', 0))
		watchdog('debug','form_submit: !form',array('!form'=>check_plain(print_r($form_state,1))));
	
	$params = new stdClass ();
    $params->email = $form_state['values']['email'];
    $params->password = $form_state['values']['password'];
    $params->ivrBrandId = variable_get('teligence_purchase_brandid', 1);
    $params->gender = $form_state['values']['gender'];
    $result = teligence_purchase_soap_call($params, 'SignUp', variable_get('teligence_purchase_wsdl_membercredentials',''));
	switch($result->SignUpResult->ResponseCode)
	{
		case 'Success':
			// send validation email
			$tokens = teligence_purchase_tokens('emailValidateAccount');
			$tokens['[email]'] = $form_state['values']['email'];
			$tokens['[password]'] = $form_state['values']['password'];
			$tokens['[url]'] = url('cart/validate-web-account/' . 
				$result->SignUpResult->ValidationCode . '/' . 
				$form_state['values']['email'] . '/' . 
				$form_state['values']['password'], array('absolute' => TRUE)
			);
			drupal_mail('teligence_purchase', 'emailValidateAccount', $form_state['values']['email'], language_default(), $tokens);
			drupal_set_message(t('Thanks for signing up with us. Please check your emails to validate your account.'));
			break;
			
		case 'WebAcountAlreadyExistsValidated':
			drupal_set_message(t('This email address is already registered with us. Please !signin', 
				array('!signin' => l(t('Sign-In'), 'cart/login'))), 'warning');
			break;
			
		case 'WebAcountAlreadyExistsNotValidated':
			$_SESSION['emailValidateAccount']['email'] = $form_state['values']['email'];
			$_SESSION['emailValidateAccount']['password'] = $form_state['values']['password'];
			drupal_set_message(t('This email address is already registered with us but has not been validated yet. Please !clickhere to receive a validation email message.', 
				array('!clickhere' => l(t('click here'), 'cart/send-validation-email/' . 
				$result->SignUpResult->ValidationCode))), 'warning');
			break;
			
		default:
			drupal_set_message(t('!error', array('!error' => $result->SignUpResult->ErrMsg)), 'error');
			break;
	}
}


/***************************************
 * profile form
 */
function teligence_purchase_profile_form($form_state)
{
	// debug logging	
	if(variable_get('teligence_purchase_debug', 0))
		watchdog('debug',"SESSION['localization']: @loc",array('@loc'=>print_r($_SESSION['localization'],TRUE)));
	
	if(!isset($form_state['storage']['webprofile']))
	{
		teligence_purchase_profile_form_submit($form, $form_state);
	}
	
	$form['firstname'] = array(
		'#type' => 'textfield',
		'#title' => t('First Name'),
		'#default_value' => $form_state['storage']['webprofile']->FirstName,
	);
	$form['lastname'] = array(
		'#type' => 'textfield',
		'#title' => t('Last Name'),
		'#default_value' => $form_state['storage']['webprofile']->LastName,
	);
	if($rawdate = $form_state['storage']['webprofile']->BirthDateYyyyMmDd)
	{
		$yyyy = substr($rawdate, 0, 4);
		$mm = substr($rawdate, 4, 2);
		$dd = substr($rawdate, 6, 2);
	}
	$form['dateofbirth'] = array(
		'#type' => 'textfield',
		'#title' => t('Date of Birth'),
		'#pre_render' => array('teligence_purchase_date_prerender'),
		'#default_value' => strlen("$mm/$dd/$yyyy") > 2 ? "$mm/$dd/$yyyy" : "",
		'#description' => t('Enter date in the form of mm/dd/yyyy'),
		'#element_validate'=>array('teligence_purchase_validate_dateofbirth'),
		'#field_suffix' => theme('image', drupal_get_path('module', 'teligence_purchase').'/images/calendar.gif',t('click to pick a date'),t('click to pick a date'),array('id' => 'datePickerIcon')),
	);
	list($npa,$nxx,$number) = teligence_purchase_npanxx($form_state['storage']['webprofile']->HomePhone);
	$form['homephone'] = array(
		'#type' => 'textfield',
		'#title' => t('Home Phone'),
		'#pre_render' => array('teligence_purchase_phone_prerender'),
		'#default_value' => "($npa) $nxx-$number",
		'#description' => t('Enter phone in the form of (xxx) xxx-xxxx'),
	);
	list($npa,$nxx,$number) = teligence_purchase_npanxx($form_state['storage']['webprofile']->CellPhone);
	$form['cellphone'] = array(
		'#type' => 'textfield',
		'#title' => t('Cell Phone'),
		'#pre_render' => array('teligence_purchase_phone_prerender'),
		'#default_value' => "($npa) $nxx-$number",
		'#description' => t('Enter phone in the form of (xxx) xxx-xxxx'),
	);	
	$options = array(
		'USA' => teligence_purchase_valuelistoptions(file_get_contents(drupal_get_path('module','teligence_purchase').'/states/USA.txt')),
		'Canada' => teligence_purchase_valuelistoptions(file_get_contents(drupal_get_path('module','teligence_purchase').'/states/Canada.txt')),
	);	
	$form['stateprovince'] = array(
		'#type' => 'select',
		'#title' => t('State/Province'),
		'#options' => $options,
		'#default_value' => strlen($form_state['storage']['webprofile']->Region) ? trim($form_state['storage']['webprofile']->Region) : trim($_SESSION['localization']->Region),
	);	
	$form['city'] = array(
		'#type' => 'textfield',
		'#title' => t('City'),
		'#default_value' => $form_state['storage']['webprofile']->City ? $form_state['storage']['webprofile']->City : $_SESSION['localization']->City,
	);	
	
	$form['save'] = array(
		'#type' => 'submit',
		'#value' => t('Save Changes'),
		'#pre_render' => array('teligence_purchase_button_prerender'),
	);
	
	return $form;
}
function teligence_purchase_profile_form_validate($form, &$form_state)
{
	
}
function teligence_purchase_profile_form_submit($form, &$form_state)
{
	// save values
	if($form_state['clicked_button']['#id'] == 'edit-save')
	{
		$params = new stdClass ();
	    $params->webMemberId = $_SESSION['WebMemberId'];
	    $params->firstName = $form_state['values']['firstname'];
	    $params->lastName = $form_state['values']['lastname'];
		
		list($mm,$dd,$yyyy) = explode('/', $form_state['values']['dateofbirth']);	    
		$params->birthDateYyyyMmDd = "$yyyy$mm$dd";
	    
	    $params->homePhone = implode('',teligence_purchase_npanxx($form_state['values']['homephone']));
	    $params->cellPhone = implode('',teligence_purchase_npanxx($form_state['values']['cellphone']));
	    $params->region = $form_state['values']['stateprovince'];
	    $params->city = $form_state['values']['city'];
	    $result = teligence_purchase_soap_call($params, 'UpdateWebProfile', variable_get('teligence_purchase_wsdl_membermanagement',''));
		switch($result->UpdateWebProfileResult->ResponseCode)
		{
			case 'Success':
				drupal_set_message(t('Profile information was saved successfully.'));
				if(isset($_REQUEST['destination']))
				{
					drupal_goto($_REQUEST['destination']);
				}
				break;
				
			case 'Failure':
				drupal_set_message(t('Profile information could not be saved.'), 'error');
				drupal_set_message(t('!pleasecall', array('!pleasecall' => variable_get('teligence_purchase_customerservice', 'Please call customer service at 1-800-984-6889'))), 'error');
				break;
				
			default:
				drupal_set_message(t('!error', array('!error' => $result->UpdateWebProfileResult->ErrMsg)), 'error');
				break;
		}
	}
	
	// get values
	$params = new stdClass ();
	$params->webMemberId = $_SESSION['WebMemberId'];
	$result = teligence_purchase_soap_call($params, 'GetWebProfile', variable_get('teligence_purchase_wsdl_membermanagement',''));
	switch($result->GetWebProfileResult->ResponseCode)
	{
		case 'Success':
			$form_state['storage']['webprofile'] = $result->GetWebProfileResult;
			break;
			
		default:
			drupal_set_message(t('!error', array('!error' => $result->GetWebProfileResult->ErrMsg)), 'error');
			break;
	}
}


/*************************************
 * change email address form
 */
function teligence_purchase_newemail_form($form_state)
{
	$form['newemail'] = array(
		'#type' => 'textfield',
		'#title' => t('New Email Address'),
		'#required' => true,
		'#pre_render' => array('teligence_purchase_email_prerender'),
		'#description' => t('Enter email in the form of xxxx@xxx.xxx'),
	);
	$form['password'] = array(
		'#type' => 'password',
		'#title' => t('Current Password'),
		'#required' => true,
		'#pre_render' => array('teligence_purchase_password_prerender'),
		'#description' => t('Password must be at least 6 characters long.'),
	);
	
	$form['changeemail'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
		'#pre_render' => array('teligence_purchase_button_prerender'),
	);
	
	return $form;
}
function teligence_purchase_newemail_form_validate($form, &$form_state)
{
	if(md5($form_state['values']['password']) <> $_SESSION['WebMemberPassword'])
	{
		form_error($form['password'], t('Password is not correct.'));
	}
}
function teligence_purchase_newemail_form_submit($form, &$form_state)
{
	$params = new stdClass ();
    $params->ivrBrandId = variable_get('teligence_purchase_brandid', 1);
    $params->webMemberId = $_SESSION['WebMemberId'];
    $params->newEmail = $form_state['values']['newemail'];
	$result = teligence_purchase_soap_call($params, 'GetEmailResetId', variable_get('teligence_purchase_wsdl_membercredentials',''));
	switch($result->GetEmailResetIdResult->ResponseCode)
	{
		case 'Success':
			$tokens = teligence_purchase_tokens('emailResetEmailId');
			$tokens['[newemail]'] =  $form_state['values']['newemail'];
			$tokens['[url]'] = url(
				'cart/reset-email/' . 
				$result->GetEmailResetIdResult->EmailResetId . '/' . 
				$tokens['[newemail]'],
				array('absolute' => TRUE)
			);
			drupal_mail('teligence_purchase', 'emailResetEmailId', $tokens['[newemail]'], language_default(), $tokens);
			drupal_set_message(t('Please check your emails to validate your new email address.'));
			break;
		
		case 'EmailAlreadyExists':
			drupal_set_message(t('This email address is already registered with us. Please try a different one.'),'warning');
			break;

		default:
			drupal_set_message(t('!error', array('!error' => $result->GetEmailResetIdResult->ErrMsg)), 'error');
			break;
	}
}


/**********************************
 * change web password form
 */
function teligence_purchase_changepassword_form($form_state)
{
    $form['current_password'] = array (
	    '#type'=>'password',
	    '#title'=>t('Current Password'),
	    '#required'=>true,
	    '#pre_render' => array('teligence_purchase_password_prerender'),
	    '#description' => t('Password must be at least 6 characters long.'),
    );
    $form['password'] = array (
	    '#type'=>'password',
	    '#title'=>t('New Password'),
	    '#required'=>true,
	    '#pre_render' => array('teligence_purchase_password_prerender'),
	    '#description' => t('Password must be at least 6 characters long.'),
    );
    $form['confirm'] = array (
	    '#type'=>'password',
	    '#title'=>t('Confirm Password'),
	    '#required'=>true,
	    '#pre_render' => array('teligence_purchase_password_prerender'),
	    '#description' => t('Password must be at least 6 characters long.'),
    );
    $form['submit'] = array (
	    '#type'=>'submit',
	    '#value'=>t('Change Password'),
	    '#pre_render' => array('teligence_purchase_button_prerender'),
    );

    return $form;
}
function teligence_purchase_changepassword_form_validate($form, &$form_state)
{
	if(md5($form_state['values']['current_password']) <> $_SESSION['WebMemberPassword'])
	{
		form_error($form['current_password'], t('Current password is not correct.'));
	}
	if($form_state['values']['password'] <> $form_state['values']['confirm'])
	{
		form_error($form['password'], t('Passwords do not match.'));
		form_error($form['confirm'], t('Passwords do not match.'));
		array_pop($_SESSION['messages']['error']);
	}
}
function teligence_purchase_changepassword_form_submit($form, &$form_state)
{
	$params = new stdClass ();
    $params->webMemberId = $_SESSION['WebMemberId'];	
    $params->newPassword = $form_state['values']['password'];	
	$result = teligence_purchase_soap_call($params, 'ChangePassword', variable_get('teligence_purchase_wsdl_membercredentials',''));
	switch($result->ChangePasswordResult->ResponseCode)
	{
		case 'Success':
			$_SESSION['WebMemberPassword'] = md5($form_state['values']['password']);
			drupal_set_message(t('Your password was changed successfully.'));
			break;
			
		case 'Failure':
			drupal_set_message(t('Your password could not be changed.'), 'error');
			drupal_set_message(t('!pleasecall', array('!pleasecall' => variable_get('teligence_purchase_customerservice', 'Please call customer service at 1-800-984-6889'))), 'error');
			break;
			
		default:
			drupal_set_message(t('!error', array('!error' => $result->ChangePasswordResult->ErrMsg)), 'error');
			break;
	}
}


/*************************************
 * link IVR to web account form
 */
function teligence_purchase_linkivrtoweb_form($form_state)
{
	$form['membershipnumber'] = array(
		'#type' => 'textfield',
		'#title' => t('Membership Number'),
		'#required' => true,
		'#pre_render' => array('teligence_purchase_membershipnumber_prerender'),
		'#element_validate' => array('teligence_purchase_validate_membershipnumber'),
		'#description' => t('Membership number must be exactly 5 characters long.'),
	);
	$form['passcode'] = array(
		'#type' => 'password',
		'#title' => t('Passcode'),
		'#required' => true,
		'#pre_render' => array('teligence_purchase_passcode_prerender'),
		'#description' => t('Passcode must be exactly 4 characters long.'),
	);
	
	$form['signin'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
		'#pre_render' => array('teligence_purchase_button_prerender'),
	);
	
	return $form;
}
function teligence_purchase_linkivrtoweb_form_validate($form, &$form_state)
{
	
}
function teligence_purchase_linkivrtoweb_form_submit($form, &$form_state)
{
	$params = new stdClass ();
    $params->ivrBrandId = variable_get('teligence_purchase_brandid', 1);
    $params->webMemberId = $_SESSION['WebMemberId'];	
    $params->ivrMembershipNumber = $form_state['values']['membershipnumber'];	
    $params->ivrPasscode = $form_state['values']['passcode'];	
	$result = teligence_purchase_soap_call($params, 'LinkIvrMembership', variable_get('teligence_purchase_wsdl_membermanagement',''));
	switch($result->LinkIvrMembershipResult->ResponseCode)
	{
		case 'Success':
			// add drupal role 'ivr_user' to this user
			// load user
			global $user;
			
			// update drupal user
			$form_state['WebActiveMemberships'] = $result->LinkIvrMembershipResult->WebActiveMemberships;
			// $form_state['values']['email'] = $_SESSION['WebMemberEmail'];
			$form_state['values']['email'] = $user->mail;
			$user = teligence_purchase_drupaluser($form_state);
			
			// save values in the session
			$sessionValues = $result->LinkIvrMembershipResult;
			teligence_purchase_setsessionvalues($sessionValues);
			
			// show message to user
			drupal_set_message(t('Your accounts were linked successfully.'));
			break;
			
		case 'NotFound':
			drupal_set_message(t('Your account was not found.'), 'error');
			drupal_set_message(t('!pleasecall', array('!pleasecall' => variable_get('teligence_purchase_customerservice', 'Please call customer service at 1-800-984-6889'))), 'error');
			break;
		case 'FoundExpired':
			drupal_set_message(t('Your account expired.'), 'error');
			drupal_set_message(t('!pleasecall', array('!pleasecall' => variable_get('teligence_purchase_customerservice', 'Please call customer service at 1-800-984-6889'))), 'error');
			break;
		case 'FoundMultiple':
		case 'FoundMultipleMatch': 
			drupal_set_message(t('Your accounts could not be linked.'), 'error');
			drupal_set_message(t('!pleasecall', array('!pleasecall' => variable_get('teligence_purchase_customerservice', 'Please call customer service at 1-800-984-6889'))), 'error');
			break;
		case 'FoundAlreadyLinked':
		case 'FoundLinkedWithDifferentWebMember':
			drupal_set_message(t('Your accounts are already linked.'), 'error');
			drupal_set_message(t('!pleasecall', array('!pleasecall' => variable_get('teligence_purchase_customerservice', 'Please call customer service at 1-800-984-6889'))), 'error');
			break;
			
		default:
			drupal_set_message(t('!error', array('!error' => $result->LinkIvrMembershipResult->ErrMsg)), 'error');
			break;
	}
}


/******************************
 * change passcode form
 */
function teligence_purchase_changepasscode_form($form_state)
{
    $form['passcode_new'] = array (
	    '#type'=>'password',
	    '#title'=>t('New Passcode'),
	    '#required'=>true,
	    '#pre_render' => array('teligence_purchase_passcode_prerender'),
	    '#element_validate' => array('teligence_purchase_validate_passcode'),
	    '#description' => t('Passcode must be exactly 4 characters long.'),
    );
    $form['passcode_confirm'] = array (
	    '#type'=>'password',
	    '#title'=>t('Confirm Passcode'),
	    '#required'=>true,
	    '#pre_render' => array('teligence_purchase_passcode_prerender'),
	    '#element_validate' => array('teligence_purchase_validate_passcode'),
	    '#description' => t('Passcode must be exactly 4 characters long.'),
    );
    $form['submit'] = array (
	    '#type'=>'submit',
	    '#value'=>t('Change Passcode'),
	    '#pre_render' => array('teligence_purchase_button_prerender'),
    );

    return $form;
}
function teligence_purchase_changepasscode_form_validate($form,&$form_state)
{
	if($form_state['values']['passcode_new'] <> $form_state['values']['passcode_confirm'])
	{
		form_error($form['passcode_new'], t('Passcodes do not match.'));
		form_error($form['passcode_confirm'], t('Passcodes do not match.'));
		array_pop($_SESSION['messages']['error']);
	}
}
function teligence_purchase_changepasscode_form_submit($form,&$form_state)
{
	$params = new stdClass ();
	$params->emsMembershipId = $_SESSION['emsMemberships'][$_SESSION['IvrMembershipNumber']]->EmsMembershipId;	
	$params->newIvrPasscode = $form_state['values']['passcode_new'];	
	$result = teligence_purchase_soap_call($params,'UpdateIvrPasscode',variable_get('teligence_purchase_wsdl_ivrrtm',''));
	switch($result->UpdateIvrPasscodeResult->ResponseCode)
	{
		case 'Success':
			$_SESSION['emsMemberships'][$_SESSION['IvrMembershipNumber']]->IvrPasscode = $form_state['values']['passcode_new'];
			drupal_set_message(t('Your passcode was changed successfully.'));
			break;
		
		default:
			drupal_set_message(t('!error',array('!error'=>$result->UpdateIvrPasscodeResult->ErrMsg)),'error');
			break;
	}
}


/***********************************
 * view order history form
 */
function teligence_purchase_orderhistory_form($form_state) 
{
	$form['days'] = array(
		'#type' => 'select',
		'#title' => t('Order History for'),
		'#default_value' => $form_state['storage']['days'],
		'#options' => array(
			10 => 'Last 10 days',
			20 => 'Last 20 days',
			30 => 'Last 30 days',
		),
	);
	$form['button'] = array(
		'#type' => 'submit',
		'#value' => t('View'),
		'#pre_render' => array('teligence_purchase_button_prerender'),
	);
	
	if(!isset($form_state['storage']['orderhistory']))
	{
		teligence_purchase_orderhistory_form_submit($form,$form_state);
	}
	
	$form['list'] = array(
		'#type' => 'item',
		'#title' => t('Order History'),
		'#value' => $form_state['storage']['orderhistory'],
	);
		
	return $form;
}
function teligence_purchase_orderhistory_form_submit($form,&$form_state)
{
	$params = new stdClass ();
    $params->emsMembershipId = $_SESSION['emsMemberships'][$_SESSION['IvrMembershipNumber']]->EmsMembershipId;
    $params->daysOfHistory = ($form_state['values']['days'] ? $form_state['values']['days'] : 10);
    $result = teligence_purchase_soap_call($params, 'GetOrderHistory', variable_get('teligence_purchase_wsdl_membermanagement',''));
	switch ($result->GetOrderHistoryResult->ResponseCode) 
	{	
		case 'Success':
			if(!is_array($result->GetOrderHistoryResult->WebOrders->WebOrder)): 
				$WebOrders = array($result->GetOrderHistoryResult->WebOrders->WebOrder);
			else:
				$WebOrders = $result->GetOrderHistoryResult->WebOrders->WebOrder;
			endif;
			foreach ((array)$WebOrders as $WebOrder) 
			{
				$timestamp = teligence_cart_timestamp($WebOrder->OrderDateTime);
				$rows[] = array(
					'data' => array(
						array('data' => $WebOrder->OrderId),
						array('data' => t(format_date($timestamp,'custom','F')).' '.format_date($timestamp, 'custom', 'j, Y')),
						array('data' => t($WebOrder->OrderStatus)),
						// array('data' => $WebOrder->OrderType),
						array('data' => t($WebOrder->PaymentType)),
						array('data' => $WebOrder->Minutes),
						array('data' => '$'.number_format($WebOrder->AmountCents/100, 2)),
					),
					'class' => 'order-history-item'
				);
			}
			$headers = array(t('Order Id'), t('Date'), t('Order Status'), t('Payment Type'), t('Minutes'), t('Amount'));
			$form_state['storage']['orderhistory'] = theme('table', $headers, $rows, array('id'=>'orderhistoryTable'));			
		break;
		
		case 'NoOrders':
			$form_state['storage']['orderhistory'] = t('No Orders');
		break;
		
		default:
			drupal_set_message(t('!error',array('!error'=>$result->GetOrderHistoryResult->ErrMsg)),'error');
			break;
	};
	
	$form_state['storage']['days'] = $form_state['values']['days'];
	
}


/************************************
 * add new credit card form
 * manage credit cards
 */
function teligence_purchase_addnewcc_form($form_state) 
{
	// $form['cc_info'] = array(
		// '#type' => 'fieldset',
	// );	
	// $form['cc_info']['cc_number'] = array (
    	// '#type'=>'textfield',
    	// '#title'=>t('Card #'),
    	// '#size'=>20,
    	// '#maxlength'=>16,
    // );
	// $form['cc_info']['cc_expiration'] = array (
    	// '#type'=>'date',
    	// '#title'=>t('Expiration Date'),
    	// '#theme' => 'teligence_purchase_ccexpirationdate',
    	// '#description'=>t('Enter expiration date on card'),
    // );
	// $form['cc_info']['add'] = array(
		// '#type' => 'submit',
		// '#value' => t('Add'),
		// '#pre_render' => array('teligence_purchase_button_prerender'),
	// );
	
	if(!isset($form_state['storage']['cclist']))
	{
		teligence_purchase_addnewcc_form_submit($form, $form_state);
	}
	
	if(count($form_state['storage']['cclist']))
	{
		$form['cclist'] = array(
			'#type' => 'fieldset',
			'#theme' => 'teligence_purchase_addnewcclist',
			'#tree' => TRUE,
		);
		foreach((array)$form_state['storage']['cclist'] as $k => $v)
		{
			$form['cclist'][$k]['cc_selected'] = array(
				'#type' => 'checkbox',
				'#default_value' => ($_REQUEST['cc']==$k ? 1 : 0),
			);
			$form['cclist'][$k]['AccountNo'] = array(
				'#type' => 'item',
				'#value' => $v['cc_number'],
			);
			$form['cclist'][$k]['cc_type'] = array(
				'#type' => 'item',
				'#value' => $v['cc_type'],
			);
			$form['cclist'][$k]['ExpiryDateMMYY'] = array(
				'#type' => 'date',
				'#default_value' => $v['cc_date'],
				'#theme' => 'teligence_purchase_ccexpirationdate',
			);
			$form['cclist'][$k]['cc_delete'] = array(
				'#type' => 'item',
				'#value' => l(t('Delete'),'cart/delete-cc/'.$k), 
			);
		}
		$form['update'] = array(
			'#type' => 'submit',
			'#value' => t('Update'),
			'#pre_render' => array('teligence_purchase_button_prerender'),
		);	
	}
	else
	{
		$form['cclist'] = array(
			'#type' => 'fieldset',
			'#value' => t('There are no Credit Cards on file for your account.'),
		);
	}
	
	return $form;
}
function teligence_purchase_addnewcc_form_validate($form, &$form_state) 
{
	if ($form_state['clicked_button']['#id'] == 'edit-add') 
	{
		if (empty($form_state['values']['cc_number'])) 
		{
			form_error($form['cc_info']['cc_number'], t('Credit Card Number is required.'));
		}
		teligence_purchase_validate_expirationdate($form['cc_info']['cc_expiration'], $form_state);
	}
	
	if ($form_state['clicked_button']['#id'] == 'edit-update') 
	{
		foreach ($form_state['values']['cclist'] as $k => $v) 
		{
			if ($form_state['values']['cclist'][$k]['cc_selected']) 
			{
				teligence_purchase_validate_expirationdate($form['cclist'][$k]['ExpiryDateMMYY'], $form_state);
			}
		}
	}
	
}
function teligence_purchase_addnewcc_form_submit($form, &$form_state) 
{
	// add new credit cards
	if ($form_state['clicked_button']['#id'] == 'edit-add') 
	{
		$params = new stdClass ();
	    $params->emsMembershipId = $_SESSION['emsMemberships'][$_SESSION['IvrMembershipNumber']]->EmsMembershipId;
		$params->creditCardNumber = $form_state['values']['cc_number'];
		$params->expiryDateMmYy = 	str_pad ($form_state['values']['cc_expiration']['month'], 2, 0, STR_PAD_LEFT).
									str_pad ($form_state['values']['cc_expiration']['year'], 2, 0, STR_PAD_LEFT);
	    $result = teligence_purchase_soap_call($params, 'AddCreditCard', variable_get('teligence_purchase_wsdl_membermanagement',''));
		switch ($result->AddCreditCardResult->ResponseCode) 
		{
			case 'Success':
				drupal_set_message(t('Credit Card added successfully.'));
				break;
			
			case 'InvalidCreditCardNo':
				form_error($form['cc_info']['cc_number'], t('Invalid credit card number.'));
				break;
			
			case 'MembershipNotFound':
			case 'PaymethodBelongsToOtherMember':
			case 'CanadianNotVerifiedStatus':
			case 'FraudulentPaymethod':
			case 'InactivePaymethod':
			case 'NoAddressForMember':
			case 'TechnicalError':
			default:
				drupal_set_message(t('!error',array('!error'=>$result->AddCreditCardResult->ResponseCode)),'error');
				drupal_set_message(t('!error',array('!error'=>$result->AddCreditCardResult->ErrMsg)),'error');
				break;
		}
	}
	
	// update credit cards
	if ($form_state['clicked_button']['#id'] == 'edit-update') 
	{
		$i = 0;
		foreach ($form_state['values']['cclist'] as $k => $v) 
		{
			if ($form_state['values']['cclist'][$k]['cc_selected']) 
			{
				$params = new stdClass ();
			    $params->paymethodId = $k;
				$params->expiryDateMmYy = 	str_pad($form_state['values']['cclist'][$k]['ExpiryDateMMYY']['month'], 2, 0, STR_PAD_LEFT).
											str_pad ($form_state['values']['cclist'][$k]['ExpiryDateMMYY']['year'], 2, 0, STR_PAD_LEFT);
			    $result = teligence_purchase_soap_call($params, 'UpdateCreditCardExpiryDate',variable_get('teligence_purchase_wsdl_membermanagement',''));
				switch ($result->UpdateCreditCardExpiryDateResult->ResponseCode) 
				{
					case 'Success':
						drupal_set_message(t('Credit Card !num updated successfully.', array('!num' => $form['cclist'][$k]['AccountNo']['#value'])));
						break;
					
					case 'InvalidExpiryDate':
						form_error($form['cclist'][$k]['ExpiryDateMMYY'], 'Invalid Expiry Date');
						break;
					
					default:
						drupal_set_message(t('!error',array('!error'=>$result->UpdateCreditCardExpiryDateResult->ErrMsg)),'error');
						break;
				};
				$i++;
			}
		}
		($i ? NULL : drupal_set_message(t('Please select a credit card from the list.'), 'warning'));
		
		if(isset($_REQUEST['destination']))
		{
			drupal_goto($_REQUEST['destination']);
		}
	}
	
	// load list of credit cards
	$params = new stdClass ();
    $params->emsMembershipId = $_SESSION['emsMemberships'][$_SESSION['IvrMembershipNumber']]->EmsMembershipId;
	$result = teligence_purchase_soap_call($params,'GetPaymethods',variable_get('teligence_purchase_wsdl_membermanagement',''));
	switch ($result->GetPaymethodsResult->ResponseCode) 
	{
		case 'Success':
			if(!is_array($result->GetPaymethodsResult->WebPaymethods->WebPaymethod)): 
				$WebPaymethods = array($result->GetPaymethodsResult->WebPaymethods->WebPaymethod);
			else:
				$WebPaymethods = $result->GetPaymethodsResult->WebPaymethods->WebPaymethod;
			endif;
			foreach ((array)$WebPaymethods as $WebPaymethod) 
			{
				$form_state['storage']['cclist'][$WebPaymethod->PaymethodId] = array(
					'cc_number' => $WebPaymethod->AccountNo,
					'cc_type' => $WebPaymethod->PaymethodType,
					'cc_date' => array('year' => (int)substr($WebPaymethod->ExpiryDateMMYY,2,2), 'month' => (int)substr($WebPaymethod->ExpiryDateMMYY,0,2), 'day' => 1),
					'cc_expired' => $WebPaymethod->IsExpired,
				);
			}
			break;
			
		default:
			drupal_set_message(t('!error',array('!error'=>$result->GetPaymethodsResult->ErrMsg)),'error');
			break;	
	}
}



/******************************
 * manage subscriptions form
 */
function teligence_purchase_subscriptions_form($form_state)
{
	if(!isset($form_state['storage']['perms']))
	{
		teligence_purchase_subscriptions_form_submit($form,$form_state);
	}
	
	$form['perm_group']['channels'] = array(
	  '#type' => 'checkboxes', 
	  '#title' => t('Contact Channels'),
	  '#options' => array(
		'sms' => t('Contact me via SMS'), 
		'email' => t('Contact me via Email'),
	  ),
	  '#description' => t('Allows us to contact you via the channels selected above.'),
	  '#default_value' => array(
		$form_state['storage']['perms']['email'] ? 'email' : '',
		$form_state['storage']['perms']['sms'] ? 'sms' : '',
	  ),
	);
	
	// if(strlen($form_state['storage']['webprofile']->CellPhone))
	// {
		$form['ani'] = array(
			'#type' => 'hidden',
			'#default_value' => $form_state['storage']['webprofile']->CellPhone,
		);
		$form['update'] = array(
			'#type' => 'submit',
			'#value' => t('Update'),
			'#pre_render' => array('teligence_purchase_button_prerender'),
		);
	// }	
	
	return $form;
}
function teligence_purchase_subscriptions_form_validate($form,&$form_state)
{
	if ($form_state['clicked_button']['#id'] == 'edit-update') 
	{
		if(empty($form_state['values']['ani']))
		{
			form_error($form, t('We cannot process your request. Please fill out your !profile first.',array('!profile' => l(t('profile'),'cart/profile'))));
		}
	}
}
function teligence_purchase_subscriptions_form_submit($form,&$form_state)
{
	// update permissions
	if ($form_state['clicked_button']['#id'] == 'edit-update') 
	{
		$params = new stdClass ();
	    $params->ivrBrandId = variable_get('teligence_purchase_brandid', 1);
		$params->ani = $form_state['values']['ani'];
		$params->email = $_SESSION['WebMemberEmail'];
		$params->aniTelemarketingPtc = $params->aniNotificationsPtc = true;
		$params->emailNotificationsPtc = true;
		$params->aniSmsPtc = ($form_state['values']['channels']['sms'] ? true : false);
		$params->emailPtc = ($form_state['values']['channels']['email'] ? true : false);
		$result = teligence_purchase_soap_call($params, 'UpdatePermissionToContact', variable_get('teligence_purchase_wsdl_membermanagement',''));
		switch ($result->UpdatePermissionToContactResult->ResponseCode) 
		{
			case 'Success':
				drupal_set_message(t('Contact Permissions were set successfully.'));
				break;
			
			default:
				drupal_set_message(t('!error',array('!error'=>$result->UpdatePermissionToContactResult->ErrMsg)),'error');
				break;
		}
	}
	
	teligence_purchase_profile_form_submit($form, $form_state);
	if(strlen($form_state['storage']['webprofile']->CellPhone))
	{
		// load permissions
		$params = new stdClass ();
	    $params->ivrBrandId = variable_get('teligence_purchase_brandid', 1);
		$params->ani = $form_state['storage']['webprofile']->CellPhone;
		$params->email = $_SESSION['WebMemberEmail'];
		$result = teligence_purchase_soap_call($params, 'GetPermissionToContact', variable_get('teligence_purchase_wsdl_membermanagement',''));
		switch ($result->GetPermissionToContactResult->ResponseCode) 
		{
			case 'Success':
				$form_state['storage']['perms']['email'] = $result->GetPermissionToContactResult->EmailPtc;
				$form_state['storage']['perms']['sms'] = $result->GetPermissionToContactResult->AniSmsPtc;
				break;
		
			default:
				drupal_set_message(t('!error',array('!error'=>$result->GetPermissionToContactResult->ErrMsg)),'error');
				break;
		}
	}
	else
	{
		drupal_set_message(t('Please provide us your !cell first.',array('!cell' => l(t('Cell Phone number'),'cart/profile',array('query' => array('destination' => $_GET['q']))))),'error');	
	}
}