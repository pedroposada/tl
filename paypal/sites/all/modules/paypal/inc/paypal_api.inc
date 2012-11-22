<?php

/**
 * Paypal SandBox
 * 
 * Account Login 
 * https://developer.paypal.com/us/cgi-bin/devscr
 * pedro.posada@teligence.net
 * teligence
 * 
 */


/**
 * Send HTTP POST Request using cURL
 *
 * @param	array	Fully populated vendor array
 * @param	string	The API method name
 * @param	string	The POST Message fields in &name=value pair format
 * @return	array	Parsed HTTP Response body
 */
function PPHttpPost($vendor, $methodName_, $nvpStr_) 
{
	// Set up your API credentials, PayPal end point, and API version.
	$API_UserName = urlencode($vendor['PayPalAPI_UserName']);
	$API_Password = urlencode($vendor['PayPalAPI_Password']);
	$API_Signature = urlencode($vendor['PayPalAPI_Signature']);
	$API_Endpoint = "https://api-3t.paypal.com/nvp";
	
	if("sandbox" === variable_get('paypal_api_environment',"sandbox")) 
	{
		//https://api-3t.sandbox.paypal.com/nvp
		$API_Endpoint = "https://api-3t." . variable_get('paypal_api_environment',"sandbox") . ".paypal.com/nvp";
		
		// API sandbox login credentials
		$API_UserName = urlencode(variable_get('paypal_sandbox_api_username', ''));
		$API_Password = urlencode(variable_get('paypal_sandbox_api_password', ''));
		$API_Signature = urlencode(variable_get('paypal_sandbox_api_signature', ''));
	}
	
	//$version = urlencode('3.0');
	$version = urlencode('52.0');

	// Set the curl parameters.
	$ch = curl_init();
	curl_setopt($ch, CURLOPT_URL, $API_Endpoint);
	curl_setopt($ch, CURLOPT_VERBOSE, 1);

	// Turn off the server and peer verification (TrustManager Concept).
	curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
	curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, FALSE);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
	curl_setopt($ch, CURLOPT_POST, 1);

	// Set the API operation, version, and API signature in the request.
	$nvpreq = "METHOD=$methodName_&VERSION=$version&PWD=$API_Password&USER=$API_UserName&SIGNATURE=$API_Signature$nvpStr_";

	//store call request in pp_Logging
	db_query("INSERT INTO {pp_Logging} (SessionID, CallName, Value) VALUES('%s', '%s', '%s')", $_SESSION['paypal_guid'], $methodName_ . '_request', $nvpreq);
	
	// Set the request as a POST FIELD for curl.
	curl_setopt($ch, CURLOPT_POSTFIELDS, $nvpreq);

	// Get response from the server.
	$httpResponse = curl_exec($ch);

	if(!$httpResponse) 
	{
		drupal_set_message("$methodName_ failed: ".curl_error($ch).'('.curl_errno($ch).')');
		
		// error logging and alerts
		watchdog("debug","@errorId - @cause - @resol - @httpResult", 
		array(
			"@errorId" => "PPPP002", // Brand Websites teligence click to call
			"@cause" => "Cause: cURL cannot connect to $API_Endpoint; Connection times out or response is invalid.",
			"@resol" => "Resolution: open network connection on port 80 from paypal.teligence.net box to $API_Endpoint. Try telnet to $API_Endpoint server from paypal.teligence.net box.", 
			"@errorMsg" => "cURL error message = ".curl_error($ch)." - cURL error code = " .curl_errno($ch),
		), WATCHDOG_EMERG);
		
		return;
	}
	
	//store call response in pp_Logging
	db_query("INSERT INTO {pp_Logging} (SessionID, CallName, Value) VALUES('%s', '%s', '%s')", $_SESSION['paypal_guid'], $methodName_ . '_response', $httpResponse);

	// Extract the response details.
	$httpResponseAr = explode("&", $httpResponse);

	$httpParsedResponseAr = array();
	foreach ($httpResponseAr as $i => $value) 
	{
		$tmpAr = explode("=", $value);
		if(sizeof($tmpAr) > 1) 
		{
			$httpParsedResponseAr[$tmpAr[0]] = $tmpAr[1];
		}
	}

	if((0 == sizeof($httpParsedResponseAr)) || !array_key_exists('ACK', $httpParsedResponseAr)) 
	{
		drupal_set_message("Invalid HTTP Response for POST request($nvpreq) to $API_Endpoint.");
		
		// error logging and alerts
		watchdog("debug","@errorId - @cause - @resol - @input - @httpResponse", 
		array(
			"@errorId" => "PPPP003", // Brand Websites teligence click to call
			"@cause" => "Cause: cURL request came back empty or invalid from $API_Endpoint",
			"@resol" => "Resolution: input parameters could be invalid or paypal.com could be down. Telnet to either $API_Endpoint from paypal box to test the connection on port 80", 
			"@input" => "Input Parameters [$nvpreq]", 
			"@httpResponse" => "Http Response from paypal.com [$httpResponse]", 
		), WATCHDOG_EMERG);
		
		return false;
	}
	
	//add debugging values to response array
	$httpParsedResponseAr['request'] = explode("&", $nvpreq);
	$httpParsedResponseAr['request']['API_Endpoint'] = $API_Endpoint;

	return $httpParsedResponseAr;
}


