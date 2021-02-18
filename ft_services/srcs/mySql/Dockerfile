# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/18 22:36:01 by marvin            #+#    #+#              #
#    Updated: 2021/02/18 22:36:23 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM    alpine:3.12

RUN     apk update
RUN     apk add mariadb mariadb-common mariadb-client openrc
# RUN     apk add telegraf --repository http://dl-3.alpinelinux.org/alpine/edge/testing/ --allow-untrusted --no-cache
RUN     wget https://dl.influxdata.com/telegraf/releases/telegraf-1.14.0-static_linux_amd64.tar.gz && \
	    tar -C . -xzf telegraf-1.14.0-static_linux_amd64.tar.gz && \
	    chmod +x telegraf/telegraf && \
	    cp telegraf/telegraf /usr/bin/ && \
	    rm -rf telegraf-1.14.0-static_linux_amd64.tar.gz telegraf/ && mkdir -p /etc/telegraf
RUN     apk add supervisor
RUN     mkdir -p /etc/telegraf

COPY    /srcs/telegraf.conf /etc/telegraf/
COPY    /srcs/run.sh    .
COPY    /srcs/build.sh    .
COPY    /srcs/supervisord.conf  /etc/supervisord.conf
COPY    /srcs/my.cnf     /etc/mysql/my.cnf
COPY    /srcs/mysql-service.sql     .

RUN     chmod +x build.sh

CMD     sh build.sh