#include "./minishell.h"

extern char *environ[];

int g_pipe_fd[2];
int g_red_out_fd;
int g_red_in_fd;

void set_red_out(char *title)
{
	g_red_out_fd = open(title, O_CREAT | O_RDWR);
	dup2(g_red_out_fd, 1);
	close(g_red_out_fd);
}

void set_pipe_child()
{
	close(g_pipe_fd[0]);
	dup2(g_pipe_fd[1], 1);
	close(g_pipe_fd[1]);
}

void set_pipe_parent()
{
	close(g_pipe_fd[1]);
	dup2(g_pipe_fd[0], 0);
	close(g_pipe_fd[0]);
}

void find_pipe(char *cmd, int *is_pipe, int pipe_idx)
{
    if (!strcmp(cmd, "|"))
    {
        *is_pipe = 1;
        pipe(g_pipe_fd);
        printf("%d\n", pipe_idx);
        /* 여기서 인덱스를 갖고 명령어를 나눠서 어떻게 처리할지를 해보자
            비슷한 함수를 두 번 거치더라도 파이프 있는 경우와 아닌 경우를 
            나눠서 하면 된다. 리다이렉션은 그 안에서 처리하면 될 것 같다 */
    }
}

void exec_cmd(char *cmd[], int i, int *is_pipe)
{
    pid_t pid = fork();
    wait(NULL);
    if (pid == 0)
    {
        if (*is_pipe)
            set_pipe_child();
        /* exec cmd */
    }
    else
    {
        if (*is_pipe)
            set_pipe_parent();
    }
    *is_pipe = 0;
}

void test(void)
{
    /* ;콜론으로 나눠진 것이 여기로 들어왔다고 가정하자! */
    char *cmd[15] = {"ls", "-al", "|", "grep", "Sep", "|", "wc", ">", "hello",
                     "|", "echo", "hi", ">", "hello2", NULL};
    
    int i;
    int is_pipe;

    i = 0;
    is_pipe = 0;
    while (cmd[i])
    {
        find_pipe(cmd[i], &is_pipe, i);
        i++;
    }
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}
