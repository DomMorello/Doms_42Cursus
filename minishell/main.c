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

void set_red_in(char *title)
{
	g_red_in_fd = open(title, O_CREAT | O_RDWR);
	dup2(g_red_in_fd, 0);
	close(g_red_in_fd);
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

void process_red_out(char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
    int i;

    i = *prev_pipe_idx;
    while (cmd[i] && i < pipe_idx)
    {
        if (!strcmp(cmd[i], ">"))
            set_red_out(cmd[i + 1]);
        if (!strcmp(cmd[i], "<"))
            set_red_in(cmd[i + 1]);
        i++;
    }
}

void exec_cmd(char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
    static int i = 0;

    i++;
    pid_t pid = fork();
    wait(NULL);
    if (pid == 0)
    {
        set_pipe_child();
        process_red_out(cmd, prev_pipe_idx, pipe_idx);
        if (i == 1)
            execlp("grep", "grep", "Sep", NULL);
        if (i == 2)
            execlp("ls", "ls", "-al", NULL);
        if (i == 3)
            execlp("wc", "wc", NULL);
    }
    else
    {
        set_pipe_parent();
    }
}

void process_pipe(char *cmd[], int pipe_idx, int *prev_pipe_idx)
{
    if (!strcmp(cmd[pipe_idx], "|"))
    {
        pipe(g_pipe_fd);
        exec_cmd(cmd, prev_pipe_idx, pipe_idx);
        *prev_pipe_idx = pipe_idx;
    }
}

void exec_last_cmd(char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
    process_red_out(cmd, prev_pipe_idx, pipe_idx);
    execlp("wc", "wc", NULL);
}

void test(void)
{
    /* ;콜론으로 나눠진 것이 여기로 들어왔다고 가정하자! */
    // char *cmd[50] = {"ls", "-al", "|", "grep", "Sep", "|", "wc", ">",
    //         "hello1", ">", "hello2", "|", "echo", "hi", ">", "hello3", NULL};
    
    char *cmd[50] = {"grep", "Sep", "<", "hello1", "|", "wc", "<", "hello1", NULL};

    int i;
    int prev_pipe_idx;

    prev_pipe_idx = 0;
    i = 0;
    while (cmd[i])
    {
        process_pipe(cmd, i, &prev_pipe_idx);
        i++;
        if (!cmd[i])
            exec_last_cmd(cmd, &prev_pipe_idx, i);
    }
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}
