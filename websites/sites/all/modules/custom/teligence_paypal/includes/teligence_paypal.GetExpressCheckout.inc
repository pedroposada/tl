<?php
/** GetExpressCheckoutDetails NVP example; last modified 08MAY23.
 *
 *  Get information about an Express Checkout transaction. 
*/

/**
 * This example assumes that this is the return URL in the SetExpressCheckout API call.
 * The PayPal website redirects the user to this page with a token.
 */

// Obtain the token from PayPal.
if(!array_key_exists('token', $_REQUEST)) {
	//exit('Token is not received.');
	drupal_set_message('Token is not received.');
	drupal_goto('paypal/return/technical');
}

// Set request-specific fields.
$token = urlencode(htmlspecialchars($_REQUEST['token']));

// Add request-specific fields to the request string.
$nvpStr = "&TOKEN=$token";

// Execute the API operation; see the PPHttpPost function above.
$httpParsedResponseAr = PPHttpPost('GetExpressCheckoutDetails', $nvpStr, $environment = variable_get('paypal_api_environment','sandbox'));

if("Success" == $httpParsedResponseAr["ACK"]) {
	// Extract the response details.
	$payerID = $httpParsedResponseAr['PAYERID'];
	$street1 = $httpParsedResponseAr["SHIPTOSTREET"];
	if(array_key_exists("SHIPTOSTREET2", $httpParsedResponseAr)) {
		$street2 = $httpParsedResponseAr["SHIPTOSTREET2"];
	}
	$city_name = $httpParsedResponseAr["SHIPTOCITY"];
	$state_province = $httpParsedResponseAr["SHIPTOSTATE"];
	$postal_code = $httpParsedResponseAr["SHIPTOZIP"];
	$country_code = $httpParsedResponseAr["SHIPTOCOUNTRYCODE"];

	//exit('Get Express Checkout Details Completed Successfully: '.print_r($httpParsedResponseAr, true));
	//drupal_set_message('<pre>'.print_r($httpParsedResponseAr,true).'</pre>');
	
} else  {
	//exit('GetExpressCheckoutDetails failed: ' . print_r($httpParsedResponseAr, true));
	drupal_set_message('<pre>'.print_r($httpParsedResponseAr,true).'</pre>');
	drupal_goto('paypal/return/technical');
}