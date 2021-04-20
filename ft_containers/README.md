# ft_containers (42 school)

## Subject
> To re-implement C++ containers<br>

> 이 프로그램은 C++ 컨테이너 자료구조들을 재구현한 것입니다.

## Compile
- `git clone https://github.com/DomMorello/minishell.git`
- `cd minishell`
- `make`
- `./minishell`

## Restrictions
- Any function implemented in a header (except in the case of templates), and any
unprotected header, means 0 to the exercise.
- The following functions are FORBIDDEN :*alloc, *printf and free.
- Not allowed to use the STL containers
- the C++ keywords "using namespace" and
"friend" are forbidden
- no C++11 and derivates, nor Boost.
- Code will be compiled with clang++ using flags : -Wall -Wextra -Werror.
<br><br>
- 템플릿의 경우를 제외한 어떤 함수도 헤더에 있으면 안 됩니다.
- 다음의 함수는 금지합니다 : *alloc, *printf, free.
- 컨테이너를 재구현하는 프로그램이기 때문에 STL 라이브러리 컨테이너는 사용 금지입니다.
- c++ 키워드인 "using namespace" 와 "friend" 는 사용 금지입니다.
- c++11 과 그로부터 파생된 버전들과 Boost도 사용 금지입니다.
- 코드는 -Wall -Wextra -Werror 플래그를 사용하여 clang++로 컴파일 됩니다.
<br><br>

## Requirements
- Implement the following containers, and turn in the necessary files <container>.hpp
- You must also provide a main.cpp which tests everything for your evaluations.
- The member function get_allocator is not expected here, the remaining member
functions are. Non-member overloads are expected aswell.
- If the container has an iterator system, you must reimplent it.
- You can use https://www.cplusplus.com/ as a reference of what to implement.
- You cannot implement more public functions than the ones offered in the standard
containers. Everything else must be private or protected. Each public function/-
variable must be justified.
- For non-member overloads, the keyword friend is allowed. Each use of friend
must be justified and will be checked during evaluation.
- You must turn in the following containers and their associated functions:

• List<br>
• Vector<br>
• Map<br>
• Stack<br>
• Queue<br>
Of course, STL is forbidden. You are however allowed to use the STD library
<br><br>

- 다음의 컨테이너들을 구현하고 필요한 <continaer>.hpp 파일을 제출하십시오.
- 구현한 컨테이너들이 정확하게 작동하는지 보여줄 수 있는 test 목적 main.cpp파일을 제출해야 합니다.
- get_allocator 맴버함수는 구현하지 않아도 되지만 다른 맴버함수들은 구현해야 하고 맴버함수가 아닌 오버로딩도 구현해야 합니다.(?)
- 컨테이너에 반복자 시스템이 있는 경우 반복자를 반드시 구현해야 합니다.
- https://www.cplusplus.com/ 링크를 참고해서 무엇을 구현해야 하는지를 확인하십시오.
- 표준 컨테이너에서 제공하는 public 함수말고는 public 함수를 구현하면 안 됩니다. 다른 함수들은 private 이거나 protected 이어야 합니다. 모든 public 함수와 변수는 정당화돼야 합니다.
- 맴버함수가 아닌 오버로딩 함수들에 대해서는 friend 키워드가 허용됩니다. 이에 대해서 정당한 설명이 가능해야 하며 평가 중에 이를 확인합니다. 
- 아래와 같은 컨테이너와 관련된 모든 함수들을 구현해야 합니다:

• List <br>
• Vector<br>
• Map<br>
• Stack<br>
• Queue<br>
물론 STL 은 사용 금지입니다. 하지만 STD 라이브러리는 사용 가능합니다.

#### Contact: zuzudnf@gmail.com
