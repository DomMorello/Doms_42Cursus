# libasm
42 Seoul assembly project

## Subject
> to make a library which has some basic functions with assembly language<br>

> �������� �⺻���� �Լ��� �����ϰ� �̸� ���̺귯���� ����� ������Ʈ�Դϴ�.<br>

## Requirements
- This library is written 64 bits ASM.
- The functions written in assembly code will be compiled with nasm
- I used the Intel syntax, not the AT&T.
- When you fail to call system call in ft_read and ft_write functions, the errno variable will be properly set.
<br><br>
- �� ���̺귯���� 64��Ʈ ������� �ۼ��Ǿ����ϴ�.
- �������� �ۼ��� �Լ����� nasm���� ������ �˴ϴ�.
- ������δ� AT&T������ �ƴ� Intel ���� ������� �ۼ��Ǿ����ϴ�. 
- ft_read�� ft_write�Լ����� �ý������� �������� ��쿡 errno ������ ������ �����ڵ尡 ����˴ϴ�.
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
�� ���α׷��� �� OSȯ�濡���� ���� �����մϴ�.<br>

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