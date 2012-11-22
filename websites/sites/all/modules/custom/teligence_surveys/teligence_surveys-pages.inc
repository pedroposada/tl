<?php

/**
 * facebook january mini contest
 */
function teligence_surveys_facebookJanuaryMiniContest_form($form_state)
{
	// contest form fields
	$form['firstname'] = array(
		'#title' => t('First Name'),
		'#type' => 'textfield',
	);
	$form['lastname'] = array(
		'#title' => t('Last Name'),
		'#type' => 'textfield',
	);
	$form['phone'] = array(
		'#title' => t('Phone'),
		'#type' => 'textfield',
		'#pre_render'=>array('teligence_purchase_prerenderPhone'),
	);
	$form['email'] = array(
		'#title' => t('Email'),
		'#type' => 'textfield',
	);
	$form['submit'] = array(
		'#value' => t('Submit'),
		'#type' => 'submit',
		'#pre_render' => array('teligence_surveys_buttonDisable'),
	);
	
	// hidden fields
	$form['signed_request'] = array(
		'#type' => 'hidden',
		'#default_value'=>'',
	);
	$form['pageLiked'] = array(
		'#type' => 'hidden',
		'#default_value'=>'',
	);
	$form['facebookId'] = array(
		'#type' => 'hidden',
		'#default_value'=>'',
	);
	$form['successMessage'] = array(
		'#type' => 'hidden',
		'#default_value'=>t('Successful submission'),
	);
	$form['failureMessage'] = array(
		'#type' => 'hidden',
		'#default_value'=>t('There was a problem.'),
	);
	$form['submittedSuccess'] = array(
		'#type'=>'hidden',
		'#default_value'=>$form_state['storage']['success'],
	);
	
	return $form;
}
function teligence_surveys_facebookJanuaryMiniContest_form_validate($form, &$form_state)
{
	// clicked submit button to enter contest
	if($form_state['clicked_button']['#id'] == 'edit-submit')
	{
		teligence_surveys_duplicateValue($form['phone'],$form_state);
		teligence_surveys_duplicateValue($form['email'],$form_state);
		
		if(!teligence_surveys_validPhoneNumber($form_state['values']['phone']))
		{
			form_error($form['phone'],'Invalid Phone Number.');
		}
		if(!valid_email_address($form_state['values']['email']))
		{
			form_error($form['email'],'Invalid Email Address.');
		}
		if(empty($form_state['values']['firstname']))
		{
			form_error($form['firstname'],'First Name is required.');
		}
		if(empty($form_state['values']['lastname']))
		{
			form_error($form['lastname'],'Last Name is required.');
		}
		if(empty($form_state['values']['facebookId']))
		{
			form_error($form['facebookId'],'Please logout and log back in.');
		}
	}
}
function teligence_surveys_facebookJanuaryMiniContest_form_submit($form, &$form_state)
{
	// clicked submit button to enter contest
	if($form_state['clicked_button']['#id'] == 'edit-submit')
	{
		$form_state['storage']['success'] = 0;
		db_set_active('surveys');
		$sql = "INSERT INTO {teligence_surveys} (formId, formValues) VALUES ('%s','%s');";
		$result = db_query($sql,$form_state['values']['form_id'],serialize($form_state['values']));
		db_set_active();
		if($result)
		{
			$form_state['storage']['success'] = 1;
			drupal_set_message($form_state['values']['successMessage']);
		}
		else
		{
			drupal_set_message($form_state['values']['failureMessage']);
		}
	}
}


/**
 * facebook february date night contest
 */
