# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/18 22:37:42 by marvin            #+#    #+#              #
#    Updated: 2021/02/18 22:38:21 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM 	    alpine:3.12

LABEL maintainer="donglee@student.42seoul.kr"

RUN  	    apk update
RUN 	    apk add nginx
RUN	        apk add openssl
RUN	        apk add openssh
RUN	        apk add openrc
RUN         apk add supervisor
RUN         apk add wget
RUN	    mkdir	-p /run/nginx
# RUN     apk add telegraf --repository http://dl-3.alpinelinux.org/alpine/edge/testing/ --allow-untrusted --no-cache
RUN     wget https://dl.influxdata.com/telegraf/releases/telegraf-1.14.0-static_linux_amd64.tar.gz && \
	    tar -C . -xzf telegraf-1.14.0-static_linux_amd64.tar.gz && \
	    chmod +x telegraf/telegraf && \
	    cp telegraf/telegraf /usr/bin/ && \
	    rm -rf telegraf-1.14.0-static_linux_amd64.tar.gz telegraf/ && mkdir -p /etc/telegraf

COPY    /srcs/build.sh      .
COPY     /srcs/telegraf.conf /etc/telegraf/
COPY	 /srcs/nginx.key	/etc/ssl/private/nginx.key
COPY    /srcs/nginx.crt	/etc/ssl/certs/nginx.crt
COPY 	/srcs/nginx.conf	/etc/nginx/nginx.conf
COPY    /srcs/supervisord.conf  /etc/supervisord.conf
COPY    /srcs/sshd_config   /etc/ssh/sshd_config
COPY    /srcs/run.sh        .

EXPOSE      80

EXPOSE      443

RUN         chmod +x build.sh

CMD         sh build.sh