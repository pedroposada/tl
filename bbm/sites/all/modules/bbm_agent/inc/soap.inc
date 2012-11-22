<?php 

/*
 * SOAP call
 */
function bbm_agent_soap_call($params, $method_name, $wsdl, $renewGUID = null)
{
	$output = array ();
	
	if(!class_exists('SoapClient')){
		$output['result'] = 'SoapClientMissing';
		$output['debug'] = 'We are having technical problems. Plase try again later.';
		return $output;
	}
	
	$params->sequenceId = bbm_agent_uuid($renewGUID);
	
    // send xml
    try
    {
    	if(!@file_get_contents($wsdl)) {
        	throw new SoapFault('Server', 'No WSDL found at ' . $wsdl);
    	}
		
		// set up the service client using WSDL
		// TODO: remove/add array('cache_wsdl'=>WSDL_CACHE_NONE) as parameter for live/dev
		if(variable_get('teligence_cart_cache_wsdl', 1)){
			$client = new SoapClient($wsdl);
		}else{
			$client = new SoapClient($wsdl, array('cache_wsdl'=>WSDL_CACHE_NONE));
		}
    	
        $result = $client->{ $method_name }($params);

        //$output['debug'] = '<pre>'.check_plain(print_r($result, true)).'</pre>';
        $output['debug'] = 'Response Code for '.$method_name.': '.$result->{ $method_name.'Result' }->ResponseCode;
		
		$output['result'] = $result;
        //$output = '<pre>'.check_plain(print_r($client, true)).'</pre>';

    } 
	catch(SoapFault $e)
    {
        $output['error'] = $method_name.' <pre>'.check_plain(print_r($e->getMessage(), true)).'</pre>';
        
        if(check_plain(print_r($e->getMessage(), true)) == 'Error Fetching http headers'){
        	drupal_get_messages();
        	$output['debug'] = 'There has been a technical problem with your transaction. Please call our customer service: '.variable_get('teligence_cart_customer_service_phone', '1-800-xxx-xxxx');
        	drupal_goto('cart/blank');
        }else{
        	$output['debug'] = $method_name.' Soap Error Code: '.check_plain(print_r($e->getMessage(), true));
        }
        
    }

    return $output;
}

/*
 * GUID global universal identifier generator.
 * One per session.
 */
function bbm_agent_uuid($renewGUID = null)
{

    // The field names refer to RFC 4122 section 4.1.2
    if ( isset($_SESSION['guid']) && !$renewGUID )
    {
        return $_SESSION['guid'];
    }
    else
    {
        $_SESSION['guid'] = sprintf('%04x%04x-%04x-%03x4-%04x-%04x%04x%04x',
        mt_rand(0, 65535), mt_rand(0, 65535), // 32 bits for "time_low"
        mt_rand(0, 65535), // 16 bits for "time_mid"
        mt_rand(0, 4095), // 12 bits before the 0100 of (version) 4 for "time_hi_and_version"
        bindec(substr_replace(sprintf('%016b', mt_rand(0, 65535)), '01', 6, 2)),
        // 8 bits, the last two of which (positions 6 and 7) are 01, for "clk_seq_hi_res"
        // (hence, the 2nd hex digit after the 3rd hyphen can only be 1, 5, 9 or d)
        // 8 bits for "clk_seq_low"
        mt_rand(0, 65535), mt_rand(0, 65535), mt_rand(0, 65535) // 48 bits for "node"
        );
        return $_SESSION['guid'];
    }
}