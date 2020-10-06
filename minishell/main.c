#include "./minishell.h"

extern char *environ[];

int g_pipe_fd[2];
int g_red_out_fd;
int g_red_in_fd;

// void set_red_out(char *cmd[], int red_idx)
// {
//     g_red_out_fd = open(cmd[red_idx + 1], O_CREAT | O_RDWR);
//     /* 이렇게 하면 > 가 여러개 나오더라도 마지막에 나온 fd가 복제되니까 괜찮겠찌? */
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
            set_red_out(cmd, i);    //이렇게 명령어를 쭉 읽으면서 해야할까
                                    //아님 먼저 세팅을 하고 해야 하나?
                                    //일단 어떤 식으로 되는지를 한 번 보자
        i++;
    }
}

void test(void)
{
    /* ;콜론으로 나눠진 것이 여기로 들어왔다고 가정하자! */
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
