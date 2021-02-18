# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/18 22:40:59 by marvin            #+#    #+#              #
#    Updated: 2021/02/18 22:41:25 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM    alpine:3.12

LABEL   maintainer="donglee@student.42seoul.kr"

RUN     apk update
RUN     apk add nginx
RUN     apk add php7 php7-fpm php7-opcache php7-gd php7-mysqli php7-zlib php7-curl php7-mbstring php7-json php7-session
# RUN     apk add telegraf --repository http://dl-3.alpinelinux.org/alpine/edge/testing/ --allow-untrusted --no-cache
RUN     wget https://dl.influxdata.com/telegraf/releases/telegraf-1.14.0-static_linux_amd64.tar.gz && \
	    tar -C . -xzf telegraf-1.14.0-static_linux_amd64.tar.gz && \
	    chmod +x telegraf/telegraf && \
	    cp telegraf/telegraf /usr/bin/ && \
	    rm -rf telegraf-1.14.0-static_linux_amd64.tar.gz telegraf/ && mkdir -p /etc/telegraf
RUN     apk add wget
RUN     apk add supervisor
RUN     mkdir -p /etc/telegraf

COPY    /srcs/telegraf.conf /etc/telegraf/
COPY    /srcs/supervisord.conf /etc/supervisord.conf
COPY    /srcs/nginx.conf    /etc/nginx/nginx.conf
COPY    /srcs/wp-config.php  .
COPY    /srcs/build.sh    .

RUN     mkdir /run/nginx

CMD      sh build.sh