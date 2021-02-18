# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Dockerfile                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: donglee <donglee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/18 15:57:45 by donglee           #+#    #+#              #
#    Updated: 2021/02/18 16:42:02 by donglee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FROM 	alpine:3.12

LABEL   maintainer="donglee@student.42seoul.kr"

RUN 	apk update
RUN		apk add vsftpd
RUN     apk add wget

# RUN     apk add telegraf --repository http://dl-3.alpinelinux.org/alpine/edge/testing/ --allow-untrusted --no-cache
RUN     wget https://dl.influxdata.com/telegraf/releases/telegraf-1.14.0-static_linux_amd64.tar.gz && \
	    tar -C . -xzf telegraf-1.14.0-static_linux_amd64.tar.gz && \
	    chmod +x telegraf/telegraf && \
	    cp telegraf/telegraf /usr/bin/ && \
	    rm -rf telegraf-1.14.0-static_linux_amd64.tar.gz telegraf/ && mkdir -p /etc/telegraf

RUN  	apk add openssl
RUN     apk add supervisor

COPY 	/srcs/vsftpd.conf 	.
COPY 	/srcs/vsftpduserlist.conf  /etc/vsftpduserlist.conf
COPY	/srcs/vsftpd.pem		.

RUN 	mkdir /etc/certs
RUN     mkdir -p /etc/telegraf

COPY    /srcs/telegraf.conf /etc/telegraf/
COPY    /srcs/supervisord.conf  /etc/supervisord.conf

RUN 	cp vsftpd.pem /etc/certs
RUN  	cp vsftpd.conf /etc/vsftpd/vsftpd.conf
RUN  	{ echo "labhairi"; echo "labhairi";} | adduser donglee
RUN 	mkdir /home/donglee/ftp
RUN 	chown nobody:nogroup /home/donglee/ftp/
RUN 	chmod a-w /home/donglee/ftp/
RUN 	mkdir /home/donglee/ftp/files
RUN 	chown donglee:donglee /home/donglee/ftp/files

COPY 	/srcs/build.sh	/usr/sbin

RUN 	chmod +x /usr/sbin/build.sh

CMD 	sh /usr/sbin/build.sh

EXPOSE 	21  20 31110 31111
