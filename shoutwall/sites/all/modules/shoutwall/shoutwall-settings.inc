<?php

/**
 * settings form
 */
function shoutwall_settings_form($form_state)
{
	$form['shoutwall'] = array(
		'#type' => 'fieldset',
		'#pre_render' => array('shoutwall_settingsPrerender'),
	);
	$form['shoutwall']['shoutwall_secret'] = array(
		'#type'=>'textfield',
		'#size'=>60,
		'#default_value'=>variable_get('shoutwall_secret','teligence'),
		'#description'=>t('Shared secret string between telephony box and website.'),
	);
	
	return system_settings_form($form);
}


/*
 * pre render functin for error messages form
 * show default value for each variable in the description property of the field, below the field
 */
function shoutwall_settingsPrerender($form)
{
	foreach((array)element_children($form) as $key)
	{
		$form[$key]['#description'] .= " Variable Name: <strong>variable_get('" . $key . "', '' )</strong>";
		$subjectsibling = '';
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