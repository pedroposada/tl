README file for shoutwall module.


WIKI
----
More details about the shoutwall can be found at http://teliwiki/doku.php?id=ep:nbi:200841



Features of this module 
-----------------------
- Creates one custom page and one custom table (shoutwall_shouts).

- Custom page is accessible through path /shoutwall/frontpage

- This module will automatically set /shoutwall/frontpage as the default drupal front page.

- In order to add recordings to the table, an HTTP request via POST can be used as follows
	Sample cURL HTTP POST request:
	curl -F "fileupload=@/home/chromatic/shoutwall/audio/82a5c3ac9713f31b938264e0274f8a40.mp3" -F "op=create" -F "Status=A" -F "CategoryName=Happy Go Lucky" -F "HeadlineText=some head line text here" -F "ShoutText=some shout here updated" http://www.theshoutwall.com/shoutwall/remotepost/2/c38cb67b4cab2371f473fb4c6ab4dff0

- To see all details about the available input parameters and the format for each parameter please refer to http://teliwiki/doku.php?id=ep:nbi:200841:technical

- The custom table and all recordings will be deleted when uninstalling the module.

- By default the feddback form under the About Us tab will send emails to feedback@theshoutwall.com

- The feedback email can be modified via drush by runing the following command in the terminal:
	drush vset shoutwall_feedbackEmail "myemail@myemail.com"

- Or it can also be modified via UI under /admin/shoutwall


THEME
-----
- There are two template available from this module inside template folder.

- shoutwall-audioPlayer.tpl.php is used to theme the audio player.

- shoutwall-frontPage.tpl.php is used to theme the front page.

- The audio player is nested inside the front page template as the $audioPlayer variable.

- All UI elements can be overriden through the template.php and by copying the 
	provided template into the theme folder.
	
