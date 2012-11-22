<?php

/**
 * settings form
 */
function teligence_purchase_settings_form($form_state)
{
	$form['mssql'] = array(
		'#type' => 'fieldset',
		'#title'=>t('Common Event MSSQL Connection Settings'),
		'#collapsed' => TRUE,
		'#collapsible' => TRUE,
	);
	$form['mssql']['teligence_purchase_mssqlServer'] = array(
		'#type'=>'textfield',
		'#title'=>t('Server Name'),
		'#default_value'=>variable_get('teligence_purchase_mssqlServer',""),
	);	
	$form['mssql']['teligence_purchase_mssqlUser'] = array(
		'#type'=>'textfield',
		'#title'=>t('Server Username'),
		'#default_value'=>variable_get('teligence_purchase_mssqlUser',""),
	);	
	$form['mssql']['teligence_purchase_mssqlPass'] = array(
		'#type'=>'textfield',
		'#title'=>t('Server Password'),
		'#default_value'=>variable_get('teligence_purchase_mssqlPass',""),
	);	
	
	$form['teligence_purchase_brandid'] = array(
		'#type' => 'select',
		'#title' => t('Brand Code'),
		'#options' => array (
	        1=>'Livelinks',
	        2=>'InteractiveMale',
	        3=>'Tango Personals',
	        4=>'Red Hot Dateline',
	        6=>'Mens Free Chatline',
	        7=>'VibeLine',
	        8=>'Fonochat',
	        12=>'Lavender Line',
	    ),
		'#default_value' => variable_get('teligence_purchase_brandid', 1),
	);
	$form['teligence_purchase_customerservice'] = array(
		'#type' => 'textfield',
		'#title' => t('Call Customer Service Message'),
		'#default_value' => variable_get('teligence_purchase_customerservice', 'Please call customer service at 1-800-984-6889'),
		'#required' => true,
	);
	$form['teligence_purchase_cachewsdl'] = array(
		'#type' => 'select',
		'#title' => t('Cache WSDL'),
		'#options' => array(0 =>'No', 1 => 'Yes'),
		'#default_value' => variable_get('teligence_purchase_cachewsdl', 1),
		'#required' => true,
		'#description' => t('If set to Yes, it will refresh the WSDL on wevery call to back-end.'),
	);
	$form['teligence_purchase_debug'] = array(
		'#type' => 'select',
		'#title' => t('Debug Mode'),
		'#options' => array(0 =>'No', 1 => 'Yes'),
		'#default_value' => variable_get('teligence_purchase_debug', 0),
		'#required' => true,
		'#description' => t('Error messages will show on the page.'),
	);
	
	/**
	 * Localization
	 */
	$items = array(
		'GetLocalAccessNumberByLongLat',
		'GetLocalAccessNumberByAreaCode',
		'GetMarkets',
	);
	$form['teligence_purchase_wsdl_localization'] = array(
		'#type' => 'textfield',
		'#title' => t('WSDL for Localization'),
		'#default_value' => variable_get('teligence_purchase_wsdl_localization','http://192.168.184.197/Teligence/Services/Hosts/BrandWebSite/Localization.svc?wsdl'),
		'#description' =>theme('fieldset',array('#title'=>t('Services'),'#collapsible' =>1,'#collapsed'=>1,'#value'=>theme('item_list',$items))),
		'#size' => 120, 
		'#required' => true,
	);
	
	/**
	 * Member Management
	 */
	$items = array(
		'GetWebProfile',
		'UpdateWebProfile',
		'LinkIvrMembership',
		'GetPaymethods',
		'AddCreditCard',
		'UpdateCreditCardExpiryDate',
		'DeactivatePaymentMethod',
		'GetOrderHistory'
	);
	$form['teligence_purchase_wsdl_membermanagement'] = array(
		'#type' => 'textfield',
		'#title' => t('WSDL for Member Management'),
		'#default_value' => variable_get('teligence_purchase_wsdl_membermanagement','http://192.168.184.197/Teligence/Services/Hosts/BrandWebSite/MemberManagement.svc?wsdl'),
		'#description' =>theme('fieldset',array('#title'=>t('Services'),'#collapsible' =>1,'#collapsed'=>1,'#value'=>theme('item_list',$items))),
		'#size' => 120, 
		'#required' => true,
	);
	
	/**
	 * Member Credentials
	 */
	$items = array(
		'SignUp',
		'SignIn',
		'ValidateWebAccount',
		'ForgotEmail',
		'ChangePassword',
		'GetPasswordResetId',
		'ResetPassword',
		'GetEmailResetId',
		'ResetEmail',
	);
	$form['teligence_purchase_wsdl_membercredentials'] = array(
		'#type' => 'textfield',
		'#title' => t('WSDL for Member Credentials'),
		'#default_value' => variable_get('teligence_purchase_wsdl_membercredentials','http://192.168.184.197/Teligence/Services/Hosts/BrandWebSite/MemberCredentials.svc?wsdl'),
		'#description' =>theme('fieldset',array('#title'=>t('Services'),'#collapsible' =>1,'#collapsed'=>1,'#value'=>theme('item_list',$items))),
		'#size' => 120,
		'#required' => true,
	);
	
	/**
	 * Ivr Rtm 
	 */
	$items = array(
		'UpdateIvrPasscode',
		'GetMembershipStats',
	);
	$form['teligence_purchase_wsdl_ivrrtm'] = array(
		'#type' => 'textfield',
		'#title' => t('WSDL for Member Credentials'),
		'#default_value' => variable_get('teligence_purchase_wsdl_ivrrtm','http://192.168.184.197/Teligence/Services/Hosts/BrandWebSite/IvrRtm.svc?wsdl'),
		'#description' =>theme('fieldset',array('#title'=>t('Services'),'#collapsible' =>1,'#collapsed'=>1,'#value'=>theme('item_list',$items))),
		'#size' => 120,
		'#required' => true,
	);
	
	/**
	 * Provisioning
	 */
	$items = array(
		'GetPackagesByMembership',
		'GetPackagesByBrandAni',
		'GetPackagesByBrandMarket',
	);
	$form['teligence_purchase_wsdl_provisioning'] = array(
		'#type' => 'textfield',
		'#title' => t('WSDL for Provisioning'),
		'#default_value' => variable_get('teligence_purchase_wsdl_provisioning','http://192.168.184.197/Teligence/Services/Hosts/BrandWebSite/Provisioning.svc?wsdl'),
		'#description' =>theme('fieldset',array('#title'=>t('Services'),'#collapsible' =>1,'#collapsed'=>1,'#value'=>theme('item_list',$items))),
		'#size' => 120,
		'#required' => true,
	);
	
	/**
	 * Order Management
	 */
	$items = array(
		'ProcessFreeTimeOrder ',
		'ValidateAsuNotSignedIn',
		'ValidateAsuSignedInNewCreditCard',
		'ValidateAsuSignedInOldCreditCard',
		'ValidateSrOldCreditCard',
		'ValidateSrNewCreditCard',
		'ProcessPayment',
	);
	$form['teligence_purchase_wsdl_ordermanagement'] = array(
		'#type' => 'textfield',
		'#title' => t('WSDL for Order Management'),
		'#default_value' => variable_get('teligence_purchase_wsdl_ordermanagement','http://192.168.184.197/Teligence/Services/Hosts/BrandWebSite/OrderManagement.svc?wsdl'),
		'#description' =>theme('fieldset',array('#title'=>t('Services'),'#collapsible' =>1,'#collapsed'=>1,'#value'=>theme('item_list',$items))),
		'#size' => 120,
		'#required' => true,
	);
	
	return system_settings_form($form);
}
/**
 * settings 2 form
 * variables to store emails
 */
