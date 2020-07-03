# libft

## Subject
To make my own c library which has many useful functions for the future projects<br><br>
앞으로의 프로젝트에서 요긴하게 사용될 유용한 함수들의 라이브러리 만들기.<br>

## Run
To test, you should make your own c file like this:<br><br>
test.c
```
#include "./libft.h"
#include <stdio.h>

int main(void)
{
    int a;
    char *str;

    a = 0;
    str = "hello world";
    a = ft_strlen(str);
    printf("%d\n", a);
    
    return (0);
}
```
To compile,
```
git clone https://github.com/DomMorello/libft.git
cd libft
make
touch test.c
gcc -Wall -Wextra -Werror test.c libft.a %% ./a.out
```
It should give back:
```
11
```

## Functions

### #Part 1
Re-code a set of libc functions as defined in their man. Those function's prototype is exactly same as original ones. <br><br>
스탠다드 c 라이브러리에 포함된 다음 함수들을 재구현한 라이브러리 입니다.
이 함수들의 선언부는 원래의 함수들과 완전히 같습니다. <br>

- memset
- bzero
- memcpy
- memccpy
- memmove
- memchr
- memcmp
- strlen
- strlcpy
- strlcat
- strchr
- strrchr
- strnstr
- strncmp
- atoi
- isalpha
- isdigit
- isalnum
- isascii
- isprint
- toupper
- tolower
- calloc
- strdup

### #Part 2
A set of functions that are either not included in the libc, or included in a different form.<br><br>
libc에 포함돼있지 않거나 다른 형태로 포함돼있는 함수들.

#### ft_substr
- **Prototype(선언부)**:  ```char *ft_substr(char const *s, unsigned int start,
size_t len);```
- **Parameters**: #1. The string from which to create the substring.
#2. The start index of the substring in the string
’s’.
#3. The maximum length of the substring.
- **Return value**: The substring. NULL if the allocation fails.
- **Description**: Allocates (with malloc(3)) and returns a substring
from the string ’s’.
The substring begins at index ’start’ and is of
maximum size ’len’.
<br><br>
- **매개변수**: #1. 문자열을 뽑아낼 대상이 되는 문자열 #2. 첫 번째 매개변수에서 뽑아낼 문자열의 첫번째 인덱스 #3. 뽑아낼 문자열의 길이
- **반환값**: 뽑아낸 문자열. 동적할당 실패시 NULL
- **설명**: 문자열 's'에서 뽑아낼 문자열만큼 동적할당을 한다(malloc(3) 함수 이용). 뽑아낼 문자열의 첫 인덱스(시작점)은 'start'이고 그 문자열의 길이는 'len'이다.

#### ft_strjoin
- **Prototype(선언부)**: ```char *ft_strjoin(char const *s1, char const *s2);```
- **Parameters**: #1. The prefix string.
#2. The suffix string.
- **Return value**: The new string. NULL if the allocation fails.
- **Description**: Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’.
<br><br>
- **매개변수**: #1. 앞에 올 문자열 #2. 뒤에 올 문자열
- **반환값**: 두 문자열을 합친 새 문자열. 동적할당 실패시 NULL
- **설명**: 두 문자열 's1', 's2'를 그대로 이은 문자열을 동적할당하여 반환(malloc(3)함수 이용)

#### ft_strtrim
- **Prototype(선언부)**: ```char *ft_strtrim(char const *s1, char const *set);```
- **Parameters**: #1. The string to be trimmed.
#2. The reference set of characters to trim.
- **Return value**: The trimmed string. NULL if the allocation fails.
- **Description**: Allocates (with malloc(3)) and returns a copy of
’s1’ with the characters specified in ’set’ removed
from the beginning and the end of the string.
<br><br>
- **매개변수**: #1. 정돈될 문자열 #2. 어떤 문자들을 기준으로 정돈할지를 정하는 문자열
- **반환값**: 정돈된 문자열을 반환. 동적할당 실패시 NULL
- **설명**: 'set'에 정의된 문자들이 's1' 문자열의 앞과 뒤에 있으면 그 문자들을 전부 삭제하고 난 후의 정돈된 문자열을 동적할당하여 반환(malloc(3)함수 이용)

