# libft

## Subject
To make my own c library which has many useful functions for the future projects<br><br>
�������� ������Ʈ���� ����ϰ� ���� ������ �Լ����� ���̺귯�� �����.<br>

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
���Ĵٵ� c ���̺귯���� ���Ե� ���� �Լ����� �籸���� ���̺귯�� �Դϴ�.
�� �Լ����� ����δ� ������ �Լ���� ������ �����ϴ�. <br>

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
libc�� ���Ե����� �ʰų� �ٸ� ���·� ���Ե��ִ� �Լ���.

#### ft_substr
- **Prototype(�����)**:  ```char *ft_substr(char const *s, unsigned int start,
size_t len);```
- **Parameters**: #1. The string from which to create the substring.
#2. The start index of the substring in the string
��s��.
#3. The maximum length of the substring.
- **Return value**: The substring. NULL if the allocation fails.
- **Description**: Allocates (with malloc(3)) and returns a substring
from the string ��s��.
The substring begins at index ��start�� and is of
maximum size ��len��.
<br><br>
- **�Ű�����**: #1. ���ڿ��� �̾Ƴ� ����� �Ǵ� ���ڿ� #2. ù ��° �Ű��������� �̾Ƴ� ���ڿ��� ù��° �ε��� #3. �̾Ƴ� ���ڿ��� ����
- **��ȯ��**: �̾Ƴ� ���ڿ�. �����Ҵ� ���н� NULL
- **����**: ���ڿ� 's'���� �̾Ƴ� ���ڿ���ŭ �����Ҵ��� �Ѵ�(malloc(3) �Լ� �̿�). �̾Ƴ� ���ڿ��� ù �ε���(������)�� 'start'�̰� �� ���ڿ��� ���̴� 'len'�̴�.

#### ft_strjoin
- **Prototype(�����)**: ```char *ft_strjoin(char const *s1, char const *s2);```
- **Parameters**: #1. The prefix string.
#2. The suffix string.
- **Return value**: The new string. NULL if the allocation fails.
- **Description**: Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ��s1�� and ��s2��.
<br><br>
- **�Ű�����**: #1. �տ� �� ���ڿ� #2. �ڿ� �� ���ڿ�
- **��ȯ��**: �� ���ڿ��� ��ģ �� ���ڿ�. �����Ҵ� ���н� NULL
- **����**: �� ���ڿ� 's1', 's2'�� �״�� ���� ���ڿ��� �����Ҵ��Ͽ� ��ȯ(malloc(3)�Լ� �̿�)

#### ft_strtrim
- **Prototype(�����)**: ```char *ft_strtrim(char const *s1, char const *set);```
- **Parameters**: #1. The string to be trimmed.
#2. The reference set of characters to trim.
- **Return value**: The trimmed string. NULL if the allocation fails.
- **Description**: Allocates (with malloc(3)) and returns a copy of
��s1�� with the characters specified in ��set�� removed
from the beginning and the end of the string.
<br><br>
- **�Ű�����**: #1. ������ ���ڿ� #2. � ���ڵ��� �������� ���������� ���ϴ� ���ڿ�
- **��ȯ��**: ������ ���ڿ��� ��ȯ. �����Ҵ� ���н� NULL
- **����**: 'set'�� ���ǵ� ���ڵ��� 's1' ���ڿ��� �հ� �ڿ� ������ �� ���ڵ��� ���� �����ϰ� �� ���� ������ ���ڿ��� �����Ҵ��Ͽ� ��ȯ(malloc(3)�Լ� �̿�)

