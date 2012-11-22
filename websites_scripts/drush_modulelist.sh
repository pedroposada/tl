#!/bin/bash
# output a list of enabled modules from brand websites

# define drush path
DRUSHPATH='/home/chromatic/drush/drush'

# define drupal root directory
DRUPALROOT='/var/www/websites/'

# change directory into websites
cd "${DRUPALROOT}"

# find all sites inside websites
for site in $(find "${DRUPALROOT}" -name settings.php |  awk -F/ '{print $6}')
do
   # store list of module in variable
   LIST=`"${DRUSHPATH}" -y -l "${site}" pm-list --pipe --type=module --status=enabled --no-core`
   FULL="${FULL}${LIST}"
   
done

# output distinct list of modules for all brand websites
echo "${FULL}" | sort | uniq
echo ""
