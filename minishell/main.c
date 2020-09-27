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
    dup2(g_pipe_fd[0], 0);
    close(g_pipe_fd[1]);
    /* ���߿� Ȯ���ؼ� g_pipe_fd[0] �� �ݾƾ� �Ѵ� */

}

void parse_pipe(char *cmd[], int *pipe)
{
    int pipe_idx;

    pipe_idx = is_pipe(cmd);
    if (pipe_idx)
    {
        *pipe = 1;
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
    /* �̷��� �ϸ� > �� ������ �������� �������� ���� fd�� �����Ǵϱ� ��������? */
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
        /* �Է� �� ���� ������ red�� ���õ������� ������� �������� �� �� ���� */
    }
}

void exec_cmd(char *cmd[], int is_pipe)
{
    pid_t pid;

    pid = fork();
    wait(NULL);
    if (pid == 0)
    {
        if (is_pipe == 1)
        {
            dup2(g_pipe_fd[1], 1);
            close(g_pipe_fd[0]);
            close(g_pipe_fd[1]);
        }
        execlp(cmd[0], cmd[0], cmd[1], NULL);
        perror("exec err");
    }
}

void test(void)
{
    int is_pipe;
    char *cmd[9] = {"ls", "-al", ">", "a", ">", "b", ">", "c", NULL};

    is_pipe = 0;
    parse_redirection(cmd);
    parse_pipe(cmd, &is_pipe); /* ��ɾ ������ ������ �ݺ��ؾ� �ȴ�. */
    exec_cmd(cmd, is_pipe);
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}
