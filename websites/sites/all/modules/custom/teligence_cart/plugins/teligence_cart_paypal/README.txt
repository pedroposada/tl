Documentation for Paypal plugin for Teligence Web Payment Module
----------------------------------------------------------------

This module allows the brand websites to connect to paypal.teligence.net

In the case that the drupal brand website is multilingual, each language needs to have a prefix. 
i.e.: 
english => en 
spanish => es 
and so on.

To configure this module go to:

After enableing the module at "admin/build/modules" go to "admin/cart/paypal"

Each brand website needs to have a unique identifier and password. This will be validated by paypal.teligence.net

Insert HTML or text in the box that says "Price Confirmation Screen". This content will show up in the package 
confirmation screen under http://paypal.teligence.net/paypal/package-details

Insert HTML or text in the box that says "Failure Screen:". This will show up in the after the user comes back
from paypal.com and the process failed. 




TROUBLESHOOTING
---------------

To test this plugin in QA make sure that:

	- QA webserver box has entries in the hosts file that allows the brand website to call itsef. Meaning, the http
		request will resolve correctly when sending them from itself.

	- If the brand website is multilingual, then make sure that each language has a prefix configured at 
		 http://www.BRANDWEBSITE.com/admin/settings/language -> click on EDIT -> set prefix

	- paypal.teligence.net needs to have entries for every vendor (brand website). Refer to dpcumentation 
		for paypal payment module at http://wiki.teligence.net/doku.php?id=ep:nbi:200781

	- There are entries in the hosts file of QA webserver so that it is able to resolve the URL "paypal.teligence.net"