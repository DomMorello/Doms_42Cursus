# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    build.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/18 22:40:22 by marvin            #+#    #+#              #
#    Updated: 2021/02/18 22:40:49 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#! /bin/bash

     wget https://wordpress.org/latest.tar.gz

     tar -xvf latest.tar.gz

     mkdir /var/www/wordpress

     mv wordpress/*      /var/www/wordpress/
     cp wp-config.php  /var/www/wordpress/wp-config.php
     adduser -G www-data -D www-data

    chown -R www-data:www-data /var/www/wordpress
    #telegraf &
    #php-fpm7 & nginx -g 'daemon off;' 

    supervisord  -c /etc/supervisord.conf  & tail -f /dev/null
