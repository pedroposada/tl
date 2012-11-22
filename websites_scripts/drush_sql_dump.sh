#!/bin/bash
#dump websites databases using drush

#create folder to store dumps
DUMPSFOLDER='/home/chromatic/websites_dumps'
cd "${DUMPSFOLDER}" 

# define drush path
DRUSHPATH='/home/chromatic/drush/drush'

# define drupal root directory
DRUPALROOT='/var/www/websites/'

# change directory into websites
cd "${DRUPALROOT}"

# find all sites inside websites
for site in $(find "${DRUPALROOT}" -name settings.php |  awk -F/ '{print $6}')
do
   site_path="${DRUPALROOT}"sites/"${site}"

        echo "Dumping database for $site"
        "${DRUSHPATH}" -y -l "${site}" sql-dump --result-file="${DUMPSFOLDER}"/"${site}".sql --gzip
        echo "Done"
done