#### ft_split
- **Prototype(�����)**: ```char **ft_split(char const *s, char c);```
- **Parameters**: #1. The string to be split.
#2. The delimiter character.
- **Return value**: The array of new strings resulting from the split.
NULL if the allocation fails.
- **Description**: Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ��s�� using the
character ��c�� as a delimiter. The array must be
ended by a NULL pointer.
<br><br>
- **�Ű�����**: #1. ���� ���ڿ� #2. ���ڿ��� ���� ������ �Ǵ� ����
- **��ȯ��**: ���� ����� ��� �ִ� ���ڿ� �迭. �����Ҵ� ���н� NULL
- **����**: 'c' ���ڸ� �������� 's' ���ڿ��� ���� �� �� ���ڿ����� ���ڿ� �迭�� �����Ҵ��Ͽ� ��ȯ. ��ȯ�� ���ڿ� �迭�� ������ ��ҿ��� NULL�����Ͱ� ���� �Ѵ�. 
#### ft_itoa
- **Prototype(�����)**: ```char *ft_itoa(int n);```
- **Parameters**: #1. the integer to convert.
- **Return value**: The string representing the integer. NULL if the
allocation fails.
- **Description**: Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.
<br><br>
- **�Ű�����**: #1. ��ȯ�� int ������
- **��ȯ��**: ���ڷ� ���� �������� ��Ÿ���� ���ڿ�. �����Ҵ� ���н� NULL
- **����**: ���ڷ� ���� �������� ��Ÿ���� ���ڿ��� �����Ҵ��Ͽ� ��ȯ. ������ ���������� ó���� �ž� ��.

#### ft_strmapi
- **Prototype(�����)**: ```char *ft_strmapi(char const *s, char (*f)(unsigned
int, char));```
- **Parameters**: #1. The string on which to iterate.
#2. The function to apply to each character.
- **Return value**: The string created from the successive applications
of ��f��. Returns NULL if the allocation fails.
- **Description**: Applies the function ��f�� to each character of the
string ��s�� to create a new string (with malloc(3))
resulting from successive applications of ��f��.
<br><br>
- **�Ű�����**: #1. �� ���ڿ� �� ��° �Ű������� ������ ����� �Ǵ� ���ڿ� #2. �� ���ڿ��� ������ �Լ� ������
- **��ȯ��**: 'f' �Լ��� �� ���ڿ� �����Ͽ� ������� ���ڿ�. �����Ҵ� ���н� NULL
- **����**: 'f' �Լ��� ���ڿ� 's'�� ���� �ִ� �� ���ڿ� ���� �����Ͽ� ���ο� ���ڿ��� ����. 

#### ft_putchar_fd
- **Prototype(�����)**: ```void ft_putchar_fd(char c, int fd);```
- **Parameters**: #1. The character to output.
- #2. The file descriptor on which to write.
- **Return value**: None
- **Description**: Outputs the character ��c�� to the given file
descriptor.
<br><br>
- **�Ű�����**: #1. ��µ� ���� #2. write�� ���� ��ũ����
- **��ȯ��**: ����
- **����**: �־��� ���� ��ũ���Ϳ� ���� 'c'�� ���

#### ft_putstr_fd
- **Prototype(�����)**: ```void ft_putstr_fd(char *s, int fd);```
- **Parameters**: #1. The string to output.
- #2. The file descriptor on which to write.
- **Return value**: None
- **Description**: Outputs the string ��s�� to the given file
descriptor.
<br><br>
- **�Ű�����**: #1. ����� ���ڿ� #2. write�� ���� ��ũ����
- **��ȯ��**: ����
- **����**: �־��� ���� ��ũ���Ϳ� ���ڿ� 's'�� ���

#### ft_putendl_fd
- **Prototype(�����)**: ```void ft_putendl_fd(char *s, int fd);```
- **Parameters**: #1. The string to output.
- #2. The file descriptor on which to write.
- **Return value**: None
- **Description**: Outputs the string ��s�� to the given file
descriptor, followed by a newline.
<br><br>
- **�Ű�����**: #1. ����� ���ڿ� #2. write�� ���� ��ũ����
- **��ȯ��**: ����
- **����**: �־��� ���� ��ũ���Ϳ� ���ڿ� 's'�� ����� �Ŀ� ������ ���

