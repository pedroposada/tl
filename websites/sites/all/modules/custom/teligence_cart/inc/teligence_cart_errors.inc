<?php
/*
 * cart errors messages form
 */
function teligence_cart_errors_form($form_state)
{   
	$form['#pre_render'] = array('teligence_cart_errors_form_pre_render');
	
    $form['teligence_cart_button_processing'] = array (
    	'#type'=>'textfield',
    	'#title'=>t('Text to show in button when clicked'),
    	'#default_value'=>variable_get('teligence_cart_button_processing', 'Processing...'),
    );
    $form['teligence_cart_error_link_expired'] = array (
    	'#type'=>'textfield',
    	'#title'=>t('Validation link expired'),
    	'#default_value'=>variable_get('teligence_cart_error_link_expired', 'Your link expired.'),
    );
    $form['teligence_cart_error_valid_account'] = array (
    	'#type'=>'textfield',
    	'#title'=>t('Valid account'),
    	'#default_value'=>variable_get('teligence_cart_error_valid_account', 'Your account has been validated. You can login now.'),
    );
    $form['teligence_cart_error_existing_account'] = array (
    	'#type'=>'textfield',
    	'#title'=>t('Existing account'),
    	'#default_value'=>variable_get('teligence_cart_error_existing_account', 'You already have an account with us. Did you forget your password?'),
    );
    $form['teligence_cart_error_new_account'] = array (
    	'#type'=>'textfield',
    	'#title'=>t('New account'),
    	'#default_value'=>variable_get('teligence_cart_error_new_account', 'Your new web account has been created. Further instructions have been sent to your e-mail address.'),
    );
    
    $form['teligence_cart_customer_service_phone'] = array (
    '#type'=>'textfield',
    '#title'=>t('Customer Service Number'),
    '#description'=>t('This number will be shown to the user in emergency cases when a transaction cannot be completed.'),
    '#default_value'=>variable_get('teligence_cart_customer_service_phone', '1-800-xxx-xxxx'),
    );
    
    $form['teligence_cart_customer_access_phone'] = array (
    '#type'=>'textfield',
    '#title'=>t('Customer Access Number'),
    '#description'=>t('Will be shown if no local access numbers are available.'),
    '#default_value'=>variable_get('teligence_cart_customer_access_phone', '1-800-xxx-xxxx'),
    );
    
    $form['teligence_cart_free_trial_code'] = array (
    '#type'=>'textfield',
    '#title'=>t('Free Trial Code'),
    '#description'=>t('Will be shown if no local access numbers are available.'),
    '#default_value'=>variable_get('teligence_cart_free_trial_code', '1-800-xxx-xxxx'),
    );
    $form['teligence_cart_error_call_cs'] = array (
    '#type'=>'textfield',
    '#title'=>t('Call Customer Service'),
    '#default_value'=>variable_get('teligence_cart_error_call_cs', 'Please call our customer service: '.variable_get('teligence_cart_customer_service_phone', '1-800-xxx-xxxx')),
    );
    $form['teligence_cart_customer_access_phone_fullmessage'] = array (
    '#type'=>'textarea',
    '#title'=>t('No Local Access Numbers Available'),
    '#default_value'=>variable_get('teligence_cart_customer_access_phone_fullmessage', ''),
    '#description' => t('Show this text to the user when no local numbers are available in the area.'),
    );
    
    /**
     * error messages requested by Shantel Shave email on Tuesday, June 29, 2010 4:20 PM
     */
    $form['teligence_cart_error_phone_number'] = array (
    '#type'=>'textfield',
    '#title'=>t('Blank phone number'),
    '#default_value'=>variable_get('teligence_cart_error_phone_number', 'Phone number is required. Please enter your phone number.'),
    );
    $form['teligence_cart_error_password_match'] = array (
    '#type'=>'textfield',
    '#title'=>t("Passwords don't match"),
    '#default_value'=>variable_get('teligence_cart_error_password_match', "Passwords don't match. Please re-enter your password."),
    );
    $form['teligence_cart_error_password_re_enter'] = array (
    '#type'=>'textfield',
    '#title'=>t("Re-enter your password"),
    '#default_value'=>variable_get('teligence_cart_error_password_re_enter', "Please re-enter your password."),
    );
    $form['teligence_cart_error_invalid_csc'] = array (
    '#type'=>'textfield',
    '#title'=>t("Invalid security code"),
    '#default_value'=>variable_get('teligence_cart_error_invalid_csc', "Invalid security code. Please re-enter your security code."),
    );
    
    $form['teligence_cart_returning_member'] = array (
    '#type'=>'textarea',
    '#title'=>t("User selected 'Returning Member' option in Buy Now page"),
    '#default_value'=>variable_get('teligence_cart_returning_member', "If you already have a web account with us please login. If you don't have a web account with us, please create one " . l('here', 'cart/signup')),
    '#rows'=>10,
    );
    $form['teligence_cart_asu_screen'] = array (
    '#type'=>'textarea',
    '#title'=>t('ASU - Message to show on screen when successful purchase'),
    '#default_value'=>variable_get('teligence_cart_asu_screen', "Thanks for signing up for an account with us.<br /><ul><li>Your new IVR Memebership Number is: [ivr_number]</li><li>Your new IVR Passcode is: [ivr_passcode]</li><li>Your new Web Account Password is: [password]</li></ul>"),
    '#rows'=>10,
    '#description' => 'Tokens: <strong>' . theme('item_list', array_keys(teligence_cart_tokens())) . '</strong>Only relevant tokens are available.',
    );
    
    /*
     * EMAIL CAMPAIGN SUCCESS PAGE
     */
    $form['teligence_cart_error_new_account_email_campaign_subject'] = array (
    '#type'=>'textarea',
    '#title'=>t('EMAIL CAMPAIGN SUCCESS PAGE'),
    '#default_value'=>variable_get('teligence_cart_error_new_account_email_campaign_subject', ''),
    '#rows'=>10,
    );
    $form['teligence_cart_error_new_account_email_campaign'] = array (
    '#type' => 'item',
    '#title' => t('Tokens'), 
    '#value'=> t('URL to preview this page: !url', array('!url' => l(url('cart/email-campaign/success', array('absolute' => true)), 'cart/email-campaign/success'))).
    	'<br/><strong>' . theme('item_list', array_keys(teligence_cart_tokens())) . '</strong>Only relevant tokens are available.',
    );
    
    /**
     * EMAILS
     */
    $form['teligence_cart_forgot_pass_email_subject'] = array (
    '#type'=>'textfield',
    '#title'=>t('Forgot Password Email Subject'),
    '#default_value'=>variable_get('teligence_cart_forgot_pass_email_subject', '[brand-name] account: reset your password'),
	'#description' => 'Tokens: same as below',
    );
    $form['teligence_cart_forgot_pass_email'] = array (
    '#type'=>'textarea',
    '#title'=>t('Forgot Password Email Body'),
    '#default_value'=>variable_get('teligence_cart_forgot_pass_email', "You requested a password reset for your account.<br /><br />In order to reset your password please go to:<br />[link]<br /><br />Thanks<br />The [brand] Team"),
    '#rows'=>10,
    '#description' => 'Tokens: <strong>' . theme('item_list', array_keys(teligence_cart_tokens())) . '</strong>Only relevant tokens are available.',
    );
    $form['teligence_cart_validate_account_subject'] = array (
    '#type'=>'textfield',
    '#title'=>t('Validate Account Email Subject'),
    '#default_value'=>variable_get('teligence_cart_validate_account_subject','Welcome to [brand-name]: please validate email'),
	'#description' => 'Tokens: same as below',
    );
    $form['teligence_cart_validate_account'] = array (
    '#type'=>'textarea',
    '#title'=>t('Validate Account Email Body'),
    '#default_value'=>variable_get('teligence_cart_validate_account', "Thanks for signing up for an account with us.<br /><br />In order to validate your account please go to:<br />[link]<br /><br />Thanks<br />The [brand] Team"),
    '#rows'=>10,
    '#description' => 'Tokens: <strong>' . theme('item_list', array_keys(teligence_cart_tokens())) . '</strong>Only relevant tokens are available.',
    );
    $form['teligence_cart_asu_subject'] = array (
    '#type'=>'textfield',
    '#title'=>t('Email - Time purchase email subject (ASU, SR)'),
    '#default_value'=>variable_get('teligence_cart_asu_subject', 'Thank you from [brand-name]: purchase confirmation'),
	'#description' => 'Tokens: same as below',
    );
    $form['teligence_cart_asu'] = array (
    '#type'=>'textarea',
    '#title'=>t('Email - Time purchase email body (ASU, SR)'),
    '#default_value'=>variable_get('teligence_cart_asu', "Thanks for signing up for an account with us.<br /><ul><li>Your new IVR Memebership Number is: [ivr_number]</li><li>Your new IVR Passcode is: [ivr_passcode]</li><li>Your new Web Account Password is: [password]</li></ul><br /><br />Thanks<br />The [brand] Team"),
    '#rows'=>10,
    '#description' => 'Tokens: <strong>' . theme('item_list', array_keys(teligence_cart_tokens())) . '</strong>Only relevant tokens are available.',
    );
    $form['teligence_cart_sr_subject'] = array (
    '#type'=>'textfield',
    '#title'=>t('Email - Signup web account email subject (ASU, Signup form)'),
    '#default_value'=>variable_get('teligence_cart_sr_subject', 'Thank you from [brand-name]: signup confirmation'),
    '#description' => 'Tokens: same as below',
    );
    $form['teligence_cart_sr'] = array (
    '#type'=>'textarea',
    '#title'=>t('Email - Signup web account email body (ASU, Signup form)'),
    '#default_value'=>variable_get('teligence_cart_sr', ""),
    '#rows'=>10,
    '#description' => 'Tokens: <strong>' . theme('item_list', array_keys(teligence_cart_tokens())) . '</strong>Only relevant tokens are available.',
    );
    $form['teligence_cart_email_campaign_subject'] = array (
    '#type'=>'textfield',
    '#title'=>t('Email - Email Collection Campaign email subject'),
    '#default_value'=>variable_get('teligence_cart_email_campaign_subject','[brand-name] on-line account confirmation'),
    '#description' => 'Tokens: same as below',
    );
    $form['teligence_cart_email_campaign'] = array (
    '#type'=>'textarea',
    '#title'=>t('Email - Email Collection Campaign email body'),
    '#default_value'=>variable_get('teligence_cart_email_campaign', ""),
    '#rows'=>10,
    '#description' => 'Tokens: <strong>' . theme('item_list', array_keys(teligence_cart_tokens())) . '</strong>Only relevant tokens are available.',
    );
	
    return system_settings_form($form);
}


/*
 * pre render functin for error messages form
 * show default value for each variable in the description property of the field, below the field
 */
function teligence_cart_errors_form_pre_render($form)
{
	foreach((array)element_children($form) as $key)
	{
		//!strstr($key, '#') ? $form[$key]['#description'] .= "Variable Name: <strong>variable_get('" . $key . "', '' )</strong>" : null;
		$form[$key]['#description'] .= " Variable Name: <strong>variable_get('" . $key . "', '' )</strong>";
		
		if(substr($key, -8) == '_subject')
		{
			$subjectsibling = substr($key, 0, -8);
			$form['group_'.$subjectsibling] = array(
				'#title' => "COMBO - " . $subjectsibling,
				'#type' => 'fieldset',
				'#collapsible' => true,
				'#collapsed' => true,
				'#weight' => -100,
			);
			$form['group_'.$subjectsibling][$key] = $form[$key];
			unset($form[$key]);
		}
		if($key == $subjectsibling)
		{
			$form['group_'.$subjectsibling][$key] = $form[$key];
			unset($form[$key]);
			unset($subjectsibling);
		}
	}	
	
	return $form;
}