웹 UI 대시보드 설정 방법
(https://fliedcat.tistory.com/171)<br>

minikube 설치 방법
(https://medium.com/@cratios48/minikube-%EC%84%A4%EC%B9%98-%EB%B0%8F-%ED%99%9C%EC%9A%A9-4a63ddbc7fcb)
minikube start --no-vtx-check<br>
이렇게 해야지만 에러가 발생하지 않고 정상적으로 minikube가 설치된다. <br>

- virtual box에서 리눅스 깔고 난 후에 ubuntu에서 minikube 설치방법

`sudo install conntrack` 으로 conntrack 설치함.
아래 링크에서 minikube를 설치하지 않고 설치는 공홈에서 실시함(version 때문에)
그리고 kubectl 부터는 아래 링크를 따라했는데 마지막에 kubectl 버전이 낮다고 해서
`sudo minikube kubectl -- get pods -A` 명령어를 침
아래 링크에서 chmod +x minikube && sudo mv minikube /usr/local/bin/ 이 부분은 실행하지 않음. 공홈에서 받으면 알아서 됨.
(https://vovaprivalov.medium.com/setup-minikube-on-virtualbox-7cba363ca3bc)<br>

