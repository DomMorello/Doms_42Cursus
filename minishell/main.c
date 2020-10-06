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

void process_cmd(char *cmd[])
{
    int i;

    i = 0;
    while (cmd[i])
    {
        if (!strcmp(cmd[i], "|"))
            set_pipe(cmd, i);
        if (!strcmp(cmd[i], ">"))
            set_red_out(cmd, i);    //�̷��� ��ɾ �� �����鼭 �ؾ��ұ�
                                    //�ƴ� ���� ������ �ϰ� �ؾ� �ϳ�?
                                    //�ϴ� � ������ �Ǵ����� �� �� ����
        i++;
    }
}

void test(void)
{
    /* ;�ݷ����� ������ ���� ����� ���Դٰ� ��������! */
    int is_pipe;
    char *cmd[15] = {"ls", "-al", "|", "grep", "Sep", ">", "hello1", "|", "ls", "-al", "|", "wc", ">", "hello2", NULL};

    is_pipe = 0;
    process_cmd(cmd);

}

int main(int argc, char *argv[])
{
    test();
    return 0;
}
