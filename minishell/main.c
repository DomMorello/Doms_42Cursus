#include "./minishell.h"

extern char *environ[];

int g_pipe_fd[2];
int g_red_out_fd;
int g_red_in_fd;

void set_red_out(char *title)
{
	g_red_out_fd = open(title, O_CREAT | O_RDWR);
    perror("red out open");
	dup2(g_red_out_fd, 1);
	close(g_red_out_fd);
}

void set_red_in(char *title)
{
	g_red_in_fd = open(title, O_CREAT | O_RDWR);
    perror("red in open");
	dup2(g_red_in_fd, 0);
	close(g_red_in_fd);
}

void set_red_double_out(char *title)
{
    g_red_out_fd = open(title, O_CREAT | O_RDWR | O_APPEND);
    perror("double open");
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

void process_redirection(char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
    int i;

    i = *prev_pipe_idx;
    while (cmd[i] && i < pipe_idx)
    {
        if (!strcmp(cmd[i], ">"))
            set_red_out(cmd[i + 1]);
        if (!strcmp(cmd[i], "<"))
            set_red_in(cmd[i + 1]);
        if (!strcmp(cmd[i], ">>"))
            set_red_double_out(cmd[i + 1]);
        i++;
    }
}

int is_usr_bin(char *cmd, int *is_in_usr_bin)
{
    struct dirent *usr_bin;
    DIR *usr_bin_p;

    usr_bin_p = opendir("/usr/bin");
    usr_bin = readdir(usr_bin_p);
    while (usr_bin)
    {
        if (!strcmp(usr_bin->d_name, cmd))
        {
            *is_in_usr_bin = 1;
            break ;
        }
        usr_bin = readdir(usr_bin_p);
    }
}

int is_bin(char *cmd, int *is_in_bin)
{
    struct dirent *bin;
    DIR *bin_p;

    bin_p = opendir("/bin");
    bin = readdir(bin_p);
    while (bin)
    {
        if (!strcmp(bin->d_name, cmd))
        {
            *is_in_bin = 1;
            break ;
        }
        bin = readdir(bin_p);
    }
}

void handle_executable(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
    int is_in_usr_bin;
    int is_in_bin;

    is_in_usr_bin = 0;
    is_in_bin = 0;
    is_usr_bin(cmd[prev_pipe_idx], &is_in_usr_bin);
    is_bin(cmd[prev_pipe_idx], &is_in_bin);
    printf("is usr bin: %d\n", is_in_usr_bin);
    printf("is bin: %d\n", is_in_bin);
    // while (prev_pipe_idx < pipe_idx)
    // {
        
    // }
}

void handle_executable2(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
    int is_in_usr_bin;
    int is_in_bin;

    is_in_usr_bin = 0;
    is_in_bin = 0;
    is_usr_bin(cmd[prev_pipe_idx + 1], &is_in_usr_bin);
    is_bin(cmd[prev_pipe_idx + 1], &is_in_bin);
    printf("is usr bin: %d\n", is_in_usr_bin);
    printf("is bin: %d\n", is_in_bin);

    // while (++prev_pipe_idx < pipe_idx)
    // {
    //     printf("handle: %s\n", cmd[prev_pipe_idx]);
    // }
}

void parse_cmd(char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
    int i;

    i = *prev_pipe_idx;
    if (i == 0)
        handle_executable(cmd, i, pipe_idx); //함수 이름은 나중에 적절하게 바꾸자
    else
        handle_executable2(cmd, i, pipe_idx);
}

void exec_cmd(char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
    static int i = 0;

    i++;
    pid_t pid = fork();
    if (pid == 0)
    {
        // set_pipe_child();
        // process_redirection(cmd, prev_pipe_idx, pipe_idx);
        // if (i == 1)
        //     execlp("grep", "grep", "Sep", NULL);
        // if (i == 2)
        //     execlp("grep", "grep", "Sep", NULL);
        // if (i == 3)
        //     execlp("wc", "wc", NULL);
        parse_cmd(cmd, prev_pipe_idx, pipe_idx);
        exit(1);
    }
    else if (pid < 0)
    {
        perror("fork err");
    }
    else
    {
        wait(NULL);
        // set_pipe_parent();
    }
}

void process_pipe(char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
    if (!strcmp(cmd[pipe_idx], "|"))
    {
        // pipe(g_pipe_fd);
        // perror("pipe err");
        exec_cmd(cmd, prev_pipe_idx, pipe_idx);
        *prev_pipe_idx = pipe_idx;
    }
}

void exec_last_cmd(char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
    // process_redirection(cmd, prev_pipe_idx, pipe_idx);
    // execlp("wc", "wc", NULL);
    parse_cmd(cmd, prev_pipe_idx, pipe_idx);
}

void test(void)
{
    /* ;콜론으로 나눠진 것이 여기로 들어왔다고 가정하자! */
    char *cmd[50] = {"ls", "-al", "|", "grep", "Sep", "|", "wc", ">",
            "hello1", ">", "hello2", "|", "echo", "hi", ">", "hello3", NULL};

    // char *cmd[50] = {"grep", "Sep", "<", "hello1", "|", "wc", "<", "hello1", NULL};

    // char *cmd[50] = {"ls", "-al", "|", "grep", "Sep", ">>", "hello1", "|",
    //                 "echo", "hi", ">>", "hello1", NULL};

    // char *cmd[50] = {"grep", "Sep", "<", "hello1", "|", "wc", ">>", "hello1", ">>", "hello2", NULL};

    int i;
    int prev_pipe_idx;

    prev_pipe_idx = 0;
    i = 0;
    while (cmd[i])
    {
        process_pipe(cmd, &prev_pipe_idx, i);
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