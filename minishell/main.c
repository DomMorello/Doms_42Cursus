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

void set_pipe_child(char *cmd[], int pipe_idx)
{
    pid_t pid;
    static int i = 0;

    i++;
    pipe(g_pipe_fd);
    pid = fork();
    wait(NULL);
    if (pid == 0)
    {
        close(g_pipe_fd[0]);
        dup2(g_pipe_fd[1], 1);
        close(g_pipe_fd[1]);
        execlp("ls", "ls", "-al", NULL);
       
    }
    // if (i == 2)
    // {
    //     char buf[1000];
    //     read(g_pipe_fd[0], buf, sizeof(buf));
    //     perror("read");
    //     printf("%s\n", buf);
    // }
}

void set_pipe_parent(char *cmd[], int pipe_idx)
{
    close(g_pipe_fd[1]);
    dup2(g_pipe_fd[0], 0);
    close(g_pipe_fd[0]);
    execlp("grep", "grep", "Sep", NULL);
}

void test(void)
{
    /* ;콜론으로 나눠진 것이 여기로 들어왔다고 가정하자! */
    char *cmd[6] = {"ls", "-al", "|", "grep", "Sep", NULL};
    
    int i;
    int is_pipe;

    i = 0;
    is_pipe = 0;
    while (cmd[i])
    {
        if (!strcmp(cmd[i], "|"))
        {
            set_pipe_child(cmd, i);
            is_pipe = 1;
        }
        if (is_pipe)
        {
            set_pipe_parent(cmd, i);
            is_pipe = 0;
        }
        // if (!strcmp(cmd[i], ">"))
        //     set_red_out(cmd[i + 1]);
        i++;
    }
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}
