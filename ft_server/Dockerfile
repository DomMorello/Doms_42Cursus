FROM debian:buster
MAINTAINER domMorello <zuzudnf@gmail.com>

COPY ./srcs/default /tmp/
COPY ./srcs/wp-config.php /tmp/
COPY ./srcs/set.sql /tmp/
COPY ./srcs/start.sh ./

CMD bash start.sh
