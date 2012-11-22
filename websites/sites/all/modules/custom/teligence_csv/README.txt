Teligence CSV module
Developed by Pedro Posada


 INTRO
-------
This module was developed to create a comma separated text file wirh opted in email addresses and store this file in a directory.
The purpose is to allows dba team to fetch the csv file every week and update the opted in table of users.
The dba team would use a FTP to fetch the file from the websites server and use it to update their database.
This module was only enabled in teligence.net and biggaykiss.com websites.
It implements the hook_cron to have the websites reacreate the dump files every week.




HOW IT WORKS
-------------
On every cron job it will check the date of the most recent csv file in the opt_out_csv/ direcotry that sits inside the file_directory_temp() direcotory.
After checking this, it calculates if its been more than a week since this last file was created and creates a new one.
The contents of the new file come from a table called "webform_submitted_data". It grabs the email address of every user that opted in the last week.
This happens every monday.
See the code for more details about datbase sql statements.

