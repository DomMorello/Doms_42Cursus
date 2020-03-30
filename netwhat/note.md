newtwhat
===============
<details>
<summary style="font-size:15pt"> #1 What is an IP address</summary>
<ul>
<li>IP(Internet Protocol) Address
<li>��ǻ�� ��Ʈ��ũ���� ��ġ���� ���θ� �ν��ϰ� ����� �ϱ� ���ؼ� ����ϴ� Ư���� ��ȣ</li>
<li>IP�ּҴ� 32�ڸ� 2������ �Ǿ�����(10������ ǥ��). ���� IP�ּ��� ������ 0 ~ 2^32 (�� 42�� 9õ�� ����).
<li>IPv4 : 32bits(4���� Octet)
<li>IPv6 : 128bits
<li>��Ʈ��ũ �ּҴ� ȣ��Ʈ �ּҸ� �����ϴ� ��ǥ �ּ�, ȣ��Ʈ �ּҴ� ���������� �Ҵ�� �ּ�
</ul>
</details>

<details>
<summary style="font-size:15pt"> #2 What is a Netmask</summary>
<ul>
<li>0�� 1�� �����Ͽ� ȣ��Ʈ ��ǻ���� �ּ� �κи� IPv4 IP �ּ� �ڿ� ����ų� ���͸��ϵ��� �ϴ� ���ڿ��̴�. ����ũ�� ���̳ʸ� 1�� �����ϸ� IP �ּ��� ��Ʈ��ũ ID �κ��� 0���� ��ȯ�ȴ�. ������ ��Ÿ���� 2���� 0�� ȣ��Ʈ ID�� �����Ѵ�. �Ϲ������� ���Ǵ� �ݸ���ũ�� ��255.255.255.0���̸� �ִ� 255���� ȣ��Ʈ ��ǻ�͸� ������ �� �ִ� C Ŭ���� ������� ���� ���ȴ�.
<li>��Ʈ��ũ �ּ� �κ��� ��Ʈ�� 1�� ġȯ�� ���� �ݸ���ũ
</ul>
</details>

<details>
<summary style="font-size:15pt"> #3 What is the subnet of an IP with Netmask</summary>
<ul>
<li>IP Ŭ������ ��ȿ�������� ���� subnet�̶�� ������ �����ϰ� ��. 
<li>IP�ּҿ� ����ݸ���ũ�� �� AND �����ϸ� ����ݳ�Ʈ��ũ�� ���� �� �ִ�.
<li>����ݸ���ũ�� AŬ����, BŬ����, CŬ������ �⺻ ����ݸ���ũ���� ���� �� �ִ� ��Ʈ��ũ������ ȣ��Ʈ������ �� �ɰ��� �� ȿ�������� ��������ϴ� ���̴�. �׷��� ������ ���� ��� CŬ����(3���׵������ ��Ʈ��ũ�� �����) �̻����� 4���׵� ������ 5�ڸ� 2������ ��Ʈ��ũ �������� Ȯ���ϰ� ȣ��Ʈ ������ 3�ڸ� 2������ �Ҵ������ν� �⺻����ݸ���ũ�� Ŀ���� �� ������ ��������� ������ �� �ִ�.
<li>IP�ּ� �ڿ� /24 ���� �͵��� Prefix(���ξ�)�� ����� ����ũ�� bit ���� �ǹ�
<li>��������� ���� Network ID�� Ȯ���ϸ� �Ҵ��� �� �ִ� ��Ʈ��ũ�� ���� ������. ������ ��Ʈ��ũ�� �и��ǹǷ� ���ΰ� ����ϱ� ���ؼ��� ����͸� ���Ͽ����� �����ϰ� �˴ϴ�. ���� �� ��Ʈ��ũ�� ���� �ִ� ȣ��Ʈ���� ���� ������ �����ϱ⿡ ����ͱ��� ��ġ�� �ʰ� ����� �� �ִ�. 
</ul>
</details>

