#include "./minishell.h"

extern char *environ[];

void start(char *argv[])
{
    char buf[100] = {0,};
    pid_t pid;

    if (!strcmp(argv[1], "pwd"))
    {
        if ((pid = fork()) > 0)
        {
            //parent
        }
        else if (!pid)
        {   // child
            getcwd(buf, sizeof(buf));
            /* ���⼭ ��� �ؾ���? redireciton�� �Դٰ� �����ϸ� ���� �ؾ� �ǳ�. */
        }
        else if (pid < 0)
        {   //error
            printf("fork fail! %s\n", strerror(errno));
            exit(-1);
        }
    }
}

int main(int argc, char *argv[])
{
    /* token ���� ������ */
    /* ��ɾ ��Ȯ�� ������ ������� ������ �˻��ϰ�(;|/> ���� ���� ������ �� �ȴ�) */
    /* �ñ׳��� ������ �� ��� �ϴ����� ���߿� �������� */
    /* ����� �ִ� ��� process�� ������ */
    start(argv);
    return 0;
}
