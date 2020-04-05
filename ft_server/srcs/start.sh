#!/bin/bash

# update
apt-get update
apt-get install -y wget

# install nginx
apt-get install -y nginx

# install php
apt-get install -y php7.3-fpm
apt-get install -y php7.3-gd
apt-get install -y php7.3-mbstring
apt-get install -y php-mysql
apt-get install -y php7.3-curl

# install MySQL
apt-get install -y mariadb-server
service mysql start

# install wordpress
wget https://wordpress.org/latest.tar.gz
tar -xvf latest.tar.gz
rm -rf latest.tar.gz
mv wordpress /var/www/html/
chown -R www-data:www-data /var/www/html/wordpress
mv /tmp/wp-config.php /var/www/html/wordpress/

# set database
mysql < /tmp/set.sql

# config nginx
cp /tmp/default /etc/nginx/sites-available/default
rm -rf /tmp/default

# open php info page
echo "<?php phpinfo(); ?>" > /var/www/html/index.php

# install phpmyadmin
wget https://files.phpmyadmin.net/phpMyAdmin/4.9.0.1/phpMyAdmin-4.9.0.1-all-languages.tar.gz
tar -xvf phpMyAdmin-4.9.0.1-all-languages.tar.gz
mv phpMyAdmin-4.9.0.1-all-languages /var/www/html/phpmyadmin
chown -R www-data:www-data /var/www/html/phpmyadmin

#start server
service mysql restart
service php7.3-fpm start
service nginx start

/bin/bash
