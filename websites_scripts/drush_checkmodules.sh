#!/bin/bash
# output a list of enabled modules from brand websites

# define drush path
DRUSHPATH='/home/chromatic/drush/drush'

# define drupal root directory
DRUPALROOT='/var/www/websites/'

# change directory into websites
cd "${DRUPALROOT}"

echo "find all sites inside websites"
for site in $(find "${DRUPALROOT}" -name settings.php |  awk -F/ '{print $6}')
do
	echo "build list of enabled modules for ${site}"
   	LIST=`"${DRUSHPATH}" -y -l "${site}" pm-list --pipe --type=module --status=enabled --no-core`
   	FULL="${FULL}${LIST}"
done

echo "change direcotry to '/var/www/d7'"
cd /var/www/d7

echo "remove availablemodules.txt"
rm -f availablemodules.txt

echo "remove missingmodules.txt"
rm -f missingmodules.txt

echo "loop through the enabled module list; try to download the drupal7 version of the module; log messages"
for MODULE in $(echo "${FULL}" | sort | uniq)
do
	echo "find release for module: ${MODULE}"
	test "$("${DRUSHPATH}" rl "${MODULE}")" != '' && (echo "${MODULE}" >> availablemodules.txt) || (echo "${MODULE}" >> missingmodules.txt)
done