function teligence_purchase_settings2_form($form_state)
{
	$form['teligence_purchase'] = array(
		'#type' => 'fieldset',
		'#pre_render' => array('teligence_purchase_emails_pre_render'),
	);
	
	// package purchase
	$form['teligence_purchase']['teligence_purchase_emailPackagePurchase_subject'] = array (
	    '#type'=>'textfield',
	    '#title'=>t('Package Purchase Subject Line'),
	    '#default_value'=>variable_get('teligence_purchase_emailPackagePurchase_subject',''),
	    '#description' => theme('item_list', array_keys((array)teligence_purchase_tokens('emailPackagePurchase'))),
    );
    $form['teligence_purchase']['teligence_purchase_emailPackagePurchase'] = array (
	    '#type'=>'textarea',
	    '#title'=>t('Package Purchase Body'),
	    '#default_value'=>variable_get('teligence_purchase_emailPackagePurchase',''),
	    '#rows'=>10,
	    '#description' => theme('item_list', array_keys((array)teligence_purchase_tokens('emailPackagePurchase'))),
    );
	
	// new account email
	$form['teligence_purchase']['teligence_purchase_emailNewIvrAccount_subject'] = array (
	    '#type'=>'textfield',
	    '#title'=>t('New IVR Account Subject Line'),
	    '#default_value'=>variable_get('teligence_purchase_emailNewIvrAccount_subject',''),
	    '#description' => theme('item_list', array_keys((array)teligence_purchase_tokens('emailNewIvrAccount'))),
    );
    $form['teligence_purchase']['teligence_purchase_emailNewIvrAccount'] = array (
	    '#type'=>'textarea',
	    '#title'=>t('New IVR Account Body'),
	    '#default_value'=>variable_get('teligence_purchase_emailNewIvrAccount',''),
	    '#rows'=>10,
	    '#description' => theme('item_list', array_keys((array)teligence_purchase_tokens('emailNewIvrAccount'))),
    );
	
	// validate account email
	$form['teligence_purchase']['teligence_purchase_emailValidateAccount_subject'] = array (
	    '#type'=>'textfield',
	    '#title'=>t('Validate Account Subject Line'),
	    '#default_value'=>variable_get('teligence_purchase_emailValidateAccount_subject',''),
	    '#description' => theme('item_list', array_keys((array)teligence_purchase_tokens('emailValidateAccount'))),
    );
    $form['teligence_purchase']['teligence_purchase_emailValidateAccount'] = array (
	    '#type'=>'textarea',
	    '#title'=>t('Validate Account Body'),
	    '#default_value'=>variable_get('teligence_purchase_emailValidateAccount',''),
	    '#rows'=>10,
	    '#description' => theme('item_list', array_keys((array)teligence_purchase_tokens('emailValidateAccount'))),
    );
	
	// password recovery email
	$form['teligence_purchase']['teligence_purchase_emailPasswordRecovery_subject'] = array (
	    '#type'=>'textfield',
	    '#title'=>t('Validate Account Subject Line'),
	    '#default_value'=>variable_get('teligence_purchase_emailPasswordRecovery_subject',''),
	    '#description' => theme('item_list', array_keys((array)teligence_purchase_tokens('emailPasswordRecovery'))),
    );
    $form['teligence_purchase']['teligence_purchase_emailPasswordRecovery'] = array (
	    '#type'=>'textarea',
	    '#title'=>t('Validate Account Body'),
	    '#default_value'=>variable_get('teligence_purchase_emailPasswordRecovery',''),
	    '#rows'=>10,
	    '#description' => theme('item_list', array_keys((array)teligence_purchase_tokens('emailPasswordRecovery'))),
    );
	
	// email reset email id
	$form['teligence_purchase']['teligence_purchase_emailResetEmailId_subject'] = array (
	    '#type'=>'textfield',
	    '#title'=>t('Reset Email Id Subject Line'),
	    '#default_value'=>variable_get('teligence_purchase_emailResetEmailId_subject',''),
	    '#description' => theme('item_list', array_keys((array)teligence_purchase_tokens('emailResetEmailId'))),
    );
    $form['teligence_purchase']['teligence_purchase_emailResetEmailId'] = array (
	    '#type'=>'textarea',
	    '#title'=>t('Reset Email Id Body'),
	    '#default_value'=>variable_get('teligence_purchase_emailResetEmailId',''),
	    '#rows'=>10,
	    '#description' => theme('item_list', array_keys((array)teligence_purchase_tokens('emailResetEmailId'))),
    );
	
	return system_settings_form($form);
}

/*
 * pre render functin for error messages form
 * show default value for each variable in the description property of the field, below the field
 */
function teligence_purchase_emails_pre_render($form)
{
	foreach((array)element_children($form) as $key)
	{
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