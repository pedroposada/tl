#!/bin/bash
echo "*********************** Change ownership to 'websites' folder contents to apache:apache **************"
chown -R apache:apache /var/www/websites/

echo "*********************** Set permissions to settings.php files to 444 *************"
echo "*********************** Before: ****************"
find /var/www/websites/ -type f -name "settings.php" -ls
find /var/www/websites/ -type f -name "settings.php" -exec chmod 444 {} \;

echo "*********************** After: ************************"
find /var/www/websites/ -type f -name "settings.php" -ls

