
openrc

touch /run/openrc/softlevel

echo "Install modfication.."
/usr/bin/mysql_install_db


echo "starting mariadb"
rc-service mariadb start

echo "Apllying DataBase"

echo "CREATE DATABASE wordpress;" | mysql -u root

echo "CREATE USER 'donglee'@'%' identified by 'donglee';" | mysql -u root

echo "GRANT ALL PRIVILEGES ON wordpress.* TO 'donglee'@'%';" | mysql -u root

echo "FLUSH PRIVILEGES;" | mysql -u root

mysql -u root wordpress  < mysql-service.sql

/usr/bin/mysqld_safe --datadir="/var/lib/mysql"

telegraf & tail -f /dev/null