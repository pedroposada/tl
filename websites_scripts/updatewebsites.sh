#!/bin/bash
# Requires DRUSH

echo "Test if drush is installed ..."
drush st || exit 1


echo "Change directory to '/var/www/websites' ..."
cd /var/www/websites || exit 1


echo "Change ownership of websites_copy folder to chromatic:apache ..."
chown -R chromatic:apache .


echo "SVN Update websites to latest"
echo -e "Type your svn username and press [ENTER]:"
read svnusername
echo -e "Type your svn password and press [ENTER]:"
read svnpassword
svn up --username "$svnusername" --password "$svnpassword"


echo "Make a temporary copy of existing websites folder except '.svn' folders to '/home/chromatic/websites_copy' folder ..."
rsync -a --progress --exclude-from '/home/chromatic/websites_scripts/exclude.txt' . /home/chromatic/websites_copy


echo "Change directory to '/home/chromatic/websites_copy' ..."
cd /home/chromatic/websites_copy


echo "Change ownership of websites_copy folder to chromatic:apache ..."
chown -R chromatic:apache .


echo "Enable core 'update' module on all sites ..."
drush @sites -y -v en update


echo "Run drupal update script on all sites ..."
drush @sites -y -v updb


echo "Update code on all sites ..."
drush @sites -y -v upc --version-control=backup --no-backup


echo "Run drupal update script on all sites ..."
drush @sites -y -v updb


echo "Disable core 'update' module on all sites ..."
drush @sites -y -v dis update


echo "Clear caches ..."
drush @sites -y -v cc all


echo "change directory to '/var/www/websites' ..."
cd /var/www/websites


echo "Synchronize copy with original '/var/www/websites' except for the '.svn' directories ..."
rsync -va --exclude-from '/home/chromatic/websites_scripts/exclude.txt' /home/chromatic/websites_copy/ .


echo "Change ownership of '/var/www/websites' folder to chromatic:apache ..."
chown -R chromatic:apache .


echo "Run perms.sh script to configure proper permissions for files folders and settings.php files"
cd /home/chromatic/websites_scripts
chmod u+x perms.sh
./perms.sh


echo "Remove temporary copy '/home/chromatic/websites_copy' folder ...."
rm -rf /home/chromatic/websites_copy


echo "Done updating code and databases"
echo "Test all websites before commit!"


exit 1
