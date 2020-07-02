# ft_server

## Requirements
- I set up a web server with Nginx, in only one docker container. The
container OS must be debian buster
- This web server is able to run several services at the same time. The services
are WordPress website, phpMyAdmin and MySQL. SQL database in the server works with the WordPress and phpMyAdmin
- This server uses the SSL protocol
- Depending on the url, the server redirects to the correct website
- The server is running with an autoindex that is able to be disabled
<br><br>
- 하나의 docker container 안에 Nginx를 이용한 서버를 구현했고 컨테이너의 OS는 debian buster 입니다.
- WordPress website, phpMyAdmin, MySQL 서비스를 동시애 작동할 수 있습니다. 서버에 연결된 SQL 데이터베이스는 WordPress와 phpMyAdmin와 상호작용합니다.
- 이 서버는 SSL protocol을 사용합니다.
- URL에 따라서 서버는 정확한 웹사이트로 리다이렉트 합니다.
- 이 서버는 autoindex 를 사용할 수 있고 autoindex를 작동시키지 않을 수도 있습니다.

## Run
CMD build:
```
$> docker build -t name .
```
CMD run:
```
$> docker run --name aname -it -p 80:80 -p 443:443 name
```

#### Contact: zuzudnf@gmail.com