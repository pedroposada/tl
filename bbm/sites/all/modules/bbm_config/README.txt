Teligence Browser Based Monitoring Project
BBM Configuration module developed by Pedro Posada for Teligence April/May 2010, pedro.posada@teligence.net


 INTRO
---------------
This module complements the BBM Agent module and depends on it too.
It provides a number of screens to allow configuration of rules for the BBM system.
It plugs into the BBM Agent navigation structure creating a second level row of tabs.
Each tab represents a screen. Each screen contains a form.
This module is tightly connected with MSSQL database. It uses DRUPAL only for form generation, session handling and presentation layer.



 REFERENCES
---------------
- PHP http://ca2.php.net/tut.php
- DRUPAL http://drupal.org/about
- DRUPAL API http://api.drupal.org/
- DRUPAL FORMS API http://drupal.org/node/751826
- MSSQL PHP EXTENSION http://www.howtoforge.com/installing_php_mssql_centos5.0
- JQUERY http://jquery.com/
- TIMEPICKER in auditing tab http://milesich.com/timepicker/



 SERVER REQUIREMENTS
----------------------------
The sever needs to have the php-mssql extension installed and working. This extension allows php to establish connections to a Microsoft SQL server.
- php-mssql extension http://www.howtoforge.com/installing_php_mssql_centos5.0




 THEME
----------------
The default theme this module supports is bluemarine. This theme comes with drupal by default and provides css styles for tabs and forms.
The bbm_agent-style.css file ovewrites some of the default bluemarine styles.
- bluemarine




 SETTINGS
------------
- go to admin/settings/bbm to set up database connection and other settings like password recovery email and
time out limit




 TROUBLESHOOTING
----------------------
-- If you get error: "warning: mssql_connect()"

It means that linux SQL username and password are wrong. 
Change them at http://bbm.teligence.net/admin/settings/bbm/settings
admin-bbm
P@ssw0rd

Database Username:
svcbbm2web02

Database Password: 
BBM2Web02

-- If you get error: "warning: mssql_execute()"

It means that the section name in freetds file and server name are not exactly the same. 

In server run command:
nano /etc/freetds.conf

At the very bottom of the file add lines:

# Microsoft 2008 SQL server configuration for BBM
[SVANSQLPRD03]
       host = 192.168.198.170
       port = 1433
       tds version = 8.0

Save and reload apache:
service httpd relaod

Make sure server name in BBM web is exactly the same at http://bbm.teligence.net/admin/settings/bbm/settings
admin-bbm
P@ssw0rd

Data Base Server IP or URL: 
SVANSQLPRD03

Database Password: 
BBM2Web02