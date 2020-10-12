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
        /* pipe_idx �� �̿��ؼ� ��ɾ�ó�� ������ �ڸ���. */

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
    /* ;�ݷ����� ������ ���� ����� ���Դٰ� ��������! */
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

/* �������� �������� ��ɾ� ������ ���� �ڸ��� ���� �����ϴ� ����� �����غ��� */
int main(int argc, char *argv[])
{
    test();
    return 0;
}