/** SetExpressCheckout NVP
 *
 *  Initiate an Express Checkout transaction. 
 *  
 *  @param	array	Fully populated vendor array
*/
function paypal_SetExpressCheckout($vendor, $productDescription, $totalAmt, $invoiceNumber, $paymentType = "Sale")
{
	// Add request-specific fields to the request string.
	$nvp = array(
		'AMT' => urlencode($totalAmt),
		'RETURNURL' => urlencode(url('paypal/return/' . $vendor['VendorID'], array('absolute' => true))), //urlencode($vendor['PaypalReturnURL']),
		//'RETURNURL' => url('paypal/buffer/' . $vendor['VendorID'], array('absolute' => true)), //urlencode($vendor['PaypalReturnURL']),
		'CANCELURL' => urlencode($vendor['PaypalCancelURL']),
		'PAYMENTACTION' => urlencode($paymentType), // or 'Sale' or 'Order'
		'PAGESTYLE' => urlencode('Paypal'),
		'CURRENCYCODE' => urlencode($vendor['PayPalAPI_Currency']), // or other currency code ('GBP', 'EUR', 'JPY', 'CAD', 'AUD')
		'NOSHIPPING' => 1,
		//'L_AMT0' => $itemAmt,
		//'L_TAXAMT0' => $taxesAmt,
		'LANDINGPAGE' => 'Billing',
		'INVNUM' => urlencode($invoiceNumber),
		'L_PAYMENTTYPE0' => 'InstantOnly',
		'L_NAME0' => urlencode($productDescription),
		'BRANDNAME' => urlencode($vendor['VendorName']),
	);
	//( $itemAmt ? $nvp['L_AMT0'] = urlencode($itemAmt) : null );
	//( $taxesAmt ? $nvp['L_TAXAMT0'] = urlencode($taxesAmt) : null );
	
	
	$nvpStr = '';
	foreach($nvp as $key => $value)
	{
		$nvpStr .= "&" . $key . "=" . $value;
	}
	
	// Execute the API operation; see the PPHttpPost function above.
	$httpParsedResponseAr = PPHttpPost($vendor, 'SetExpressCheckout', $nvpStr);
	
	if("Success" == $httpParsedResponseAr["ACK"]) 
	{
		// Redirect to paypal.com.
		$token = urldecode($httpParsedResponseAr["TOKEN"]);
		$payPalURL = "https://www.paypal.com/webscr&cmd=_express-checkout&token=$token";
		if("sandbox" === variable_get('paypal_api_environment','sandbox') || "beta-sandbox" === variable_get('paypal_api_environment','sandbox')) 
		{
			$payPalURL = 'https://www.'.variable_get('paypal_api_environment','sandbox').'.paypal.com/webscr&cmd=_express-checkout&token='.$token;
		}
		$httpParsedResponseAr['paypalStartURL'] = $payPalURL;
	} 
	else  
	{
		$httpParsedResponseAr['paypalStartURL'] = 0;
	}
	
	return $httpParsedResponseAr;
}


/** GetExpressCheckoutDetails NVP
 *
 *  Get information about an Express Checkout transaction. 
 *  
 *  @param	array	Fully populated vendor array
*/

function paypal_GetExpressCheckoutDetails($vendor, $token = null)
{
	/**
	 * This example assumes that this is the return URL in the SetExpressCheckout API call.
	 * The PayPal website redirects the user to this page with a token.
	 */
	
	// Obtain the token from PayPal.
	if(is_null($token)) 
	{
		drupal_set_message('Token is not received.');
		return false;
	}
	
	// Set request-specific fields.
	$token = urlencode(htmlspecialchars($token));
	
	// Add request-specific fields to the request string.
	$nvpStr = "&TOKEN=$token";
	
	// Execute the API operation; see the PPHttpPost function above.
	return PPHttpPost($vendor, 'GetExpressCheckoutDetails', $nvpStr);
}


