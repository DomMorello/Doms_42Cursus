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

// ls -al | grep D > test
// echo hello > a > b > c
void test(void)
{
    pid_t pid;
    int status;
    char *command[8] = {"ls", "-al", "|", "grep", "D", ">", "test", NULL};

    set_red(command);
    // set_pipe(command);
    // exex_cmd(command);
}

int main(int argc, char *argv[])
{
    /* token ���� ������ */
    /* ��ɾ ��Ȯ�� ������ ������� ������ �˻��ϰ�(;|/> ���� ���� ������ �� �ȴ�) */
    /* �ñ׳��� ������ �� ��� �ϴ����� ���߿� �������� */
    /* ����� �ִ� ��� process�� ������ */
    test();
    return 0;
}
