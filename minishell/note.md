# minishell
(https://ko.wikipedia.org/wiki/Echo_(%EB%AA%85%EB%A0%B9%EC%96%B4))echo 위키설명 -> 도움 안 됨<br>
(https://eoworld.tistory.com/entry/Linux-%EB%A6%AC%EB%88%85%EC%8A%A4-%EB%AA%85%EB%A0%B9%EC%96%B4-unset) unset 명령어 설명 -> unset 은 env에 들어가있는 환경변수를 없애준다. 사용법: unset dom 하면 dom이라는 이름의 env 내 환경변수가 삭제된다.<br>
- (https://www.gnu.org/software/bash/manual/html_node/Redirections.html)Redirection -> 공식문서라서 계속 참고해야 하지만 읽기 ㅈㄴ싫음<br>

(https://ko.wikipedia.org/wiki/%EB%A6%AC%EB%8B%A4%EC%9D%B4%EB%A0%89%EC%85%98)리다이렉션 위키 -> 리다이렉션의 기본적인 사용법 참고하기 좋음<br>
(https://neul-carpediem.tistory.com/70)리다이렉션과 파이프에 대한 설명 -> 파이프 사용법에 대해 알게 됨<br>
(http://www.linuxhowtos.org/Tips%20and%20Tricks/Protecting%20files%20with%20noclobber.htm)noclobber옵션에 대한 설명 -> 필요없음 <br>
(https://blog.gaerae.com/2015/01/bash-hello-world.html)bash shell 기본 ->ㅇㅋ<br>
- (https://wiki.kldp.org/HOWTO/html/Adv-Bash-Scr-HOWTO/exit-status.html)종료상태 확인하는 $? 사용법 errno 등 return 값을 활용해서 해야 할 것 같음<br>

(https://superuser.com/questions/169051/whats-the-difference-between-c-and-d-for-unix-mac-os-x-terminal)ctrl d ctrl c 차이점 스택오버플로 -> 시그널 키워드를 얻음<br>
(https://en.wikipedia.org/wiki/Signal_(IPC)#SIGQUIT)시그널 관련한 설명 위키피디아 -> 공부함<br>
(https://man7.org/linux/man-pages/man2/fork.2.html) man fork<br>
(https://codetravel.tistory.com/23)fork 함수 블로그 -> <br>
- (https://man7.org/linux/man-pages/man2/waitpid.2.html)man wait, waitpid<br>
- (https://linux.die.net/man/2/wait3()) man wait3 wait4<br>
waitpid를 대신 쓰는 것이 좋다고 한다. <br>
- (https://codetravel.tistory.com/30)wait 함수 사용 블로그 -> 느린 시스템콜로 인해 발생하는 오류 이슈 설명있음. 에러 발생시 리턴하는 함수들에 대한 설명이 있어서 테스트 할 때 활용하면 좋을 것 같음. <br>

(http://forum.falinux.com/zbxe/index.php?document_srl=408545&mid=C_LIB)wait함수 설명 블로그<br>
- (https://man7.org/linux/man-pages/man7/signal.7.html)man signal<br>
- (https://blockdmask.tistory.com/23)siganl 함수 블로그 -> signal 매크로와 함수들에 대한 간략한 설명<br>

(https://www.joinc.co.kr/w/man/2/waitpid)waitpid 함수 설명<br>
- (http://forum.falinux.com/zbxe/index.php?category=520920&document_srl=413771&mid=C_LIB) kill함수에 대한 설명 블로그 -> 설명 잘 돼있음<br>

(https://www.man7.org/linux/man-pages/man3/exit.3.html)man exit<br>
(https://stackoverflow.com/questions/16535335/what-does-least-significant-byte-mean)the least significant byte 설명 스택오버플로<br>
(https://minimonk.net/m/1539?category=309376)getcwd, chdir 함수에 대한 설명 블로그 -> 간단함.<br>
(https://linux.die.net/man/3/getcwd)man getcwd<br>
(https://bodamnury.tistory.com/37)unix stat 함수 설명 블로그 -> 대충 오케이<br>
(https://linux.die.net/man/2/stat)stat man page<br>
- (https://www.it-note.kr/173)stat 함수에 대한 블로그 설명 글 -> stat함수를 사용할 때 printf 로 출력하는 좋은 예시가 있다. 파일에 대해서 어떻게 출력할지 궁금할 때 참고하면 좋음 <br>
- (https://www.it-note.kr/157)execve 함수에 대한 설명 -> 기본적인 사용방법 참고하기 좋음<br>

(http://forum.falinux.com/zbxe/index.php?document_srl=408569&mid=C_LIB)execve 함수에 대한 다른 블로그 설명 -> ㅇㅋ<br>
- (https://stackoverflow.com/questions/29615540/using-execve-in-c)execve 에서 세 번째 매개변수인 환경변수 이차원 배열 사용하는 방법에 대한 질문글. 이 링크가 나중에 필요할진 모르겠지만 아무튼 키 밸유 쌍으로 "PATH=/Users/donglee" 처럼 선언이 돼있어야 된다는 사실을 언급하고 있다. <br>

(https://ehclub.co.kr/1321)dup함수에 대한 설명 블로그 -> ㅇㅋ<br>
- (https://reakwon.tistory.com/80)pipe 함수 블로그 -> 기본 사용법 참고<br>
- (https://man7.org/linux/man-pages/man2/pipe.2.html)man pipe<br>
- (https://www.it-note.kr/24)opendir, readdir, closedir 함수 설명 -> 간단한 사용방법<br>

(https://stackoverflow.com/questions/3740504/why-doesnt-the-cd-command-work-in-my-shell-program)cd관련 스택오버플로 질문 -> 모르겠다<br>
- (https://harm-smits.github.io/42docs/projects/minishell)42docs -> 조언<br>

- (https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)writing your own shell pdf -> 이 방식으로 구현을 하자 이게 본질인 것 같다.<br>
- (https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html) shell 공식문서 참고할 사항들이 있을 거임 <br>

(https://stackoverflow.com/questions/13656344/c-minishell-need-to-kill-zombies-for-pipeline-implementation)about zombie process issue -> <br>
(http://forum.falinux.com/zbxe/index.php?document_srl=413254&mid=C_LIB)signal 함수에 대해서 블로그 -> 장황함<br>
(https://badayak.com/4381)setenv -> 필요없음<br>
- (https://stackoverflow.com/questions/5491775/how-to-write-a-shell-lexer-by-hand)lexer by hand stack overflow<br>
- (https://stackoverflow.com/questions/13636252/c-minishell-adding-pipelines/13640308#13640308)pipeline sof 모르겠지만 일단 그냥 남겨둔다.<br>
- (https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_10)shell grammar 관련 lexer만들때 참고해야 할 것 같다. <br>

(https://en.wikipedia.org/wiki/Abstract_syntax_tree)abstract syntax tree<br>
(https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form)backus-Naur form 이게 뭘까? -> 몰라<br>

- (https://www.gnu.org/software/bash/manual/html_node/Definitions.html#Definitions)shell terms definition -> 참고하자.<br>
(http://keepcalmswag.blogspot.com/2018/06/linux-unix-export-echo_49.html)export 문법<br>
(http://ehpub.co.kr/tag/environ-%EB%B3%80%EC%88%98/)c environ 변수에 대한 공부 <br>
(http://throughkim.kr/2016/12/22/linux-4/)export 명령어<br>