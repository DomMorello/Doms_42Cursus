#include "./minishell.h"

extern char *environ[];

void start(char *argv[])
{
    if (argv[1] && !strcmp(argv[1], "pwd"))
    {
        pid_t pid;
        int status;

        if ((pid = fork()) == 0)
        {
            /* child */
            char buf[100];

            getcwd(buf, sizeof(buf));
            if (argv[2] && !strcmp(argv[2], ">"))
            {
                int fd;

                fd = open(argv[3], O_WRONLY | O_CREAT);
                dup2(fd, 1);
                close(fd);
                printf("%s\n", buf);
            }
            else
                printf("%s\n", buf);            
            sleep(3);
        }
        else if (pid > 0)
        {
            /* parent */
            wait(&status);
            printf("parent end!\n");
        }
    }
}

int main(int argc, char *argv[])
{
    /* token ���� ������ */
    /* ��ɾ ��Ȯ�� ������ ������� ������ �˻��ϰ�(;|/> ���� ���� ������ �� �ȴ�) */
    /* �ñ׳��� ������ �� ��� �ϴ����� ���߿� �������� */
    /* ����� �ִ� ��� process�� ������ */
    /* ��ɾ� ����ü�� ���� �ѱ�鼭 �غ��? */

    // pwd > test.txt
    start(argv);
    return 0;
}
