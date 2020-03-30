newtwhat
===============
<details>
<summary style="font-size:15pt"> #1 What is an IP address</summary>
<ul>
<li>IP(Internet Protocol) Address
<li>컴퓨터 네트워크에서 장치들이 서로를 인식하고 통신을 하기 위해서 사용하는 특수한 번호</li>
<li>IP주소는 32자리 2진수로 되어있음(10진수로 표현). 따라서 IP주소의 범위는 0 ~ 2^32 (약 42억 9천개 정도).
<li>IPv4 : 32bits(4개의 Octet)
<li>IPv6 : 128bits
<li>네트워크 주소는 호스트 주소를 포함하는 대표 주소, 호스트 주소는 개별적으로 할당된 주소
</ul>
</details>

<details>
<summary style="font-size:15pt"> #2 What is a Netmask</summary>
<ul>
<li>0과 1을 결합하여 호스트 컴퓨터의 주소 부분만 IPv4 IP 주소 뒤에 남기거나 필터링하도록 하는 문자열이다. 마스크가 바이너리 1로 시작하면 IP 주소의 네트워크 ID 부분이 0으로 변환된다. 다음에 나타나는 2진수 0은 호스트 ID를 유지한다. 일반적으로 사용되는 넷마스크는 ‘255.255.255.0’이며 최대 255대의 호스트 컴퓨터를 수용할 수 있는 C 클래스 서브넷을 위해 사용된다.
<li>네트워크 주소 부분의 비트를 1로 치환한 것이 넷마스크
</ul>
</details>

<details>
<summary style="font-size:15pt"> #3 What is the subnet of an IP with Netmask</summary>
<ul>
<li>IP 클래스의 비효율성으로 인해 subnet이라는 개념이 등장하게 됨. 
<li>IP주소와 서브넷마스크를 논리 AND 연산하면 서브넷네트워크를 구할 수 있다.
<li>서브넷마스크는 A클래스, B클래스, C클래스의 기본 서브넷마스크에서 가질 수 있는 네트워크영역과 호스트영역을 더 쪼개서 더 효율적으로 서브네팅하는 것이다. 그렇기 때문에 예를 들어 C클래스(3옥테드까지만 네트워크로 사용함) 이상으로 4옥테드 영역에 5자리 2진수를 네트워크 영역으로 확대하고 호스트 영역을 3자리 2진수를 할당함으로써 기본서브넷마스크로 커버할 수 없었던 서브네팅을 구현할 수 있다.
<li>IP주소 뒤에 /24 같은 것들은 Prefix(접두어)로 서브넷 마스크의 bit 수를 의미
<li>서브넷팅을 통해 Network ID를 확장하면 할당할 수 있는 네트워크의 수가 증가함. 하지만 네트워크가 분리되므로 서로가 통신하기 위해서는 라우터를 통하여서만 가능하게 됩니다. 물론 각 네트워크에 속해 있는 호스트들은 같은 영역에 존재하기에 라우터까지 거치지 않고도 통신할 수 있다. 
</ul>
</details>

<details>
<summary style="font-size:15pt"> #4 What is the broadcast address of a subnet</summary>
<ul>
<li>브로드캐스팅: 송신 호스트가 전송한 데이터가 네트워크에 연결된 모든 호스트에 전송되는 방식
<li>모든 Network ID 에서 첫 번째 주소는 Network address로 쓰이고 마지막 주소는 Broadcast 로 쓰임. (호스트 ID bit가 모두 0인경우 Network address, 모두 1인 경우 Broadcast)
<li>IP 주소와 subnet mask를 AND 연산해서 얻어낸 네트워크 주소에서 서브넷 마스크의 비트 0을 전부 1로 바꿔주면 브로드캐스트 주소가 된다.
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
<li>공인기관에서 인증한 공개형 IP주소
<li>공인 IP주소는 외부에 공개되어 있어 이 IP주소를 통해 호스트 간 직접적으로 통신할 수 있음. 따라서 공인 IP주소를 사용하려면 보안 장비가 반드시 필요함.
</ul>
<h3>private IP</h3>
<ul>
<li>외부에 공개되지 않은 패쇄형 IP 주소
<li>주소 대역이 3개로 고정되어 있다. 
<li>인터넷 공유기를 설치했을 때 인터넷 공유기 IP가 기존 IP의 값이 되고 공유기에 연결된 새로운 기기에 고정된 사설 IP가 할당된다. 
</ul>
</details>

<details>
<summary style="font-size:15pt"> #7 What is a class of IP addresses</summary>
<ul>
<li>1.jpg(https://engkimbs.tistory.com/621)
<li>클래스 A: 대규모 네트워크 환경에 사용 
<li>클래스 B: 중규모 네트워크 환경에 사용
<li>클래스 C: 소규모 네트워크 환경에 사용
<li>클래스 D: 멀티캐스트용 
<li>클래스 E: 연구/개발용 IP주소 혹은 미래에 사용하기 위해 남겨놓은 것
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

[출처]
- (https://engkimbs.tistory.com/621)
- (https://www.scienceall.com/%EB%84%B7%EB%A7%88%EC%8A%A4%ED%81%ACnetmask/)
- (https://limkydev.tistory.com/166)
