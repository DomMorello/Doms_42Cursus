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
            /* 여기서 어떻게 해야지? redireciton이 왔다고 가정하면 어케 해야 되나. */
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
    /* token 으로 나누고 */
    /* 명령어가 정확한 포맷을 갖췄는지 에러를 검사하고(;|/> 등이 먼저 나오면 안 된다) */
    /* 시그널이 들어왔을 때 어떻게 하는지는 나중에 생각하자 */
    /* 출력이 있는 경우 process로 나눠서 */
    start(argv);
    return 0;
}
