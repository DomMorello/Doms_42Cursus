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
    /* token 으로 나누고 */
    /* 명령어가 정확한 포맷을 갖췄는지 에러를 검사하고(;|/> 등이 먼저 나오면 안 된다) */
    /* 시그널이 들어왔을 때 어떻게 하는지는 나중에 생각하자 */
    /* 출력이 있는 경우 process로 나눠서 */
    /* 명령어 구조체를 만들어서 넘기면서 해볼까나? */

    // pwd > test.txt
    start(argv);
    return 0;
}
