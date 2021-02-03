웹 UI 대시보드 설정 방법
(https://fliedcat.tistory.com/171)<br>

minikube 설치 방법
(https://medium.com/@cratios48/minikube-%EC%84%A4%EC%B9%98-%EB%B0%8F-%ED%99%9C%EC%9A%A9-4a63ddbc7fcb)
minikube start --no-vtx-check<br>
이렇게 해야지만 에러가 발생하지 않고 정상적으로 minikube가 설치된다. <br>

- virtual box에서 리눅스 깔고 난 후에 ubuntu에서 minikube 설치방법

(https://zetawiki.com/wiki/%EB%A6%AC%EB%88%85%EC%8A%A4_minikube_%EC%84%A4%EC%B9%98)<br>
이 링크를 그냥 그대로 따라한다. 그런데 그렇게 하면 버전때문에 conntrack 설치해야 된다는 에러가 뜬다. 그래서 `sudo apt-get install conntrack` 으로 conntrack 설치함. 근데 이 링크로 하다가 마지막에 "minikube start --cpus 4 --memory 4096" 이 부분은 실행하지 않는다. 대신에 아래 링크를 참고한다. <br>
(https://vovaprivalov.medium.com/setup-minikube-on-virtualbox-7cba363ca3bc)<br>
여기 링크에서는 

`export CHANGE_MINIKUBE_NONE_USER=true`
`echo ‘export CHANGE_MINIKUBE_NONE_USER=true’ >> ~/.bashrc`
`sudo -E minikube start --vm-driver=none`
이 부분을 참고해서 이렇게 start를 하면 된다. <br>


