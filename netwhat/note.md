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
<li>Transmission Control Protocol
<li> TCP는 근거리 통신망이나 인트라넷, 인터넷에 연결된 컴퓨터에서 실행되는 프로그램 간에 일련의 옥텟을 안정적으로, 순서대로, 에러없이 교환할 수 있게 한다</li>
<li>인터넷상에서 데이터를 메세지의 형태로 보내기 위해 IP와 함께 사용하는 프로토콜
<li>TCP는 웹 브라우저들이 월드 와이드 웹에서 서버에 연결할 때 사용되며, 이메일 전송이나 파일 전송에도 사용된다.
<li>연결형 서비스로 가상 회선 방식을 제공한다
<li>3-way handshaking과정을 통해 연결을 설정하고 4-way handshaking을 통해 해제한다.
<li>흐름 제어 및 혼잡 제어. (흐름제어: 데이터 처리 속도를 조절하여 수신자의 버퍼 오버플로우가 발생하지 않도록 한다. 수신자가 윈도우 값을 조정해서 수신량을 정할 수 있다. 혼잡제어: 네트워크 내의 패킷 수가 넘치지 않게 방지하는 것. 정보 교환량이 많으면 패킷을 조금만 전송해서 혼잡 붕괴 현상을 막는다.)
<li>높은 신뢰성을 보장한다.
<li>UDP보다 속도가 느리다.
<li>전이중(Full-Duplex), 점대점(Point to Point) 방식.
</ul>
<h3>[TCP 서버의 특징]</h3>
<ul>
<li>서버소켓은 연결만을 담당한다.
<li>연결과정에서 반환된 클라이언트 소켓은 데이터의 송수신에 사용된다 서비스로 가상 회선 방식을 제공한다.
<li>서버와 클라이언트는 1대1로 연결된다.
<li>스트림 전송으로 전송 데이터의 크기가 무제한이다.
<li>패킷에 대한 응답을 해야하기 때문에(시간 지연, CPU 소모) 성능이 낮다.
<li>Streaming 서비스에 불리하다.(손실된 경우 재전송 요청을 하므로)
</ul>
</details>

<details>
<summary style="font-size:15pt"> #9 What is UDP</summary>
<ul>
<li>User Datagram Protocol</li>
<li>데이터를 데이터그램 단위로 처리하는 프로토콜
<li>비연결형 서비스로 데이터그램 방식을 제공한다
<li>정보를 주고 받을 때 정보를 보내거나 받는다는 신호절차를 거치지 않는다.
<li>UDP헤더의 CheckSum 필드를 통해 최소한의 오류만 검출한다.
<li>신뢰성이 낮다
<li>TCP보다 속도가 빠르다
</ul>
<h3>[UDP 서버의 특징]</h3>
<ul>
<li>UDP에는 연결 자체가 없어서(connect 함수 불필요) 서버 소켓과 클라이언트 소켓의 구분이 없다.
<li>소켓 대신 IP를 기반으로 데이터를 전송한다.
<li>서버와 클라이언트는 1대1, 1대N, N대M 등으로 연결될 수 있다.
<li>데이터그램(메세지) 단위로 전송되며 그 크기는 65535바이트로, 크기가 초과하면 잘라서 보낸다.
<li>흐름제어(flow control)가 없어서 패킷이 제대로 전송되었는지, 오류가 없는지 확인할 수 없다.
<li>파일 전송과 같은 신뢰성이 필요한 서비스보다 성능이 중요시 되는 경우에 사용된다.
</ul>
</details>

<details>
<summary style="font-size:15pt"> #10 What are the network layers</summary>
<ul>
<li>컴퓨터 네트워킹의 7계층 OSI 모형 가운데 제3계층</li>

<h3>[경로제어 (라우팅)]</h3>
     <li>단말기 혹은 컴퓨터가 어떤 망에 접속되어 있을 때 송신하고자 하는 정보가 망을 통해서 어떻게 상대방 수신측까지 전달되는가를 제어하는 일을 담당
        . 즉, 발신에서 착신까지의 패킷의 경로를 제어
     <li>하나 이상의 복수 통신망을 통한 중계를 하며, 개방시스템간의 데이타를 전송

<h3>[투명성]</h3>
     <li>상위의 Transport Layer (4 layer)가 경로선택과 중계 등 망계층 고유의 기능에
       대하여 의식하지 않도록 투명하게하는 역할

<h3>[논리적 주소체계 부여]</h3>
     <li>라우팅과 관련된 주소의 지정 등 주소체계 정립

<h3>[연결지향성 및 비연결성 서비스 제공]</h3>
     <li>망계층은 상위의 트랜스포트 계층에게 연결지향성 및 비연결성 서비스 모두를 제공
        . 연결지향 서비스는 연결의 설정, 사용, 해제를 위한 프리미티브를 가짐

