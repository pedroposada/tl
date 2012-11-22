<?php

/**
 * settings form
 */
function teligence_surveys_settings_form($form_state)
{
	// teligence_surveys_facebookJanuaryMiniContest_form
	$formid = 'teligence_surveys_facebookJanuaryMiniContest_form';
	$form[$formid] = array(
		'#type'=>'fieldset',
		'#title'=>'Facebook January Mini Contest',
		'#pre_render'=>array('teligence_surveys_prerender'),
		'#description' => 	t('URL for this contest: @url; !results',array('@url'=>url('surveys/facebook-jan',array('absolute'=>TRUE)),
							'!results'=>l('Download Results','surveys/export-csv/'.$formid))),
	);
	$form[$formid][$formid.'_pageURL'] = array(
		'#type' => 'textfield',
		'#size' => 60,
		'#required'=>TRUE,
		'#default_value'=>variable_get($formid.'_pageURL',''),
		'#description'=>t('Facebook Page URL that contains a tab to this app.'),
		'#title'=>t('Page URL for facebookJanuaryMiniContest'),
	);
	$form[$formid][$formid.'_canvasPageUrl'] = array(
		'#type' => 'textfield',
		'#size' => 60,
		'#required'=>TRUE,
		'#default_value'=>variable_get($formid.'_canvasPageUrl',''),
		'#description'=>t('Canvas Page URL Specific for this app. This is the drupal URL.'),
		'#title'=>t('Canvas Page URL for facebookJanuaryMiniContest'),
	);
	$form[$formid][$formid.'_appId'] = array(
		'#type' => 'textfield',
		'#size' => 60,
		'#required'=>TRUE,
		'#default_value'=>variable_get($formid.'_appId',''),
		'#description'=>t('Facebook App Id Specific for this app.'),
		'#title'=>t('App Id for facebookJanuaryMiniContest'),
	);
	$form[$formid][$formid.'_appSecret'] = array(
		'#type' => 'textfield',
		'#size' => 60,
		'#required'=>TRUE,
		'#default_value'=>variable_get($formid.'_appSecret',''),
		'#description'=>t('Facebook App Secret Specific for this app.'),
		'#title'=>t('App Secret for facebookJanuaryMiniContest'),
	);
	$form[$formid][$formid.'_status'] = array(
		'#type' => 'select',
		'#default_value'=>variable_get($formid.'_status',0),
		'#options'=>array(1=>'Enabled',0=>'Disabled'),
		'#title'=>t($formid.' status'),
		'#description'=>t('Enable or disable this page.'),
	);
	
	return system_settings_form($form);
}



/*
 * show default value for each variable in the description property of the field, below the field
 */
function teligence_surveys_prerender($form)
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