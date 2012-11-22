Teligence Browser Based Monitoring Project
BBM Agent module developed by Pedro Posada for Teligence April/May 2010, pedro.posada@teligence.net



 INTRO
--------------
This module implements Drupal API to provide screens to monitor and process recordings.
Naming convention for all pages is cart/*
All module dependencies are listed in the bbm_agent.info file
This module provides a number of tabs with forms to rate, monitor, search recordings.
The recordings are stored in a remote server, this module provides a handler to buffer the recording into the 
browser.
Ideally the module should live in an instance of Drupal dedicated only to this purpose.
The module allows user account creation via the administrative screen User Administration tab.
Partial user information is stored in the local MySQL database, just the username and the email address are stored
locally, the rest is stored in the MSSQL database. User accounts are created to be able to handle user SESSIONS
with Drupal API. 

The recordings are played using FLASH PLAYER Version 10.x




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
The sever needs to have the php-mssql extension installed and working. This extension allows php to establish connections a Microsoft SQL server.
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

Login as admin 
http://bbm.teligence.net/user
admin-bbm
P@ssw0rd

Then go to http://bbm.teligence.net/admin/settings/bbm/settings

Database Username:
svcbbm2web02

Database Password: 
BBM2Web02

-- How to change the password for admin
In terminal 

cd /var/www/bbm/
drush sqlq "update users set pass=md5(‘P@ssw0rd’) where uid = 1;"


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


-- If you get error: "Fatal error: call to undefined function mssql_connect()"
Make sure that php53-mssql-5.3.3-1.el5.i386.rpm is compatible with your version
of php.

Shell commands to find versions of mssql, php and centos
php -v
locate mssql.so
cat /etc/redhat-release

