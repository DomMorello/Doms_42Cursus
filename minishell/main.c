#include "./minishell.h"

extern char *environ[];

// void redirection(char *argv[])
// {
//     if (argv[1] && !strcmp(argv[1], "pwd"))
//     {
//         pid_t pid;
//         int status;
        
//         if ((pid = fork()) == 0)
//         {
//             /* child */
//             char buf[100];
//             getcwd(buf, sizeof(buf));
//             if (argv[2] && !strcmp(argv[2], "D"))
//             {
//                 int fd = open(argv[3], O_WRONLY | O_CREAT);
//                 dup2(fd, 1);
//                 close(fd);
//                 printf("%s\n", buf);
//             }
//             else
//                 printf("%s\n", buf);
//             exit(1);
//         }
//         else if (pid > 0)
//         {
//             /* parent */
//             wait(&status);
//             printf("parent end!\n");
//         }
//     }
// }

/* �����̴� ���̵��! ǥ������� �ִ� ��ɾ���� ���� �� ������ �ϰ� 
redirection�̳� pipe�� ������ ����� ���ڿ��� �Ѱܼ� ó�����ִ� �Լ��� ������.
�̷��� �ϸ� ���������� �� �� �� ������? */

void set_red(char *cmd[])
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (!strcmp(cmd[i], ">"))
        {
            /* �̷� ������ �� �� ¥���� �Լ�ȭ�� ��� ��������� ¥����. */
        }
        
        i++;
    }
}

void pipeline(char** cmd) 
{ 
    // 0 is read end, 1 is write end 
    int fd[2];  
    pid_t p1, p2; 
  
    if (pipe(fd) < 0) { 
        printf("\nPipe could not be initialized"); 
        return; 
    } 
    p1 = fork(); 
    if (p1 < 0) {
        printf("\nCould not fork"); 
        return; 
    } 
  
    if (p1 == 0) { 
        // Child 1 executing.. 
        // It only needs to write at the write end 
        close(fd[1]); 
        dup2(fd[0], 0); 
        close(fd[0]); 
  
        if (execlp("grep", "grep", "h", NULL) < 0) { 
            printf("\nCould not execute command 1.."); 
            exit(0); 
        } 
    } else { 
        // Parent executing 
        p2 = fork(); 
  
        if (p2 < 0) { 
            printf("\nCould not fork"); 
            return; 
        } 
  
        // Child 2 executing.. 
        // It only needs to read at the read end 
        if (p2 == 0) { 
            close(fd[0]); 
            dup2(fd[1], 1); 
            close(fd[1]); 
            if (execlp("ls", "ls", "-al", NULL) < 0) { 
                printf("\nCould not execute command 2.."); 
                exit(0); 
            } 
        } else { 
            // parent executing, waiting for two children 
            wait(NULL); 
        } 
    } 
}

void set_pipe(char *cmd[])
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (!strcmp(cmd[i], "|"))
        {
            pipeline(cmd);
        }
        i++;
    }
}

// ls -al | grep D > test
// echo hello > a > b > c
void test(void)
{
    pid_t pid;
    int status;
    char *command[8] = {"ls", "-al", "|", "grep", "h", ">", "test", NULL};

    set_red(command);
    set_pipe(command);
    // exex_cmd(command);
}

int main(int argc, char *argv[])
{
    /* token ���� ������ */
    /* ��ɾ ��Ȯ�� ������ ������� ������ �˻��ϰ�(;|/> ���� ���� ������ �� �ȴ�) */
    /* �ñ׳��� ������ �� ��� �ϴ����� ���߿� �������� */
    /* ����� �ִ� ��� process�� ������ */
    // test();
    int fd[2];
    pid_t pid1, pid2;

    pid1 = fork();
    if (pid1 == 0)
    {
        // child
        
    }
    else
    {
        //parent

    }
    return 0;
}
