# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    setup.sh                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: donglee <donglee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/18 14:04:36 by donglee           #+#    #+#              #
#    Updated: 2021/02/18 14:06:43 by donglee          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!	bin/bash

#eval $(docker-machine env default)

export MINIKUBE_HOME=~/goinfre

tput bold; echo "-------------------Minikube starting--------------------"
minikube  start --driver=virtualbox

eval $(minikube docker-env)

tput bold; echo "-------------------Creating Dashboard-------------------"
minikube dashboard &

# Building Dockerfile

tput bold; echo "-------------------Building Nginx-----------------------"
docker build -t nginx_service       ./srcs/nginx
tput bold; echo "-------------------Building Ftps------------------------"
docker build -t ftps_service        ./srcs/ftps
tput bold; echo "-------------------Building MySql-----------------------"
docker build -t mysql_service       ./srcs/mySql
tput bold; echo "-------------------Building Wordpress-------------------"
docker build -t wordpress_service   ./srcs/wordpress
tput bold; echo "-------------------Building PhpMyAdmin------------------"
docker build -t phpmyadmin_service  ./srcs/php_my_admin
tput bold; echo "-------------------Building Grafana---------------------"
docker build -t grafana_service     ./srcs/grafana
tput bold; echo "-------------------Building InfluxDB--------------------"
docker build -t influxdb_service    ./srcs/influxdb

# Installing Metallb
tput bold; echo "-------------------MetalLb Installation-----------------"
kubectl apply -f https://raw.githubusercontent.com/metallb/metallb/v0.9.3/manifests/namespace.yaml
kubectl apply -f https://raw.githubusercontent.com/metallb/metallb/v0.9.3/manifests/metallb.yaml
# On first install only
kubectl create secret generic -n metallb-system memberlist --from-literal=secretkey="$(openssl rand -base64 128)"

# Creating Pods and Service
tput bold; echo "------------------Service And Deployment Creation--------"

tput bold; echo "------------------Creation of Config Map-------------------"
kubectl create -f ./srcs/yaml/configMap.yaml
tput bold; echo "------------------Creation of Ftps-------------------------"
kubectl create -f ./srcs/yaml/ftps.yaml
tput bold; echo "------------------Creation of Nginx------------------------"
kubectl create -f ./srcs/yaml/nginx.yaml
tput bold; echo "------------------Creation of MySql------------------------"
kubectl create -f ./srcs/yaml/mysql.yaml
tput bold; echo "------------------Creation of Wordpress--------------------"
kubectl create -f ./srcs/yaml/wordpress.yaml
tput bold; echo "------------------Creation of PhpMyAdmin-------------------"
kubectl create -f ./srcs/yaml/phpmyadmin.yaml
tput bold; echo "------------------Creation of Grafana----------------------"
kubectl create -f ./srcs/yaml/grafana.yaml
tput bold; echo "------------------Creation of InfluxDb---------------------"
kubectl create -f ./srcs/yaml/influxdb.yaml