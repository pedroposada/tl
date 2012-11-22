From: Paul Crick 
Sent: Monday, October 24, 2011 9:50 AM
To: Ivelina Vladimirova; Pedro Posada
Subject: Jack's C2C API

We want the external vendor to call us using a URL something like this:

            http://ctc.xipservices.com/request/call.php?PartnerID=xxxxxx&Requestor=xxxxxx&Fulfillment=xxxxxx&Auth=xxxxxx


Vendor Work
-	Pass us Requestor and Fulfillment in E.164 format (ie 16045551234)
-	Calculate the Auth as an MD5 hash of “B4n0ff13P13!_” plus the Partner ID plus the Requestor value plus the Fulfillment value
-	Let’s use 102821 as their “Partner ID”

Pedro Work
-	Receive the request from the vendor (HTTP GET or POST?)
-	Validate the PartnerID is valid (let’s store valid values in a database, so we can extend this if needed)
-	Calculate the MD5 as above and validate it matches the Auth parameter of the request
-	If Auth matches, call the click to call server with the following parameters:
o	RequestorPhone                 Requestor, from the Vendor request
o	RequestorCID                      last 10 chars of Fulfillment, from the Vendor request
o	DestinationPhone               Fulfillment, from the Vendor request
o	DestinationCID                    last 10 chars of Requestor, from the Vendor request
o	PromptSet                             XIP1
o	TimeLimit                               7200
o	PartnerID                               PartnerID, from the Vendor request
o	Source                                   XIP1
o	Auth                                       MD5 hash calculated using the click to call algorithm
-	If the Auth doesn’t match, call the click to call server with the same parameters as above, but set Auth to “BadIncomingAuth”
-	Whatever the click to call server returns as a result code, return to the Vendor

If the Vendor’s Auth field doesn’t match the required value, we’ll still call the click to call server but force a failure condition – this is so we can always return a consistent interface to the Vendor, which will allow them to track request results, and allow us to investigate exactly what was sent in the case of error.

Questions
-	Do we need any level of granularity or tracking for the vendor? Or is it enough to use their multiple Fulfillment DNISes (ie we don’t need to track campaign/affiliate etc for them)?

Does this look ok to everyone?

Cheers
Paul
