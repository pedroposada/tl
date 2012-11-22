Documentation for Paypal Integration Project.

200781 PayPal � Automated Integration of Websites
http://wiki.teligence.net/doku.php?id=ep:nbi:200781


NOTES:
-----------------
This module is intended for allowing communication between any web-site, back-ends and PAYPAL. 
The module implements DRUPAL API to communicate with PAYPAL API and TELIGENCE back-end API.
The module executes a number of calls to different APIs mentioned above. 
This module was designed to be installed on a separate instance of DRUPAL.
This module is not designed to work together with other custom or contributed modules.
There is a sample databse dump file to learn more details about the database structure.

 * Paypal SandBox
 * 
 * Account Login 
 * https://developer.paypal.com/us/cgi-bin/devscr
 * ****
 * ****



INSTALLATION:
--------------------
- In a brand new installation of drupal go to /admin/build/modules and enable PayPal - Automated Integration of Websites
- Go to /admin/paypal to set up PayPal API Environment to live or sandbox (development test environment). The rest of the fields on that page can be
safely ignored.
 
 
 
 
PAYPAL TELIGENCE BACK-END 
=========================


pp_Credential Table
-------------------
USD
http://www.BRANDNAME.com/cart/buy (ASU)
http://www.BRANDNAME.com/cart/add-time (SR)
http://www.BRANDNAME.com/cart/paypal/asu/success (ASU)
http://www.BRANDNAME.com/cart/paypal/sr/success (SR)
http://www.BRANDNAME.com/cart/paypal/failure
TotalAmountDollars
PackageName
InvoiceNumber



GetPackageDetails
-----------------
http://ws.wspaypalgatewayhost.alldir.net/PayPalPayment/GetPackageDetails.ashx?SequenceId=%%&PackageId=%%
ResponseCode
Success
http://www.BRANDNAME.com/cart/paypal/price-confirmation



IPN
---
http://ws.wspaypalgatewayhost.alldir.net/PayPalPayment/ProcessNotification.ashx?SequenceId=%%&PayPalTransactionId=%%&NotificationType=%%
ResponseCode
Success



OrderFulfillment
----------------
http://ws.wspaypalgatewayhost.alldir.net/PayPalPayment/ProcessPayment.ashx?SequenceId=%%&OrderId=%%&TRANSACTIONID=%%&PAYMENTTYPE=%%
ResponseCode
Success



ValidateResponse (ASU and SR)
----------------
http://ws.wspaypalgatewayhost.alldir.net/PayPalPayment/ValidateAsuPurchase.ashx?SequenceId=%%&LASTNAME=%%&FIRSTNAME=%%&Ani=%%&PackageId=%%&PAYERID=%%
ResponseCode
Success

http://ws.wspaypalgatewayhost.alldir.net/PayPalPayment/ValidateSrPurchase.ashx?SequenceId=%%&PackageId=%%&PAYERID=%%&EmsMembershipId=%%
ResponseCode
Success


TROUBLESHOOTING
---------------------
To find out detailed transaction information check the pp_Logging table. This table should contain GET and POST parameters for every single transaction
between paypal and this module.


ERROR SCENARIOS:
----------------
DuplicateGUID - this or similiar to this message will show up in the URL of the failure page when 
comming back from paypal after paying.
Possible reasons are that when testing the ASU, the same email was used twice logging into PAYPAL.
Always make sure that you never use the same email twice in the PAYPAL logi screen when testing ASU.