#### ft_split
- **Prototype(선언부)**: ```char **ft_split(char const *s, char c);```
- **Parameters**: #1. The string to be split.
#2. The delimiter character.
- **Return value**: The array of new strings resulting from the split.
NULL if the allocation fails.
- **Description**: Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must be
ended by a NULL pointer.
<br><br>
- **매개변수**: #1. 나눌 문자열 #2. 문자열을 나눌 기준이 되는 문자
- **반환값**: 나눈 결과를 담고 있는 문자열 배열. 동적할당 실패시 NULL
- **설명**: 'c' 문자를 기준으로 's' 문자열을 나눈 후 그 문자열들을 문자열 배열에 동적할당하여 반환. 반환된 문자열 배열의 마지막 요소에는 NULL포인터가 들어가야 한다. 
#### ft_itoa
- **Prototype(선언부)**: ```char *ft_itoa(int n);```
- **Parameters**: #1. the integer to convert.
- **Return value**: The string representing the integer. NULL if the
allocation fails.
- **Description**: Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.
<br><br>
- **매개변수**: #1. 변환할 int 정수값
- **반환값**: 인자로 받은 정수값을 나타내는 문자열. 동적할당 실패시 NULL
- **설명**: 인자로 받은 정수값을 나타내는 문자열을 동적할당하여 반환. 음수도 정상적으로 처리가 돼야 함.

#### ft_strmapi
- **Prototype(선언부)**: ```char *ft_strmapi(char const *s, char (*f)(unsigned
int, char));```
- **Parameters**: #1. The string on which to iterate.
#2. The function to apply to each character.
- **Return value**: The string created from the successive applications
of ’f’. Returns NULL if the allocation fails.
- **Description**: Applies the function ’f’ to each character of the
string ’s’ to create a new string (with malloc(3))
resulting from successive applications of ’f’.
<br><br>
- **매개변수**: #1. 각 문자에 두 번째 매개변수를 적용할 대상이 되는 문자열 #2. 각 문자열에 적용할 함수 포인터
- **반환값**: 'f' 함수를 각 문자에 적용하여 만들어진 문자열. 동적할당 실패시 NULL
- **설명**: 'f' 함수를 문자열 's'가 갖고 있는 각 문자에 전부 적용하여 새로운 문자열을 생성. 

#### ft_putchar_fd
- **Prototype(선언부)**: ```void ft_putchar_fd(char c, int fd);```
- **Parameters**: #1. The character to output.
- #2. The file descriptor on which to write.
- **Return value**: None
- **Description**: Outputs the character ’c’ to the given file
descriptor.
<br><br>
- **매개변수**: #1. 출력될 문자 #2. write할 파일 디스크립터
- **반환값**: 없음
- **설명**: 주어진 파일 디스크립터에 문자 'c'를 출력

#### ft_putstr_fd
- **Prototype(선언부)**: ```void ft_putstr_fd(char *s, int fd);```
- **Parameters**: #1. The string to output.
- #2. The file descriptor on which to write.
- **Return value**: None
- **Description**: Outputs the string ’s’ to the given file
descriptor.
<br><br>
- **매개변수**: #1. 출력할 문자열 #2. write할 파일 디스크립터
- **반환값**: 없음
- **설명**: 주어진 파일 디스크립터에 문자열 's'를 출력

#### ft_putendl_fd
- **Prototype(선언부)**: ```void ft_putendl_fd(char *s, int fd);```
- **Parameters**: #1. The string to output.
- #2. The file descriptor on which to write.
- **Return value**: None
- **Description**: Outputs the string ’s’ to the given file
descriptor, followed by a newline.
<br><br>
- **매개변수**: #1. 출력할 문자열 #2. write할 파일 디스크립터
- **반환값**: 없음
- **설명**: 주어진 파일 디스크립터에 문자열 's'를 출력한 후에 개행을 출력