#### ft_putnbr_fd
- **Prototype(�����)**: ```void ft_putnbr_fd(int n, int fd);```
- **Parameters**: #1. The integer to output.
- #2. The file descriptor on which to write.
- **Return value**: None
- **Description**: Outputs the integer ��n�� to the given file
descriptor.
<br><br>
- **�Ű�����**: #1. ����� int ������ #2. write�� ���� ��ũ����
- **��ȯ��**: ����
- **����**: �־��� ���� ��ũ���Ϳ� int ������ 'n'�� ���

### #Bonus

Making list
<br><br>
����Ʈ �����

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
- **next** : The next element��s address or NULL if it��s the last element.
<br><br>

���� ����� ����ü�� libft.h ������Ͽ� ���ǵǾ� �ֽ��ϴ�.<br>
- **content** : �� ��Ұ� ���� �ִ� ������. void *Ÿ���� ������ � ������ ������ Ÿ�Ե� ���� �� �ְ� �ϱ� �����Դϴ�.
- **next** : ����Ʈ���� ���� ��Ҹ� ����Ű�� �������Դϴ�. ���� ������ ��Ҷ�� �� ���� NULL�Դϴ�.

#### ft_lstnew
- **Prototype(�����)**: t_list *ft_lstnew(void *content);
Turn in files -
- **Parameters**: #1. The content to create the new element with.
- **Return value**: The new element.
- **Description**: Allocates (with malloc(3)) and returns a new
element. The variable ��content�� is initialized
with the value of the parameter ��content��. The
variable ��next�� is initialized to NULL.
<br><br>
- **�Ű�����**: #1. ���� ������ ��尡 ���� �� content
- **��ȯ��**: ���ο� ���
- **����**: ���ο� ��带 �����Ҵ��Ͽ� ��ȯ. ���ο� ��尡 ���� �ִ� content�� ���ڷ� �޴� content�� �ʱ�ȭ�ǰ� next�� NULL�� �ʱ�ȭ �ȴ�.

#### ft_lstadd_front
- **Prototype(�����)**: void ft_lstadd_front(t_list **lst, t_list *new);
Turn in files -
- **Parameters**: #1. The address of a pointer to the first link of
a list.
#2. The address of a pointer to the element to be
added to the list.
- **Return value**: None
- **Description**: Adds the element ��new�� at the beginning of the
list.
<br><br>
- **�Ű�����**: #1. ����Ʈ�� ù ��° ��� �������� �ּҰ� #2. ����Ʈ�� �߰��� ��� �������� �ּҰ�
- **��ȯ��**: ����
- **����**: 'new' ��� ��带 ����Ʈ�� ù ��° ��ġ(�� ��)�� �߰�

#### ft_lstsize
- **Prototype(�����)**: int ft_lstsize(t_list *lst);
Turn in files -
- **Parameters**: #1. The beginning of the list.
- **Return value**: Length of the list.
- **Description**: Counts the number of elements in a list.
<br><br>
- **�Ű�����**: #1. ����Ʈ�� ù ��° ��� ������
- **��ȯ��**: ����Ʈ�� ����
- **����**: ����Ʈ�� �ִ� ����� ������ ����

#### ft_lstlast
- **Prototype(�����)**: t_list *ft_lstlast(t_list *lst);
Turn in files -
- **Parameters**: #1. The beginning of the list.
- **Return value**: Last element of the list.
- **Description**: Returns the last element of the list.
<br><br>
- **�Ű�����**: #1. ����Ʈ�� ù ��° ��� ������
- **��ȯ��**: ����Ʈ�� ������(�� ��) ���
- **����**: ����Ʈ�� ������(�� ��) ��带 ��ȯ

#### ft_lstadd_back
- **Prototype(�����)**: void ft_lstadd_back(t_list **lst, t_list *new);
Turn in files -
- **Parameters**: #1. The address of a pointer to the first link of
a list.
#2. The address of a pointer to the element to be
added to the list.
- **Return value**: None
- **Description**: Adds the element ��new�� at the end of the list.
<br><br>
- **�Ű�����**: #1. ����Ʈ�� ù ��° ��� �������� �ּҰ� #2. ����Ʈ�� �߰��� ��� �������� �ּҰ�
- **��ȯ��**: ����
- **����**: 'new' ��� ��带 ����Ʈ�� ������ ��ġ(�� ��)�� �߰�

