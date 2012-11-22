<?php

/** SetExpressCheckout NVP example; last modified 08MAY23.
 *
 *  Initiate an Express Checkout transaction. 
*/

// Set request-specific fields.
$invoicenumber = $_SESSION['paypal_order']['nid'];
$paymentAmount = urlencode($_SESSION['paypal_order']['payment_amount']);
$currencyID = urlencode(variable_get('paypal_api_currency','CAD'));							// or other currency code ('GBP', 'EUR', 'JPY', 'CAD', 'AUD')
$paymentType = urlencode('Sale');				// or 'Sale' or 'Order'

$returnURL = urlencode(variable_get('paypal_api_return_url',''));
$cancelURL = urlencode(variable_get('paypal_api_cancel_url',''));
$pageStyle = urlencode(variable_get('paypal_page_style_name','Paypal'));

// Add request-specific fields to the request string.
$nvpStr = "&Amt=$paymentAmount&ReturnUrl=$returnURL&CANCELURL=$cancelURL&PAYMENTACTION=$paymentType&PAGESTYLE=$pageStyle&CURRENCYCODE=$currencyID&NOSHIPPING=1&ITEMAMT=$paymentAmount&L_AMT0=$paymentAmount&LANDINGPAGE=Billing&INVNUM=$invoicenumber&L_BILLINGTYPE0&L_PAYMENTTYPE0=InstantOnly";

// Execute the API operation; see the PPHttpPost function above.
$httpParsedResponseAr = PPHttpPost('SetExpressCheckout', $nvpStr, variable_get('paypal_api_environment','sandbox'));

if("Success" == $httpParsedResponseAr["ACK"]) {
	// Redirect to paypal.com.
	$token = urldecode($httpParsedResponseAr["TOKEN"]);
	$payPalURL = "https://www.paypal.com/webscr&cmd=_express-checkout&token=$token";
	if("sandbox" === variable_get('paypal_api_environment','sandbox') || "beta-sandbox" === variable_get('paypal_api_environment','sandbox')) {
		$payPalURL = 'https://www.'.variable_get('paypal_api_environment','sandbox').'.paypal.com/webscr&cmd=_express-checkout&token='.$token;
	}
	//header("Location: $payPalURL");
	drupal_goto($payPalURL);
	exit;
} else  {
	//exit('SetExpressCheckout failed: ' . print_r($httpParsedResponseAr, true));
	drupal_set_message('<pre>'.print_r($httpParsedResponseAr,true).'</pre>');
	drupal_goto('paypal/return/technical');
}
