<?php

/** DoExpressCheckoutPayment NVP example; last modified 08MAY23.
 *
 *  Complete an Express Checkout transaction. 
*/

/**
 * This example assumes that a token was obtained from the SetExpressCheckout API call.
 * This example also assumes that a payerID was obtained from the SetExpressCheckout API call
 * or from the GetExpressCheckoutDetails API call.
 */
// Set request-specific fields.
$payerID = urlencode("payer_id");
$token = urlencode("token");

$paymentType = urlencode("Authorization");			// or 'Sale' or 'Order' or 'Authorization'
$paymentAmount = urlencode("payment_amount");
$currencyID = urlencode("USD");						// or other currency code ('GBP', 'EUR', 'JPY', 'CAD', 'AUD')

// Add request-specific fields to the request string.
$nvpStr = "&TOKEN=$token&PAYERID=$payerID&PAYMENTACTION=$paymentType&AMT=$paymentAmount&CURRENCYCODE=$currencyID";

// Execute the API operation; see the PPHttpPost function above.
$httpParsedResponseAr = PPHttpPost('DoExpressCheckoutPayment', $nvpStr);

if("Success" == $httpParsedResponseAr["ACK"]) {
	exit('Express Checkout Payment Completed Successfully: '.print_r($httpParsedResponseAr, true));
} else  {
	exit('DoExpressCheckoutPayment failed: ' . print_r($httpParsedResponseAr, true));
}