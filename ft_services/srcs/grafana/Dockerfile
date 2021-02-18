# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: donglee <donglee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/18 17:00:51 by donglee           #+#    #+#              #
#    Updated: 2021/02/18 17:02:30 by donglee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM alpine:3.12

LABEL   maintainer="donglee@student.42seoul.kr"

RUN     apk update
RUN     apk add wget
# RUN     apk add telegraf --repository http://dl-3.alpinelinux.org/alpine/edge/testing/ --allow-untrusted --no-cache
RUN     wget https://dl.influxdata.com/telegraf/releases/telegraf-1.14.0-static_linux_amd64.tar.gz && \
	    tar -C . -xzf telegraf-1.14.0-static_linux_amd64.tar.gz && \
	    chmod +x telegraf/telegraf && \
	    cp telegraf/telegraf /usr/bin/ && \
	    rm -rf telegraf-1.14.0-static_linux_amd64.tar.gz telegraf/ && mkdir -p /etc/telegraf
RUN     apk add libc6-compat
RUN     apk add supervisor
RUN     wget https://dl.grafana.com/oss/release/grafana-7.1.5.linux-amd64.tar.gz
RUN     tar -zxvf grafana-7.1.5.linux-amd64.tar.gz
RUN     mkdir -p /etc/telegraf

COPY    /srcs/telegraf.conf /etc/telegraf/
COPY    /srcs/supervisord.conf  /etc/supervisord.conf
COPY    /srcs/run.sh        .
COPY    /srcs/build.sh    .
COPY    /srcs/grafana.db   /grafana-7.1.5/data/grafana.db

CMD     sh build.sh

EXPOSE  3000
