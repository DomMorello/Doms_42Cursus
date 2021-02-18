# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hyeonkim <hyeonkim@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/16 11:20:01 by molabhai          #+#    #+#              #
#    Updated: 2021/02/18 13:24:53 by hyeonkim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM    alpine:3.12

LABEL   maintainer="molabhai@student.1337.ma"

RUN     apk update

RUN     apk add php wget php7-fpm phpmyadmin php-mbstring php-gettext  php7-common php7-iconv php7-json php7-gd php7-curl php7-xml php7-mysqli php7-imap php7-cgi fcgi php7-pdo php7-pdo_mysql php7-soap php7-xmlrpc php7-posix php7-mcrypt php7-gettext php7-ldap php7-ctype php7-dom

# RUN     apk add telegraf --repository http://dl-3.alpinelinux.org/alpine/edge/testing/ --allow-untrusted --no-cache
RUN     wget https://dl.influxdata.com/telegraf/releases/telegraf-1.14.0-static_linux_amd64.tar.gz && \
	    tar -C . -xzf telegraf-1.14.0-static_linux_amd64.tar.gz && \
	    chmod +x telegraf/telegraf && \
	    cp telegraf/telegraf /usr/bin/ && \
	    rm -rf telegraf-1.14.0-static_linux_amd64.tar.gz telegraf/ && mkdir -p /etc/telegraf

RUN     apk add nginx

RUN     apk add supervisor

RUN     mkdir -p /var/www/phpmyadmin

RUN     cd /var/www/phpmyadmin

COPY    /srcs/nginx.conf    /etc/nginx/nginx.conf

COPY    /srcs/config.inc.php .

COPY    /srcs/supervisord.conf  /etc/supervisord.conf

RUN     mkdir -p /etc/telegraf

RUN     mkdir   /run/nginx

COPY    /srcs/telegraf.conf     /etc/telegraf/

COPY    /srcs/build.sh    .

RUN     chmod +x build.sh

CMD     sh build.sh

EXPOSE  5000