#### ft_putnbr_fd
- **Prototype(선언부)**: ```void ft_putnbr_fd(int n, int fd);```
- **Parameters**: #1. The integer to output.
- #2. The file descriptor on which to write.
- **Return value**: None
- **Description**: Outputs the integer ’n’ to the given file
descriptor.
<br><br>
- **매개변수**: #1. 출력할 int 정수값 #2. write할 파일 디스크립터
- **반환값**: 없음
- **설명**: 주어진 파일 디스크립터에 int 정수값 'n'을 출력

### #Bonus

Making list
<br><br>
리스트 만들기

```
typedef struct      s_list
{
    void            *content;
    struct s_list   *next;
}                   t_list;
```
The struct above is defined in the libft.h file.<br>
- **content** : The data contained in the element. The void * allows to store any kind
of data.
- **next** : The next element’s address or NULL if it’s the last element.
<br><br>

위에 묘사된 구조체는 libft.h 헤더파일에 정의되어 있습니다.<br>
- **content** : 각 요소가 갖고 있는 데이터. void *타입인 이유는 어떤 종류의 데이터 타입도 담을 수 있게 하기 위함입니다.
- **next** : 리스트에서 다음 요소를 가리키는 포인터입니다. 만약 마지막 요소라면 이 값은 NULL입니다.

#### ft_lstnew
- **Prototype(선언부)**: t_list *ft_lstnew(void *content);
Turn in files -
- **Parameters**: #1. The content to create the new element with.
- **Return value**: The new element.
- **Description**: Allocates (with malloc(3)) and returns a new
element. The variable ’content’ is initialized
with the value of the parameter ’content’. The
variable ’next’ is initialized to NULL.
<br><br>
- **매개변수**: #1. 새로 생성될 노드가 갖게 될 content
- **반환값**: 새로운 노드
- **설명**: 새로운 노드를 동적할당하여 반환. 새로운 노드가 갖고 있는 content는 인자로 받는 content로 초기화되고 next는 NULL로 초기화 된다.

#### ft_lstadd_front
- **Prototype(선언부)**: void ft_lstadd_front(t_list **lst, t_list *new);
Turn in files -
- **Parameters**: #1. The address of a pointer to the first link of
a list.
#2. The address of a pointer to the element to be
added to the list.
- **Return value**: None
- **Description**: Adds the element ’new’ at the beginning of the
list.
<br><br>
- **매개변수**: #1. 리스트의 첫 번째 노드 포인터의 주소값 #2. 리스트에 추가될 노드 포인터의 주소값
- **반환값**: 없음
- **설명**: 'new' 라는 노드를 리스트의 첫 번째 위치(맨 앞)에 추가

#### ft_lstsize
- **Prototype(선언부)**: int ft_lstsize(t_list *lst);
Turn in files -
- **Parameters**: #1. The beginning of the list.
- **Return value**: Length of the list.
- **Description**: Counts the number of elements in a list.
<br><br>
- **매개변수**: #1. 리스트의 첫 번째 노드 포인터
- **반환값**: 리스트의 길이
- **설명**: 리스트에 있는 노드의 개수를 구함

#### ft_lstlast
- **Prototype(선언부)**: t_list *ft_lstlast(t_list *lst);
Turn in files -
- **Parameters**: #1. The beginning of the list.
- **Return value**: Last element of the list.
- **Description**: Returns the last element of the list.
<br><br>
- **매개변수**: #1. 리스트의 첫 번째 노드 포인터
- **반환값**: 리스트의 마지막(맨 끝) 노드
- **설명**: 리스트의 마지막(맨 끝) 노드를 반환

