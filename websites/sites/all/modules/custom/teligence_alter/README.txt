Teligence Alter Module 
Developed by Pedro Posada for teligence brand websites 2009


 INTRO
-------------
This module provides miscellaneous services to multiple websites.
This is a helper module to modify the behaviour of a number of web forms.
This module is used by multimple websites in very different scenarios.
This module controls the redirection of mobile traffic to mobile version of websites.


HOW IT WORKS
----------------
Mobile traffic:
On every page request this module checks if the device is a mobile or desktop device and executes the redirection accordingly.
Therefore this module has to be enabled on all brand websites that have a mobile version of them.

Costumer service forms:
This module alters the behaviour of two forms in a websites called paypal.livelinks.com. This website implements a number of forms to manage
local hub numbers, black listed numbers for CTC and paypal orders that came through the old paypal implementation.

Contact form:
This module implements hook_form_alter() to alter the looks of the contact form in the teligence.net website.


NOTES
------------------
It is critical to have this module enabled in all brand websites specifically because it handles the redirection to mobile pages.