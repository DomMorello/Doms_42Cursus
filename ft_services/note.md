
- virtual box���� ������ ��� �� �Ŀ� ubuntu���� minikube ��ġ���

(https://zetawiki.com/wiki/%EB%A6%AC%EB%88%85%EC%8A%A4_minikube_%EC%84%A4%EC%B9%98)<br>
�� ��ũ�� �׳� �״�� �����Ѵ�. �׷��� �׷��� �ϸ� ���������� conntrack ��ġ�ؾ� �ȴٴ� ������ ���. �׷��� `sudo apt-get install conntrack` ���� conntrack ��ġ��. �ٵ� �� ��ũ�� �ϴٰ� �������� "minikube start --cpus 4 --memory 4096" �� �κ��� �������� �ʴ´�. ��ſ� �Ʒ� ��ũ�� �����Ѵ�. <br>
(https://vovaprivalov.medium.com/setup-minikube-on-virtualbox-7cba363ca3bc)<br>
���� ��ũ������ 

`export CHANGE_MINIKUBE_NONE_USER=true`
`echo ��export CHANGE_MINIKUBE_NONE_USER=true�� >> ~/.bashrc`
`sudo -E minikube start --vm-driver=none`
�� �κ��� �����ؼ� �̷��� start�� �ϸ� �ȴ�. <br>