function teligence_surveys_facebookFebruaryContest_form($form_state)
{
	$form['#tree'] = TRUE;
	
	// contest form fields
	// female
	$form['female']['firstname'] = array(
		'#title' => t('First Name'),
		'#type' => 'textfield',
	);
	$form['female']['lastname'] = array(
		'#title' => t('Last Name'),
		'#type' => 'textfield',
	);
	$form['female']['phone'] = array(
		'#title' => t('Phone'),
		'#type' => 'textfield',
		'#pre_render'=>array('teligence_purchase_prerenderPhone'),
		'#element_validate' => array('teligence_surveys_duplicateValue'),
	);
	$form['female']['email'] = array(
		'#title' => t('Email'),
		'#type' => 'textfield',
		'#element_validate' => array('teligence_surveys_duplicateValue'),
	);
	
	// male
	$form['male']['firstname'] = array(
		'#title' => t('First Name'),
		'#type' => 'textfield',
	);
	$form['male']['lastname'] = array(
		'#title' => t('Last Name'),
		'#type' => 'textfield',
	);
	$form['male']['phone'] = array(
		'#title' => t('Phone'),
		'#type' => 'textfield',
		'#pre_render'=>array('teligence_purchase_prerenderPhone'),
		'#element_validate' => array('teligence_surveys_duplicateValue'),
	);
	$form['male']['email'] = array(
		'#title' => t('Email'),
		'#type' => 'textfield',
		'#element_validate' => array('teligence_surveys_duplicateValue'),
	);
	
	// reasons
	$form['reasons'] = array(
		'#title' => t('Tell us why you should be selected to win'),
		'#type' => 'textarea',
	);
	
	$form['submit'] = array(
		'#value' => t('Submit'),
		'#type' => 'submit',
		'#pre_render' => array('teligence_surveys_buttonDisable'),
	);
	
	// hidden fields
	$form['signed_request'] = array(
		'#type' => 'hidden',
		'#default_value'=>'',
	);
	$form['pageLiked'] = array(
		'#type' => 'hidden',
		'#default_value'=>'',
	);
	$form['facebookId'] = array(
		'#type' => 'hidden',
		'#default_value'=>'',
	);
	$form['successMessage'] = array(
		'#type' => 'hidden',
		'#default_value'=>t('Successful submission'),
	);
	$form['failureMessage'] = array(
		'#type' => 'hidden',
		'#default_value'=>t('There was a problem.'),
	);
	$form['submittedSuccess'] = array(
		'#type'=>'hidden',
		'#default_value'=>$form_state['storage']['success'],
	);
	
	return $form;
}
function teligence_surveys_facebookFebruaryContest_form_validate($form, &$form_state)
{
	// clicked submit button to enter contest
	if($form_state['clicked_button']['#id'] == 'edit-submit')
	{
		// female
		if(!teligence_surveys_validPhoneNumber($form_state['values']['female']['phone']))
		{
			form_error($form['female']['phone'],'Invalid Female Contestant Phone Number');
		}
		if(!valid_email_address($form_state['values']['female']['email']))
		{
			form_error($form['female']['email'],'Invalid Female Contestant Email Address');
		}
		if(empty($form_state['values']['female']['firstname']))
		{
			form_error($form['female']['firstname'],'Female Contestant First Name is required');
		}
		if(empty($form_state['values']['female']['lastname']))
		{
			form_error($form['female']['lastname'],'Female Contestant Last Name is required');
		}
		
		// male
		if(!teligence_surveys_validPhoneNumber($form_state['values']['male']['phone']))
		{
			form_error($form['male']['phone'],'Invalid Male Contestant Phone Number');
		}
		if(!valid_email_address($form_state['values']['male']['email']))
		{
			form_error($form['male']['email'],'Invalid Male Contestant Email Address');
		}
		if(empty($form_state['values']['male']['firstname']))
		{
			form_error($form['male']['firstname'],'Male Contestant First Name is required');
		}
		if(empty($form_state['values']['male']['lastname']))
		{
			form_error($form['male']['lastname'],'Male Contestant Last Name is required');
		}
		
		// catch duplicates within the form
		if($form_state['values']['female']['phone'] == $form_state['values']['male']['phone'])
		{
			form_error($form['female']['phone'],'Cannot enter same phone number for both contestants.');
			form_error($form['male']['phone'],'Cannot enter same phone number for both contestants.');
			array_pop($_SESSION['messages']['error']);
		}
		if($form_state['values']['female']['email'] == $form_state['values']['male']['email'])
		{
			form_error($form['female']['email'],'Cannot enter same email for both contestants.');
			form_error($form['male']['email'],'Cannot enter same email for both contestants.');
			array_pop($_SESSION['messages']['error']);
		}

		// reasons
		if(empty($form_state['values']['reasons']))
		{
			form_error($form['reasons'],'Please enter a reason why you should be selected.');
		}
	}
}
function teligence_surveys_facebookFebruaryContest_form_submit($form, &$form_state)
{
	// clicked submit button to enter contest
	if($form_state['clicked_button']['#id'] == 'edit-submit')
	{
		foreach((array)$form_state['values']['male'] as $k=>$v)
		{
			$form_state['values']['male_'.$k] = $v;
		}
		foreach((array)$form_state['values']['female'] as $k=>$v)
		{
			$form_state['values']['female_'.$k] = $v;
		}
		unset($form_state['values']['male']);
		unset($form_state['values']['female']);
		$form_state['storage']['success'] = 0;
		db_set_active('surveys');
		$sql = "INSERT INTO {teligence_surveys} (formId, formValues) VALUES ('%s','%s');";
		$result = db_query($sql,$form_state['values']['form_id'],serialize($form_state['values']));
		db_set_active();
		if($result)
		{
			$form_state['storage']['success'] = 1;
			drupal_set_message($form_state['values']['successMessage']);
		}
		else
		{
			drupal_set_message($form_state['values']['failureMessage']);
		}
	}
}
