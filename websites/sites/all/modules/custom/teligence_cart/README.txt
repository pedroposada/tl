Teligence Cart Module for Drupal 6.x
Developed by Pedro Posada pedro.posada@teligence.net

WIKI
---------
http://wiki.teligence.net/doku.php?id=ep:nbi:200721:technicalapproach

INTRO
---------
Module to integrate phone system back-end payment methods with the web. 
This module creates multiple screens with urls based in cart/*
As of now, the module provides screens to allow users to buy minutes with credit card.
There is a complementary module in the plugins folder called  teligence_cart_paypal that implements an interface to allow payments through paypal.
This module connects to the phone system back-end through web-services. 
It uses soap-php extension to consume WSDL xml files from .NET web-services from the back-end.
All URLS to connect to the web service should go in the form of domain names and not in the form of IP addresses. This can be setup in the settings section. 
You can use IP addresses for development purposes only. 



REFERENCES
-----------------
- PHP 					http://ca2.php.net/tut.php
- SOAP PHP EXTENSION  	http://ca2.php.net/manual/en/book.soap.php
- DRUPAL 				http://drupal.org/about
- DRUPAL API 			http://api.drupal.org/
- DRUPAL FORMS API 		http://drupal.org/node/751826



 SETTINGS
------------
- Go to /admin/cart , there you can set up messages for the user and urls for the webservice. 
There is a tab called Test Page, this tab works as
a sand box and show whatever you put inside function teligence_cart_test_page().
- In the teligence_cart/scripts folder you will find cart_settings.txt file which contains default development environment settings.
You can paste this script in admin/cart/settings-import and click on Import Settings button. You can use this to quickly install the module
in multiple drupal instances.



'Cart EMS Memberships' block settings
-------------------------------------
Block title: 
<none>

Page specific visibility settings:
Show on only the listed pages.
cart/add-time
cart/add-card
cart/show-balance
cart/ivr-passcode
cart/order-history
	
Role specific visibility settings:
ivr_user




'Cart' block settings
-------------------------------------
Block title: 
<none>
	
Page specific visibility settings:
Show on only the listed pages.
cart/*

Role specific visibility settings:
anonymous user
ivr_user




Permissions (/admin/user/permissions)
-----------------------------------
access buy now				anonymous user
access logged in pages		ivr_user
access login page			anonymous user
access logout page			ivr_user
active web account			ivr_user
administer cart settings	-
change web password			ivr_user





GENERAL TROUBLESHOOTING
---------------------------------------
- This module uses php SOAP extension to communicate to back-end systems. Back-end needs high time values to complete all transactions.
This causes the default php socket configuartion to time out. We received a php error saying 

"Error fetching http headers"

We fixed this problem in production environment by increasing the default_socket_timeout to 480 seconds. 
Add/change setting in your php.ini file as follows:

	default_socket_timeout = 480
	
Restore the apache webserver as follows:
	
	service httpd reload



SET OF URLS FOR FETCHING THE WSDL in DEV, QA and PRD
------------------------------------------------------
This settings are located at /admin/cart

--- DEV
WSDL URL #1 (Provisioning):
http://192.168.198.242/Teligence/Website/Services/Host/Provisioning.svc?WSDL
WSDL URL #2 (MemberManagement):
http://192.168.198.242/Teligence/WebSite/Services/Host/MemberManagement.svc?WSDL
WSDL URL #3 (MemberCredentials):
http://192.168.198.242/Teligence/Website/Services/Host/MemberCredentials.svc?WSDL
WSDL URL #4 (IvrRtm):
http://192.168.198.242/Teligence/Website/Services/Host/IvrRtm.svc?WSDL
WSDL URL #5 (OrderManagement):
http://192.168.198.242/Teligence/Website/Services/Host/OrderManagement.svc?WSDL

--- QA
http://192.168.148.59/WebsiteServices/Provisioning.svc?WSDL
http://192.168.148.59/WebsiteServices/MemberManagement.svc?WSDL
http://192.168.148.59/WebsiteServices/MemberCredentials.svc?WSDL
http://192.168.148.59/WebsiteServices/IvrRtm.svc?WSDL
http://192.168.148.59/WebsiteServices/OrderManagement.svc?WSDL

--- PRD
http://ws.wsweblogic.alldir.net/WebsiteServices/Provisioning.svc?WSDL
http://ws.wsweblogic.alldir.net/WebsiteServices/MemberManagement.svc?WSDL
http://ws.wsweblogic.alldir.net/WebsiteServices/MemberCredentials.svc?WSDL
http://ws.wsweblogic.alldir.net/WebsiteServices/IvrRtm.svc?WSDL
http://ws.wsweblogic.alldir.net/WebsiteServices/OrderManagement.svc?WSDL




SET CATCH ALL EMAIL ADDRESSES IN DEV/QA BOX TO TEST
---------------------------------------------------
http://www.postfix.org/VIRTUAL_README.html

Execute the following command:
nano /etc/postfix/virtual

Add one line per email address at the end of the file:
@yourname.dev REALADDRESS@teligence.net

Save

Execute commands:
/usr/sbin/postmap /etc/postfix/virtual
/usr/sbin/postfix reload

Done

