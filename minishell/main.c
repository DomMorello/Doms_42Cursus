#include "./minishell.h"

extern char *environ[];

int g_pipe_fd[2];
int g_red_out_fd;
int g_red_in_fd;

// void set_red_out(char *cmd[], int red_idx)
// {
//     g_red_out_fd = open(cmd[red_idx + 1], O_CREAT | O_RDWR);
//     /* �̷��� �ϸ� > �� ������ �������� �������� ���� fd�� �����Ǵϱ� ��������? */
//     dup2(g_red_out_fd, 1);
//     close(g_red_out_fd);
// }

void set_prev_pipe()
{
	close(g_pipe_fd[1]);
	dup2(g_pipe_fd[0], 0);
	close(g_pipe_fd[0]);
}

void set_post_pipe()
{
	close(g_pipe_fd[0]);
	dup2(g_pipe_fd[1], 1);
	close(g_pipe_fd[1]);
}

void set_red_out(char *title)
{
	g_red_out_fd = open(title, O_CREAT | O_RDWR);
	dup2(g_red_out_fd, 1);
	close(g_red_out_fd);
}

void set_pipe(char *cmd[], int pipe_idx)
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
        if (i == 1)
            execlp("ls", "ls", "-al", NULL);
        if (i == 2)
            execlp("grep", "grep", "Sep", NULL);
    }
    close(g_pipe_fd[1]);
    dup2(g_pipe_fd[0], 0);
    close(g_pipe_fd[0]);
}

void test(void)
{
    /* ;�ݷ����� ������ ���� ����� ���Դٰ� ��������! */
    char *cmd[6] = {"ls", "-al", "|", "grep", "Sep", NULL};
    /* ���� § �ɷ� �̷��Ը��̶� �ǳ� �� �� �غ��� */
    int i;

    i = 0;
    while (cmd[i])
    {
        if (!strcmp(cmd[i], "|"))
            set_pipe(cmd, i);
        if (!strcmp(cmd[i], ">"))
            set_red_out(cmd[i + 1]);
        i++;
    }
    
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}
