#include "./minishell.h"

extern char *environ[];

int g_pipe_fd[2];
int g_red_out_fd;
int g_red_in_fd;

// ls -al | grep D > test
// echo hello > a > b > c

int is_pipe(char *cmd[])
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (!strcmp(cmd[i], "|"))
        {
            return i;
        }
        i++;
    }
    return 0;
}

void set_pipe(char *cmd[])
{
    pipe(g_pipe_fd);
    dup2(g_pipe_fd[1], 1);
    close(g_pipe_fd[0]);
    close(g_pipe_fd[1]);
}

void parse_pipe(char *cmd[], int *i)
{
    int pipe_idx;

    pipe_idx = is_pipe(cmd);
    if (pipe_idx)
    {
        set_pipe(cmd);
    }
}

int find_redirection_out(char *cmd[])
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (!strcmp(cmd[i], ">"))
            return i;
        i++;
    }
    return 0;
}

void set_red_out(char *cmd[], int red_idx)
{
    g_red_out_fd = open(cmd[red_idx + 1], O_CREAT | O_RDWR);
    dup2(g_red_out_fd, 1);
    close(g_red_out_fd);
}

void parse_redirection(char *cmd[])
{
    int red_idx;

    red_idx = find_redirection_out(cmd);
    if (red_idx)
    {
        set_red_out(cmd, red_idx);
        /* 한 줄이 끝나고 red가 세팅돼있으면 원래대로 돌려놔야 할 것 같다 */
    }
}

void test(void)
{
    char *cmd[8] = {"ls", "-al", "|", "grep", "h", ">", "test", NULL};

    parse_redirection(cmd);
    parse_pipe(cmd);
    // exec_cmd(cmd, &i);
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}
