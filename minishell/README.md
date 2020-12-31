# Minishell (42 school)

## Subject
> The objective of this project is to create a simple bash shell.<br>

> 이 프로그램은 bash shell 프로그램을 재구현한 것입니다.

## Compile
- `git clone https://github.com/DomMorello/minishell.git`
- `cd minishell`
- `make`
- `./minishell`

## Requirements
- Allowed external functions:
- 이 프로그램은 아래의 외부 함수만 사용해서 구현했습니다:
`malloc, free, write, open, read, close, fork, wait,
waitpid, wait3, wait4, signal, kill, exit, getcwd,
chdir, stat, lstat, fstat, execve, dup, dup2, pipe,
opendir, readdir, closedir, strerror, errno`

Your shell should:
- Show a prompt when waiting for a new command
- Search and launch the right executable (based on the PATH variable or by using
relative or absolute path) like in bash
- It must implement the builtins like in bash:
◦ echo with option ’-n’
◦ cd with only a relative or absolute path
◦ pwd without any options
◦ export without any options
◦ unset without any options
◦ env without any options and any arguments
◦ exit without any options
- ; in the command should separate commands like in bash
- ’ and " should work like in bash except for multiline commands
- Redirections < > “>>” should work like in bash except for file descriptor aggregation
- Pipes | should work like in bash
- Environment variables ($ followed by characters) should work like in bash
- $? should work like in bash
- ctrl-C, ctrl-D and ctrl-\ should have the same result as in bash
<br>

프로그램은 다음과 같이 작동해야 합니다:
- 새로운 명령어를 입력할 때까지 프롬프트를 보여야 합니다.
- 실행가능한 명령어들(환경 변수 PATH를 이용하거나 절대경로,상대경로를 사용해서)을 bash처럼 작동해야 합니다.
- 다음과 같은 내부명령어(builtins)를 bash처럼 작동해야 합니다.
◦ echo 명령어를  ’-n’ 옵션이 작동하게끔 실행
◦ cd 명령어를 절대경로나 상대경로로 실행
◦ pwd 명령어 (옵션 없이)
◦ export 명령어 (옵션 없이)
◦ unset 명령어 (옵션 없이)
◦ env 명령어 (옵션이나 인자 없이)
◦ exit 명령어 (옵션 없이)
- 명령어 안에 ; 가 있다면 bash처럼 명령어를 나눠서 작동하게 해야 합니다.
- ' 와 " 는 여러 줄로 입력받는 경우를 제외하고 bash처럼 작동해야 합니다.
- '<' '>' '>>' 리디렉션이 file descriptor를 명시하는 방법은 제외하고 bash처럼 작동해야 합니다.
- 파이프 '|' 가 bash처럼 작동해야 합니다.
- 환경변수($ 다음에 오는 문자열)가 bash처럼 작동해야 합니다.
- $? 가 bash처럼 작동해야 합니다.
- ctrl-C, ctrl-D and ctrl-\ 가 bash와 똑같은 결과를 보여줘야 합니다.

#### Contact: zuzudnf@gmail.com