<details>
<summary style="font-size:15pt"> #4 What is the broadcast address of a subnet</summary>
<ul>
<li>��ε�ĳ����: �۽� ȣ��Ʈ�� ������ �����Ͱ� ��Ʈ��ũ�� ����� ��� ȣ��Ʈ�� ���۵Ǵ� ���
<li>��� Network ID ���� ù ��° �ּҴ� Network address�� ���̰� ������ �ּҴ� Broadcast �� ����. (ȣ��Ʈ ID bit�� ��� 0�ΰ�� Network address, ��� 1�� ��� Broadcast)
<li>IP �ּҿ� subnet mask�� AND �����ؼ� �� ��Ʈ��ũ �ּҿ��� ����� ����ũ�� ��Ʈ 0�� ���� 1�� �ٲ��ָ� ��ε�ĳ��Ʈ �ּҰ� �ȴ�.
</ul>
</details>

<details>
<summary style="font-size:15pt"> #5 What are the different ways to represent an ip address with the Netmask</summary>
<ul>
<li></li>
</ul>
</details>

<details>
<summary style="font-size:15pt"> #6 What are the differences between public and private IPs</summary>
<h3>public IP</h3>
<ul>
<li>���α������ ������ ������ IP�ּ�
<li>���� IP�ּҴ� �ܺο� �����Ǿ� �־� �� IP�ּҸ� ���� ȣ��Ʈ �� ���������� ����� �� ����. ���� ���� IP�ּҸ� ����Ϸ��� ���� ��� �ݵ�� �ʿ���.
</ul>
<h3>private IP</h3>
<ul>
<li>�ܺο� �������� ���� �м��� IP �ּ�
<li>�ּ� �뿪�� 3���� �����Ǿ� �ִ�. 
<li>���ͳ� �����⸦ ��ġ���� �� ���ͳ� ������ IP�� ���� IP�� ���� �ǰ� �����⿡ ����� ���ο� ��⿡ ������ �缳 IP�� �Ҵ�ȴ�. 
</ul>
</details>

<details>
<summary style="font-size:15pt"> #7 What is a class of IP addresses</summary>
<ul>
<li>1.jpg(https://engkimbs.tistory.com/621)
<li>Ŭ���� A: ��Ը� ��Ʈ��ũ ȯ�濡 ��� 
<li>Ŭ���� B: �߱Ը� ��Ʈ��ũ ȯ�濡 ���
<li>Ŭ���� C: �ұԸ� ��Ʈ��ũ ȯ�濡 ���
<li>Ŭ���� D: ��Ƽĳ��Ʈ�� 
<li>Ŭ���� E: ����/���߿� IP�ּ� Ȥ�� �̷��� ����ϱ� ���� ���ܳ��� ��
<li>2.jpg(https://engkimbs.tistory.com/621)
</ul>
</details>

<details>
<summary style="font-size:15pt"> #8 What is TCP</summary>
<ul>
<li></li>
</ul>
</details>

<details>
<summary style="font-size:15pt"> #9 What is UDP</summary>
<ul>
<li></li>
</ul>
</details>

<details>
<summary style="font-size:15pt"> #10 What are the network layers</summary>
<ul>
<li></li>
</ul>
</details>

<details>
<summary style="font-size:15pt"> #11 What is the OSI model</summary>
<ul>
<li></li>
</ul>
</details>

<details>
<summary style="font-size:15pt"> #12 What is a DHCP server and the DHCP protocol</summary>
<ul>
<li></li>
</ul>
</details>

<details>
<summary style="font-size:15pt"> #13 What is a DNS server and the DNS protocol</summary>
<ul>
<li></li>
</ul>
</details>

<details>
<summary style="font-size:15pt"> #14 What are the rules to make 2 devices communicate using IP addresses</summary>
<ul>
<li></li>
</ul>
</details>

<details>
<summary style="font-size:15pt"> #15 How does routing work with IP</summary>
<ul>
<li></li>
</ul>
</details>

<details>
<summary style="font-size:15pt"> #16 What is a default gateway for routing</summary>
<ul>
<li></li>
</ul>
</details>

<details>
<summary style="font-size:15pt"> #17 What is a port from an IP point of view and what is it used for when connecting to another device</summary>
<ul>
<li></li>
</ul>
</details>

[��ó]
- (https://engkimbs.tistory.com/621)
- (https://www.scienceall.com/%EB%84%B7%EB%A7%88%EC%8A%A4%ED%81%ACnetmask/)
- (https://limkydev.tistory.com/166)
