# get_next_line
### Score 115 / 100
## Subject
> a function which returns a line read from a file descriptor, without the newline.
<br><br>
> 파일 디스크립터로부터 한 줄의 내용을 읽어서 개행없이 문자열을 반환해주는 함수

## Requirements
- Calling your function get_next_line in a loop will then allow you to read the text
available on a file descriptor one line at a time until the EOF.
- The function behaves well when it reads from a file and when it
reads from the standard input.
- This program compiles with the flag -D BUFFER_SIZE=xx. which will be used
as the buffer size for the read calls in your get_next_line.
- For example, if the file descriptors 3, 4 and 5 are accessible for reading, then you can call get_next_line once on 3, once on 4, once again on 3 then once on 5 etc. without losing the reading thread on each of the descriptors.
<br><br>
- 반복문 안에서 get_next_line 함수를 사용하여 파일 디스크립터를 통해 읽는 파일을 한 줄씩 읽으면서 파일의 끝까지 읽을 수 있습니다.
- 이 함수는 파일을 읽을 때도 작동하지만 표준입력을 통해서도 잘 작동합니다.
- 이 프로그램을 컴파일 할 때는 -D BUFFER_SIZE=xx 와 같이 플래그를 설정해야 하는데 이는 함수에서 사용할 버퍼사이즈의 크기를 결정해 줄 것입니다.
- 예를 들어, 파일 디스크립터가 3, 4, 5에 파일을 읽을 수 있도록 되어 있고 이 함수를 사용해서 3번을 읽다가 4번을 읽고 다시 3번을 읽다가 5번을 읽었을 때 각각의 파일을 읽는데 전혀 지장이 없이 순서대로 작동합니다. 

## Compile
```
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=32 get_next_line.c get_next_line_utils.c
```

## Run


#### Contact: zuzudnf@gmail.com