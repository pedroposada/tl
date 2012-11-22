<?php 
	drupal_add_js(array('teligence_cart' => array("button_processing" => array(variable_get('teligence_cart_button_processing', '')))), 'setting');
	drupal_add_js(drupal_get_path('module', 'teligence_cart').'/js/jquery.button.js');
?>

<?php $form['local_number']['#description'] = t('Find your local access number and connect with local singles now!');  ?>
<?php $form['local_number']['area_code']['#title'] = t('Enter Area Code');  ?>


<?php print drupal_render($form);  ?>