#### ft_lstdelone
- **Prototype(�����)**: void ft_lstdelone(t_list *lst, void (*del)(void
*));
Turn in files -
- **Parameters**: #1. The element to free.
#2. The address of the function used to delete the
content.
- **Return value**: None
- **Description**: Takes as a parameter an element and frees the
memory of the element��s content using the function
��del�� given as a parameter and free the element.
The memory of ��next�� must not be freed.
<br><br>
- **�Ű�����**: #1. �޸� ������ ��� #2. ����� content�� �޸� �����ϱ� ���� �Լ� ������
- **��ȯ��**: ����
- **����**: � ��带 �Ű������� �ް� �Լ� 'del'�� �̿��� �� ����� content�� �޸� ������. ����� next�� ����Ű�� ���� ��带 �޸� �������� ����.

#### ft_lstclear
- **Prototype(�����)**: void ft_lstclear(t_list **lst, void (*del)(void
*));
Turn in files -
- **Parameters**: #1. The adress of a pointer to an element.
#2. The adress of the function used to delete the
content of the element.
- **Return value**: None
- **Description**: Deletes and frees the given element and every
successor of that element, using the function ��del��
and free(3).
Finally, the pointer to the list must be set to
NULL.
<br><br>
- **�Ű�����**: #1. � ��� �������� �ּҰ� #2. ����� content�� �޸� �����ϴ� �Լ� ������
- **��ȯ��**: ����
- **����**: 'del' �Լ��� free(3) �Լ��� ����Ͽ� �־��� ���� �� ���Ŀ� �̾��� �ִ� ��� ��带 �޸� �����ϰ� ����

#### ft_lstiter
- **Prototype(�����)**: void ft_lstiter(t_list *lst, void (*f)(void *));
Turn in files -
- **Parameters**: #1. The adress of a pointer to an element.
#2. The adress of the function used to iterate on
the list.
- **Return value**: None
- **Description**: Iterates the list ��lst�� and applies the function
��f�� to the content of each element.
<br><br>
- **�Ű�����**: #1. � ��� �������� �ּҰ� #2. ����Ʈ�� �ִ� ���鿡 ���� ������ �Լ� ������
- **��ȯ��**: ����
- **����**: 'lst'��� ����Ʈ�� ���� ��� ����� content�� 'f' �Լ��� ���� ������ 

#### ft_lstmap
- **Prototype(�����)**: t_list *ft_lstmap(t_list *lst, void *(*f)(void *),
void (*del)(void *));
Turn in files -
- **Parameters**: #1. The adress of a pointer to an element.
#2. The adress of the function used to iterate on
the list.
#3. The adress of the function used to delete the
content of an element if needed.
- **Return value**: The new list. NULL if the allocation fails.
- **Description**: Iterates the list ��lst�� and applies the function
��f�� to the content of each element. Creates a new
list resulting of the successive applications of
the function ��f��. The ��del�� function is used to
delete the content of an element if needed.
<br><br>
- **�Ű�����**: #1. � ��� �������� �ּҰ� #2. �� ��忡 ������ �Լ� ������ #3. �ʿ��� �� ��带 �����ϱ� ���� ����� �Լ� ������
- **��ȯ��**: ���ο� ����Ʈ. �����Ҵ� ���н� NULL
- **����**: ����Ʈ�� �ִ� ��� ����� content�� 'f' �Լ��� �����Ŵ. �� �Լ��� �����Ų ���ο� ����Ʈ�� ������. 'del' �Լ��� �ʿ��� �� ����� content�� �����ϱ� ���� ����

#### Contact: zuzudnf@gmail.com