#### ft_lstadd_back
- **Prototype(선언부)**: void ft_lstadd_back(t_list **lst, t_list *new);
Turn in files -
- **Parameters**: #1. The address of a pointer to the first link of
a list.
#2. The address of a pointer to the element to be
added to the list.
- **Return value**: None
- **Description**: Adds the element ’new’ at the end of the list.
<br><br>
- **매개변수**: #1. 리스트의 첫 번째 노드 포인터의 주소값 #2. 리스트에 추가될 노드 포인터의 주소값
- **반환값**: 없음
- **설명**: 'new' 라는 노드를 리스트의 마지막 위치(맨 끝)에 추가

#### ft_lstdelone
- **Prototype(선언부)**: void ft_lstdelone(t_list *lst, void (*del)(void
*));
Turn in files -
- **Parameters**: #1. The element to free.
#2. The address of the function used to delete the
content.
- **Return value**: None
- **Description**: Takes as a parameter an element and frees the
memory of the element’s content using the function
’del’ given as a parameter and free the element.
The memory of ’next’ must not be freed.
<br><br>
- **매개변수**: #1. 메모리 해제할 노드 #2. 노드의 content를 메모리 해제하기 위한 함수 포인터
- **반환값**: 없음
- **설명**: 어떤 노드를 매개변수로 받고 함수 'del'을 이용해 그 노드의 content를 메모리 해제함. 노드의 next가 가리키는 다음 노드를 메모리 해제하지 않음.

#### ft_lstclear
- **Prototype(선언부)**: void ft_lstclear(t_list **lst, void (*del)(void
*));
Turn in files -
- **Parameters**: #1. The adress of a pointer to an element.
#2. The adress of the function used to delete the
content of the element.
- **Return value**: None
- **Description**: Deletes and frees the given element and every
successor of that element, using the function ’del’
and free(3).
Finally, the pointer to the list must be set to
NULL.
<br><br>
- **매개변수**: #1. 어떤 노드 포인터의 주소값 #2. 노드의 content를 메모리 해제하는 함수 포인터
- **반환값**: 없음
- **설명**: 'del' 함수와 free(3) 함수를 사용하여 주어진 노드와 그 이후에 이어져 있는 모든 노드를 메모리 해제하고 삭제

#### ft_lstiter
- **Prototype(선언부)**: void ft_lstiter(t_list *lst, void (*f)(void *));
Turn in files -
- **Parameters**: #1. The adress of a pointer to an element.
#2. The adress of the function used to iterate on
the list.
- **Return value**: None
- **Description**: Iterates the list ’lst’ and applies the function
’f’ to the content of each element.
<br><br>
- **매개변수**: #1. 어떤 노드 포인터의 주소값 #2. 리스트에 있는 노드들에 각각 적용할 함수 포인터
- **반환값**: 없음
- **설명**: 'lst'라는 리스트가 갖는 모든 노드의 content에 'f' 함수를 전부 적용함 

#### ft_lstmap
- **Prototype(선언부)**: t_list *ft_lstmap(t_list *lst, void *(*f)(void *),
void (*del)(void *));
Turn in files -
- **Parameters**: #1. The adress of a pointer to an element.
#2. The adress of the function used to iterate on
the list.
#3. The adress of the function used to delete the
content of an element if needed.
- **Return value**: The new list. NULL if the allocation fails.
- **Description**: Iterates the list ’lst’ and applies the function
’f’ to the content of each element. Creates a new
list resulting of the successive applications of
the function ’f’. The ’del’ function is used to
delete the content of an element if needed.
<br><br>
- **매개변수**: #1. 어떤 노드 포인터의 주소값 #2. 각 노드에 적용할 함수 포인터 #3. 필요할 때 노드를 삭제하기 위해 사용할 함수 포인터
- **반환값**: 새로운 리스트. 동적할당 실패시 NULL
- **설명**: 리스트에 있는 모든 노드의 content에 'f' 함수를 적용시킴. 이 함수를 적용시킨 새로운 리스트를 생성함. 'del' 함수는 필요할 때 노드의 content를 삭제하기 위해 사용됨

#### Contact: zuzudnf@gmail.com