# libasm
42 Seoul assembly project

## Subject
> to make a library which has some basic functions with assembly language<br>

> 어셈블리어로 기본적인 함수를 구현하고 이를 라이브러리로 만드는 프로젝트입니다.<br>

## Requirements
- This library is written 64 bits ASM.
- The functions written in assembly code will be compiled with nasm
- I used the Intel syntax, not the AT&T.
- When you fail to call system call in ft_read and ft_write functions, the errno variable will be properly set.
<br><br>
- 이 라이브러리는 64비트 어셈블리로 작성되었습니다.
- 어셈블리어로 작성된 함수들은 nasm으로 컴파일 됩니다.
- 어셈블리로는 AT&T문법이 아닌 Intel 문법 기반으로 작성되었습니다. 
- ft_read와 ft_write함수에서 시스템콜이 실패했을 경우에 errno 변수에 적절한 에러코드가 저장됩니다.
### Functions
- ft_strlen (man 3 strlen)
- ft_strcpy (man 3 strcpy)
- ft_strcmp (man 3 strcmp)
- ft_write (man 2 write)
- ft_read (man 2 read)
- ft_strdup (man 3 strdup)
<br>
## Compile
the program works only in MacOS<br><br>
이 프로그램은 맥 OS환경에서만 실행 가능합니다.<br>

```bash
git clone https://github.com/DomMorello/libasm.git
cd libasm
make            //will make a library
make test       //will compile test file(main.c)
./test          //will test the functions
```

## reference
- nasm tutorial (https://cs.lmu.edu/~ray/notes/nasmtutorial/)<br>
- How to set errno in Assembly (https://stackoverflow.com/questions/15304829/how-to-return-errno-in-assembly)<br>
- 42 docs (https://harm-smits.github.io/42docs/projects/libasm)<br>
- Linux system call table (https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/)<br>

#### Contact: zuzudnf@gmail.com