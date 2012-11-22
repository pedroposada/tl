Teligence Click to Call Module

Module developed by Pedro Posada April 2010 for Teligence pedro.posada@teligence.net

This module is specifically designed to provide CTC functionality for Teligence brand websites.

This module provides functionality to connect users to the phone system. It issues an http request to an asterisk
server that generates a phone call to the user's phone, connecting the user to Livelinks or any other brand.

One of the functionalities this module provides is a ctc token for ctc_landing_page content type. When creating a new 
ctc_landing_page you can place token [ctc-form] in the body textarea and it will turn into a ctc form once the node has
been saved.

A separate database is required for the module to fetch the appropriate local hub number and send the request to
the click to call server. Right now the module works with llk_paypal database. All local hub numbers are stored
in llk_paypal database. To add or/and see a list of local hub numbers go to http://paypal.livelinks.com/ctc/hubnumbers .

There is a blacklist of phone numbers stored in the llk_paypal database. Go to http://paypal.livelinks.com/ctc/blacklist 
to add and/or view all blacklisted numbers. This module checks if the number the user entered is blacklisted and will 
block the call.

This module should also handle any mobile CTC requests. The mobile ctc form will issue a request to a page this module 
has defined, the module will parse the request, prepare all parameters and issue a request to the asterisk click to call 
server. This module defines ctc/mobile as a menu callback to handle mobile ctc requests. 

SAMPLE DATABASE CONNECTION IN settings.php FILE FOR LLK BRAND WEBSITE:
$db_url = array( 
	'default' => 'mysql://user:password@localhost/livelinks-www',
	'paypal' => 'mysql://user:password@localhost/llk_paypal',
);  

It also checks if the user submitted number has been previously listed in a black list stored in llk_paypal 
database. 


REFERENCES
---------------
- PHP http://ca2.php.net/tut.php
- DRUPAL http://drupal.org/about
- DRUPAL API http://api.drupal.org/
- DRUPAL FORMS API http://drupal.org/node/751826




SERVER
----------------
- need to be able to resolve and connect to http://voice1.f8.teligence.net/callmenow/CallMeNow.php



SETTINGS 
-----------------
- /admin/settings/ctc
	Here you can setup response messages for multiple languages
	Set the asterisk server URL and other parameters.
	Set tracking scripts for google, yahoo, bing and others
	Insert php to set up rules for tracking scripts.


NOTES
----------------- 
- Disable teligence_hub_manager module to get this module to work properly.





THIRD PARTY INTEGRATION
-----------------------
CTC module will use url path "http://brandDomainName/ctc/call" which uses callback "teligence_ctc_mobile" 
Values required from third parties to CTC module as GET parameters are: 

area_code
phone_number

The rest of the parameters are optional.

Example of url to make request:

https://www.livelinks.com/ctc/call?area_code=604&phone_number=1556987

This call will use LLK prompt set. Click to call module will use the domain name to set the prompt set.
If the domain does not map to any prompt set inside the module, then it will use LLK by default.

Prompt sets are hardcoded inside the module:

'livelinks' => 'LLK',
'interactivemale' => 'IML',
'redhotdateline' => 'RDL',
'lavenderline' => 'LBL',
'fonochatlatino' => 'FON',
'vibeline' => 'VBL',







GOOGLE MULTIVARIANT TESTING
---------------------------
- Familiarize your self with Website Optimizer from Google first.
- Upgrade the teligence_ctc module to at least version 6002.
- Edit/Create a ctc_landing_page node.
- Create a new Experiment in Website Optimizer from Google.
- Paste the Contro/Tracking scripts in the Control/Tracking Scripts text area of the landing page edit form.
- Paste the Conversion script in the Conversion Script text area of the landing page edit form. 
- Add any page sections in the Body text area of the landing page edit form.
- Save the node.
- Configure variations in Website Optimizer admin screen.
- Start your experiment.

Note: the ctc_landing_page needs to be accessible by google.
