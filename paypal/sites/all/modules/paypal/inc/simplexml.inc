<?php 
/** 
    Usage: 
        
    $xml = loadXML2("127.0.0.1", "/path/to/xml/server.php?code=do_something"); 
    if($xml) 
    { 
    	// xml doc loaded 
    } 
    else 
    { 
        // failed. show friendly error message. 
    } 
 */
function paypal_loadXML2array($domain, $path, $timeout = 30) 
{ 
    $output['success'] = false;
	$fp = fsockopen($domain, 80, $errno, $errstr, $timeout); 
    if($fp) 
    {   
//		Host: vvandevbts22.dev.alldir.net
//		User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; en-US; rv:1.9.2.3) Gecko/20100401 Firefox/3.6.3 (.NET CLR 3.5.30729)
//		Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
//		Accept-Language: en-us
//		Accept-Encoding: gzip,deflate
//		Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7
//		Keep-Alive: 115
//		Connection: keep-alive
    
        // make request 
        $out  = "GET $path HTTP/1.1\r\n"; 
        $out .= "Host: $domain\r\n"; 
        $out .= "Connection: Close\r\n\r\n"; 
        fwrite($fp, $out); 
        
        // get response 
        $resp = ""; 
        while (!feof($fp)) 
        { 
            $resp .= fgets($fp, 128); 
        } 
        fclose($fp); 
        // check status is 200 
        $status_regex = "/HTTP\/1\.\d\s(\d+)/"; 
        if(preg_match($status_regex, $resp, $matches) && $matches[1] == 200) 
        {    
            // load xml as object 
            $parts = explode("\r\n\r\n", $resp);
            $output['success'] = true;    
            $output['result'] = simplexml_load_string($parts[1]);               
        } 
    } 
    else
    {
    	$output['result'] = "Error: paypal_loadXML2array -> fsockopen -> $errstr - ($errno) ";
		
		// error logging and alerts
		watchdog("debug","@errorId - @cause - @resol - @input - @errorMessage", 
		array(
			"@errorId" => "PPPP004", // Brand Websites teligence click to call
			"@cause" => "Cause: fsockopen request timed out or response was invalid from $domain",
			"@resol" => "Resolution: input parameters could be invalid or $domain could be down. Telnet to either $domain from paypal box to test the connection on port 80", 
			"@input" => "Input Parameters [$domain?$path]", 
			"@errorMessage" => "Error: paypal_loadXML2array -> fsockopen -> $errstr - ($errno) ", 
		), WATCHDOG_EMERG);
    }
    
    return  $output;
}