</ul>
</details>

<details>
<summary style="font-size:15pt"> #11 What is the OSI model</summary>
<ul>
<h3>7계층: Application : User Interface 를 제공하는 계층</h3>
<li>사용자와 직접적으로 상호작용
<li>구글 크롬(Google Chrome), 파이어폭스(Firefox), 사파리(Safari) 등 웹 브라우저와 스카이프(Skype), 아웃룩(Outlook), 오피스(Office) 등
<h3>6계층: Presentation : 데이터의 변환 작업을 하는 계층</h3>
<li>일반적으로 응용프로그램 형식을 준비 또는 네트워크 형식으로 변환하거나 네트워크 형식을 응용프로그램 형식으로 변환하는 것을 나타낸다. 다시 말해 이 계층은 응용프로그램이나 네트워크를 위해 데이터를 “표현”하는 것이다. 대표적인 예로는 데이터를 안전하게 전송하기 위해 암호화, 복호화하는 것인데, 이 작업이 바로 6계층에서 처리된다.
<li>전송하는 데이터의 인코딩, 디코딩, 암호화, 코드 변환 등을 수행
<h3>5계층: Session : 응용 프로그램 간의 연결을 지원해주는 계층</h3>
<li>통신장치 간 상호작용 및 동기화를 제공
<li>연결 세션에서 데이터 교환,  에러 발생 시 복구 관리 => 논리적 연결 담당
<h3>4계층: Transport : 서비스를 구분하고 데이터의 전송 방식을 담당하는 계층</h3>
<li>전송 계층은 최종 시스템 및 호스트 간의 데이터 전송 조율을 담당
<li>보낼 데이터의 용량과 속도, 목적지 등을 처리
<li>전송 계층의 예 중에서 가장 잘 알려진 것이 전송 제어 프로토콜(TCP)이다
<li>종단 간(End-to-End)에 신뢰성 있고 정확한 데이터 전송을 담당
<li>4계층에서 전송 되는 단위 => 세그먼트(Segment), 종단 간의 에러 복구와 흐름 제어 담당
<h3>3계층: Network : 네트워크를 논리적으로 구분하고 연결하는 계층 - 논리적 주소 사용</h3>
<li>다른 여러 라우터를 통한 라우팅을 비롯한 패킷 전달을 담당
<li>중계 노드를 통하여 전송하는 경우, 어떻게 중계할 것인가를 규정
<li>데이터를 목적지까지 가장 안전하고 빠르게 전달 => 라우팅
<h3>2계층: Data link : 물리적 매체에 패킷 데이터를 실어 보내는 계층 - 환경에 맞는 다양한 통신 프로토콜 지원층</h3>
<li>노드 간 데이터 전송을 제공하며 물리 계층의 오류 수정도 처리
<li>2개의 부계층도 존재. 하나는 매체 접근 제어(MAC) 계층, 다른 하나는 논리적 연결 제어(LLC) 계층
<li>물리적인 연결을 통하여 인접한 두 장치간의 신뢰성 있는 정보 전송을 담당
<li>정보의 오류와 흐름을 관리. 안정된 정보 전달
<h3>1계층: Physical : 신호로 변환하여 전송하는 계층</h3>
<li>시스템의 전기적, 물리적 표현을 나타낸다. 케이블 종류, (802.11 무선 시스템에서와 같은) 무선 주파수 링크는 물론 핀 배치, 전압, 물리 요건 등이 포함
<li>전기적, 기계적 특성을 이용하여, 통신 케이블로 전기적 신호(에너지)를 전송
<li>단지 데이터 전달 역할만을 하고, 알고리즘, 오류 제어 기능 존재 X 
</ul>
</details>

<details>
<summary style="font-size:15pt"> #12 What is a DHCP server and the DHCP protocol</summary>
<ul>
<h3>[DHCP Protocol: Dynamic Host Configuration Protocol]</h3>
<li>DHCP는 네트워크 관리자들이 조직 내의 네트워크 상에서 IP 주소를 중앙에서 관리하고 할당해줄 수 있도록 해주는 프로토콜
<li>해당 클라이언트에게 일정 기간 임대
<li>
<h3>[DHCP Server]</h3>

