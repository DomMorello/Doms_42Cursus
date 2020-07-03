# ft_printf (42 school)

### Score 100 / 100 
## Subject
> Write a library that contains ft_printf, a function that will mimic the real printf<br>
> C 표준함수인 printf 함수의 일부 기능을 똑같이 작동하도록 재구현한 프로그램입니다.

## Compile
- git clone https://github.com/DomMorello/ft_printf.git
- cd ft_printf
- make
- gcc libftprintf.a test.c<br>
- ./a.out

test.c is not included in this repo so you can make one like this:

test.c
```
    # include "./ft_printf.h"

    int main()
    {
        int a;

        a = 42;
        ft_printf("%d %s\n", a, "hello world");
        return (0);
    }
```
this code should give back:
```
42 hello world
```

test.c 파일은 이 저장소에 포함돼있지 않습니다. 위와 같은 코드를 직접 만들어서 테스트해보십시오.<br>
위 예제 코드를 실행하면 위와 같은 결과를 터미널 창에 출력할 것입니다. <br>

## Requirements
- The program does not do the buffer management like the real printf
- It manages the following conversions: cspdiuxX%
- It manages any combination of the following flags: ’- 0 . *’ and minimum field
width with all conversions
<br><br>
- 이 프로그램은 실제 표준라이브러리 printf함수와는 다르게 버퍼관리를 하는 방식으로 작동하지 않습니다.
- 다음과 같은 서식지정자를 사용할 수 있습니다: cspdiuxX%
- 다음과 같은 플래그를 어떤 조합으로 사용해도 정상적으로 처리합니다: '- 0 . *' 와 모든 서식지정자에 사용 가능한 출력필드 폭 설정

#### Contact: zuzudnf@gmail.com