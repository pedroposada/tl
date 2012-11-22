<?php
// $Id: teligence_secure.admin.inc,v 1.1.2.1 2009/03/29 10:49:12 gordon Exp $

/**
 * @file
 * Provide all the administration pages
 */
 
 /**
  * Implementation of hook_settings().
  */
function teligence_secure_settings_form($form_state) {
   $form = array();
   $form['#validate'] = array('teligence_secure_settings_form_validate');
   
   $form['teligence_secure_enable'] = array(
     '#type' => 'radios',
     '#title' => t('Enable Secure Pages'),
     '#default_value' => variable_get('teligence_secure_enable', 0),
     '#options' => array(t('Disabled'), t('Enabled')),
     //'#disabled' => !teligence_secure_test(),
     //'#description' => t('To start using secure pages this setting must be enabled. This setting will only be able to changed when the web server has been configured for SSL.<br />If this test has failed then go <a href="!url">here</a>', array('!url' => preg_replace(';^http://;i', 'https://', url($_GET['q'], array('absolute' => TRUE))))),
   );
   
   $form['teligence_secure_basepath'] = array(
     '#type' => 'textfield',
     '#title' => t('Non-secure Base URL'),
     '#default_value' => variable_get('teligence_secure_basepath', $_SERVER['HTTP_HOST']),
   	 '#description' => t('Non-secure URL i.e. <strong>www.mysite.com</strong>. No trailing slash "/"'),
   	 '#required' => true,
   );

   $form['teligence_secure_basepath_ssl'] = array(
     '#type' => 'textfield',
     '#title' => t('Secure Base URL'),
     '#default_value' => variable_get('teligence_secure_basepath_ssl', str_replace("www", "secure", $_SERVER['HTTP_HOST'])),
     '#description' => t('Secure base URL i.e. <strong>secure.mysite.com</strong>. No trailing slash "/"'),
     '#required' => true,
   );

   $form['teligence_secure_secure'] = array(
     '#type' => 'radios',
     '#title' => t('Pages which will be be secure'),
     '#default_value' => variable_get('teligence_secure_secure', 1),
     '#options' => array(t('Make secure every page except the listed pages.'), t('Make secure only the listed pages.')),
   );
   $form['teligence_secure_pages'] = array(
     '#type' => 'textarea',
     '#title' => t('Pages'),
     '#default_value' => variable_get('teligence_secure_pages', "cart/*"),
     '#cols' => 40,
     '#rows' => 5,
     '#description' => t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are '<em>blog</em>' for the blog page and '<em>blog/*</em>' for every personal blog. '<em>&lt;front&gt;</em>' is the front page."),
   );
   $form['teligence_secure_ignore'] = array(
     '#type' => 'textarea',
     '#title' => t('Ignore pages'),
     '#default_value' => variable_get('teligence_secure_ignore', "*/autocomplete/*\n*/ajax/*"),
     '#cols' => 40,
     '#rows' => 5,
     '#description' => t("The pages listed here will be ignored and be either returned in http or https. Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are '<em>blog</em>' for the blog page and '<em>blog/*</em>' for every personal blog. '<em>&lt;front&gt;</em>' is the front page."),
   );
   return system_settings_form($form);
}

/*
 * validate
 */
function teligence_secure_settings_form_validate($fom, &$form_state)
{
	if(!valid_url($form_state['values']['teligence_secure_basepath']))
	{
		form_set_error('teligence_secure_basepath', 'invalid URL');
	}
	if(!valid_url($form_state['values']['teligence_secure_basepath_ssl']))
	{
		form_set_error('teligence_secure_basepath_ssl', 'invalid URL');
	}
}
 