/** DoExpressCheckoutPayment NVP
 *
 *  Complete an Express Checkout transaction. 
 *  
 *  @param	array	Fully populated vendor array
 *  @param	array	Array result from GetExpressCheckoutDetails
*/
function paypal_DoExpressCheckoutPayment($vendor, $httpParsedResponseAr)
{
	/**
	 * This example assumes that a token was obtained from the SetExpressCheckout API call.
	 * This example also assumes that a payerID was obtained from the SetExpressCheckout API call
	 * or from the GetExpressCheckoutDetails API call.
	 */
	// Set request-specific fields.
	$payerID = urlencode($httpParsedResponseAr['PAYERID']); 				// urlencode("payer_id");
	$token = urlencode(htmlspecialchars($_REQUEST['token'])); 				// urlencode("token");
	$paymentType = urlencode("Sale"); //urlencode("Authorization");			// or 'Sale' or 'Order' or 'Authorization'
	$paymentAmount = urlencode($httpParsedResponseAr['AMT']); 				// urlencode("payment_amount");
	$currencyID = urlencode($vendor['PayPalAPI_Currency']);					// or other currency code ('GBP', 'EUR', 'JPY', 'CAD', 'AUD')
	
	// Add request-specific fields to the request string.
	$nvpStr = "&TOKEN=$token&PAYERID=$payerID&PAYMENTACTION=$paymentType&AMT=$paymentAmount&CURRENCYCODE=$currencyID";
	
	// Execute the API operation; see the PPHttpPost function above.
	return PPHttpPost($vendor, 'DoExpressCheckoutPayment', $nvpStr);
}


/** DoVoid NVP
 *
 *  Void an order or an authorization. 
 *  https://cms.paypal.com/us/cgi-bin/?&cmd=_render-content&content_ID=developer/e_howto_api_nvp_r_DoVoid#id09BHI07E0EX
 *  
 *  @param	array			Fully populated vendor array
 *  @param	alphanumeric	Transaction ID returned by DoExpressCheckoutPayment
 *  @param	alphanumeric	An informational note about this void that is displayed to the payer in email and in his transaction history. Character length and limits: 255 single-byte characters 
*/
function paypal_DoVoid($vendor, $AUTHORIZATIONID, $NOTE = null)
{
	// Set request-specific fields.
	$nvp = array(
		'AUTHORIZATIONID' => urlencode($AUTHORIZATIONID),
	);	

	( strlen($NOTE) ? $nvp['NOTE'] = urlencode(htmlspecialchars($NOTE)) : null );
	
	// Add request-specific fields to the request string.
	$nvpStr = '';
	foreach($nvp as $key => $value)
	{
		$nvpStr .= "&" . $key . "=" . $value;
	}
	
	// Execute the API operation; see the PPHttpPost function above.
	return PPHttpPost($vendor, 'DoVoid', $nvpStr);
}

/** RefundTransaction NVP
 *
 *  Refund an order. 
 *  https://cms.paypal.com/us/cgi-bin/?&cmd=_render-content&content_ID=developer/e_howto_api_nvp_r_RefundTransaction
 *  
 *  @param	array			Fully populated vendor array
 *  @param	alphanumeric	Transaction ID returned by DoExpressCheckoutPayment
 *  @param	alphanumeric	Invoice number returned by DoExpressCheckoutPayment
 *  @param	alphanumeric	An informational note about this void that is displayed to the payer in email and in his transaction history. Character length and limits: 255 single-byte characters 
*/
function paypal_RefundTransaction($vendor, $TRANSACTIONID, $INVNUM, $NOTE = null)
{
	// Set request-specific fields.
	$nvp = array(
		'TRANSACTIONID' => urlencode($TRANSACTIONID),
		'INVNUM' => urlencode($INVNUM),
	);	
	( strlen($NOTE) ? $nvp['NOTE'] = urlencode(htmlspecialchars($NOTE)) : null );
	
	// Add request-specific fields to the request string.
	$nvpStr = '';
	foreach($nvp as $key => $value)
	{
		$nvpStr .= "&" . $key . "=" . $value;
	}
	
	// Execute the API operation; see the PPHttpPost function above.
	return PPHttpPost($vendor, 'RefundTransaction', $nvpStr);
}