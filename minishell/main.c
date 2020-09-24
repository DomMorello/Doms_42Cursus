#include "./minishell.h"

extern char *environ[];

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

void parse_pipe(char *cmd[])
{
    if (is_pipe(cmd))
    {
        /*  token을 나눠야 하는데;;;
            "ls -al |"
            "| grep D > test"
            이렇게 나눌 수 있을까? 이미 나눠져서 오는데;
        */
        
    }
}

void test(void)
{
    char *cmd[8] = {"ls", "-al", "|", "grep", "D", ">", "test", NULL};
    int i = 0;

    while (cmd[i])
    {
        parse_pipe(&cmd[i]);
        // parse_redirection(&cmd[i]);
        // exec_cmd(&cmd[i]);
        i++;
    }
}

// ls -al | grep D > test
int main(int argc, char *argv[])
{
    test();
    return 0;
}