<h3>[DHCP 작동원리]</h3>
<li>DHCP Discover: 단말이 DHCP 서버를 찾기 위한 메시지입니다. 그래서 LAN상에(동일 subent상에) 브로드캐스팅
<li>DHCP Offer: DHCP 서버가 응답하는 메시지. 단순히 DHCP 서버의 존재만을 알리지 않고, 단말에 할당할 IP 주소 정보를 포함한 다양한 "네트워크 정보"를 함께 실어서 단말에 전달.
<li>DHCP Request: 단말은 DHCP Request 메시지를 통해 하나의 DHCP 서버를 선택하고 해당 서버에게 "단말이 사용할 네트워크 정보"를 요청함
<li>DHCP Ack: DHCP 절차의 마지막 메시지로, DHCP 서버가 단말에게 "네트워크 정보"를 전달해 주는 메시지.
</ul>
</details>

<details>
<summary style="font-size:15pt"> #13 What is a DNS server and the DNS protocol</summary>
<ul>
<li>Domain Name Systen 는 호스트의 도메인 이름을 호스트의 네트워크 주소로 바꾸거나 그 반대의 변환을 수행할 수 있도록 하기 위해 개발되었다</li>
<li>DNS 서버는 이름에 대한 요청을 IP 주소로 변환하여 최종 사용자가 도메인 이름을 웹 브라우저에 입력할 때 해당 사용자를 어떤 서버에 연결할 것인지를 제어한다. 이 요청을 쿼리라고 부름
<h3>[DNS Server]</h3>
<li>DNS 리커서 - 리커서는 도서관의 어딘가에서 특정 책을 찾도록 요구받는 사서로 생각할 수 있다. DNS 리커서는 웹 브라우저와 같은 애플리케이션을 통해 클라이언트 컴퓨터로부터 쿼리를 받도록 고안된 서버이다. 일반적으로 리커서는 클라이언트의 DNS 쿼리를 충족시키기 위해 추가 요청을 수행한다한
<li>루트 네임서버 - 루트 서버는 사람이 읽을 수 있는 호스트 이름을 IP 주소로 변환(분해)하는 첫 번째 단계이다. 다른 책장을 가리키는 라이브러리의 색인으로 생각할 수 있으며, 일반적으로 더 특정한 위치에 대한 참조로 사용된다.
<li>TLD 네임서버 - 최상위 도메인 서버(TLD)는 도서관의 특정 책장으로 생각할 수 있다. 이 네임서버는 특정 IP 주소 검색의 다음 단계이며, 호스트 이름의 마지막 부분을 호스팅한다(example.com에서 TLD 서버는 “com”).
<li>권한있는 네임서버 - 이 최종 네임서버는 특정 이름을 해당 정의로 변환할 수 있는 책장의 사전으로 생각할 수 있다. 권한있는 네임서버는 네임서버 쿼리의 마지막 중단점이다. 권한있는 네임서버가 요청한 레코드에 대한 액세스 권한을 가진 경우, 요청한 호스트 이름의 IP 주소를 초기 요청을 한 DNS 리커서(사서)에게 다시 보낸다.
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
<li>Routing: 어떤 네트워크 안에서 통신 데이터를 보낼 최적의 경로를 선택하는 과정</li>
<h3>라우팅 방식 주요 구분</h3>
<li> 고정 라우팅(Fixed Routing) / 정적 라우팅(Static Routing): 미리 정해진 루트를 따라 경로선택 (수동 경로 설정)
<li>동적 라우팅(Dynamic Routing) / 적응적 라우팅(Adaptive Routing): 망의 상태에따라 경로선택 (자동 경로 설정)
<il>
</ul>
</details>

<details>
<summary style="font-size:15pt"> #16 What is a default gateway for routing</summary>
<ul>
<li>Gateway: 컴퓨터 네트워크에서의 게이트웨이는 현재 사용자가 위치한 네트워크(정확히는 세그먼트-segment)에서 다른 네트워크(인터넷 등)로 이동하기 위해 반드시 거쳐야 하는 거점을 의미</li>

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
- (https://mangkyu.tistory.com/15)
- (http://www.ktword.co.kr/abbr_view.php?nav=&m_temp1=439&id=747)
- (https://ko.wikipedia.org/wiki/%EB%8F%99%EC%A0%81_%ED%98%B8%EC%8A%A4%ED%8A%B8_%EA%B5%AC%EC%84%B1_%ED%94%84%EB%A1%9C%ED%86%A0%EC%BD%9C)
- (https://ko.wikipedia.org/wiki/%EB%8F%84%EB%A9%94%EC%9D%B8_%EB%84%A4%EC%9E%84_%EC%8B%9C%EC%8A%A4%ED%85%9C)
- (https://aws.amazon.com/ko/route53/what-is-dns/)<br>
- (https://www.cloudflare.com/ko-kr/learning/dns/what-is-dns/)<br>
- (https://ko.wikipedia.org/wiki/%EB%9D%BC%EC%9A%B0%ED%8C%85)<br>
- (http://www.ktword.co.kr/abbr_view.php?nav=&m_temp1=539&id=345)<br>

