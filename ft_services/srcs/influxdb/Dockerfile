# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/18 22:32:14 by marvin            #+#    #+#              #
#    Updated: 2021/02/18 22:32:41 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM    alpine:3.12

LABEL   maintainer="donglee@student.42seoul.kr"

RUN     apk update
RUN     apk add influxdb
RUN     apk add supervisor
# RUN     apk add telegraf --repository http://dl-3.alpinelinux.org/alpine/edge/testing/ --allow-untrusted --no-cache
RUN     wget https://dl.influxdata.com/telegraf/releases/telegraf-1.14.0-static_linux_amd64.tar.gz && \
	    tar -C . -xzf telegraf-1.14.0-static_linux_amd64.tar.gz && \
	    chmod +x telegraf/telegraf && \
	    cp telegraf/telegraf /usr/bin/ && \
	    rm -rf telegraf-1.14.0-static_linux_amd64.tar.gz telegraf/ && mkdir -p /etc/telegraf

COPY    /srcs/build.sh    .

RUN     mkdir -p /etc/telegraf

COPY    /srcs/supervisord.conf  /etc/supervisord.conf
COPY    /srcs/telegraf.conf /etc/telegraf/

RUN     chmod +x build.sh

CMD     sh build.sh

EXPOSE  8086    8088