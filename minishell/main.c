#include "./minishell.h"

extern char **environ;

int g_pipe_fd[2];
int g_red_out_fd;
int g_red_in_fd;

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t src_len;
	size_t i;

	src_len = 0;
	i = 0;
	while (src[src_len])
		src_len++;
	if (dstsize == 0)
		return (src_len);
	while (src[i] && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

size_t	ft_strlen(const char *s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t dst_len;
	size_t src_len;
	size_t i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	while (*dst)
		dst++;
	while (src[i] && i < dstsize - dst_len - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (dst_len + src_len);
}

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

int is_redirection(char *token)
{
    if (!strcmp(token, ">") || !strcmp(token, ">>")
        || !strcmp(token, "<"))
        return (TRUE);
    return (FALSE);
}

// 이런거 다 지워야 된다. 하아..
int is_usr_bin(char *cmd, int *which_dir)
{
    struct dirent *usr_bin;
    DIR *usr_bin_p;

    usr_bin_p = opendir("/usr/bin");
    usr_bin = readdir(usr_bin_p);
    while (usr_bin)
    {
        if (!strcmp(usr_bin->d_name, cmd))
        {
            *which_dir = USR_BIN_NUM;
            break ;
        }
        usr_bin = readdir(usr_bin_p);
    }
}

int is_bin(char *cmd, int *which_dir)
{
    struct dirent *bin;
    DIR *bin_p;

    bin_p = opendir("/bin");
    bin = readdir(bin_p);
    while (bin)
    {
        if (!strcmp(bin->d_name, cmd))
        {
            *which_dir = BIN_NUM;
            break ;
        }
        bin = readdir(bin_p);
    }
}

int get_argc(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
    int len;

    len = 0;
    if (prev_pipe_idx == 0)
        while (prev_pipe_idx < pipe_idx && !is_redirection(cmd[prev_pipe_idx++]))
            len++;
    else
        while (++prev_pipe_idx < pipe_idx && !is_redirection(cmd[prev_pipe_idx]))
            len++;
    return (len);
}

char *get_filepath(char *token, int which_dir)
{
	char *ret;

	ret = NULL;
	if (which_dir == 1)
	{
		if (!(ret = (char *)malloc(sizeof(char) * (ft_strlen(USR_BIN_STR) + ft_strlen(token) + 1))))
			exit(-1); //malloc fail -> boom
		ft_strlcpy(ret, USR_BIN_STR, ft_strlen(USR_BIN_STR) + 1);
		ret[ft_strlen(USR_BIN_STR)] = '\0';
		ft_strlcat(ret, token, ft_strlen(ret) + ft_strlen(token) + 1);
	}
	else if (which_dir == 2)
	{
		if (!(ret = (char *)malloc(sizeof(char) * (ft_strlen(BIN_STR) + ft_strlen(token) + 1))))
			exit(-1); //malloc fail -> boom
		ft_strlcpy(ret, BIN_STR, ft_strlen(BIN_STR) + 1);
		ret[ft_strlen(BIN_STR)] = '\0';
		ft_strlcat(ret, token, ft_strlen(ret) + ft_strlen(token) + 1);
	}
	return (ret);
}

void exec_executable(char *cmd[], int prev_pipe_idx, int pipe_idx, int which_dir)
{
    char **argv;
	char *filepath;
    int argc;
    int i;

    i = 0;
    argv = NULL;
    argc = get_argc(cmd, prev_pipe_idx, pipe_idx);
	filepath = get_filepath(cmd[prev_pipe_idx], which_dir);
    if (!(argv = (char **)malloc(sizeof(char *) * argc + 1)))
        exit(-1);   //malloc 실패 아웃!
    while (prev_pipe_idx < pipe_idx && !is_redirection(cmd[prev_pipe_idx]))
        argv[i++] = cmd[prev_pipe_idx++];
	argv[i] = NULL;
	execve(filepath, argv, environ);
}

void exec_executable2(char *cmd[], int prev_pipe_idx, int pipe_idx, int which_dir)
{
    char **argv;
	char *filepath;
    int argc;
	int i;

	i = 0;
    argv = NULL;
    argc = get_argc(cmd, prev_pipe_idx, pipe_idx);
	filepath = get_filepath(cmd[prev_pipe_idx + 1], which_dir);
	if (!(argv = (char **)malloc(sizeof(char *) * argc + 1)))
        exit(-1);   //malloc 실패 아웃!
    while (++prev_pipe_idx < pipe_idx && !is_redirection(cmd[prev_pipe_idx]))
        argv[i++] = cmd[prev_pipe_idx];
	argv[i] = NULL;
	execve(filepath, argv, environ);
}

void handle_executable(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
    int which_dir;

    which_dir = 0;
    is_usr_bin(cmd[prev_pipe_idx], &which_dir);
    is_bin(cmd[prev_pipe_idx], &which_dir);
    
    exec_executable(cmd, prev_pipe_idx, pipe_idx, which_dir);
}

void handle_executable2(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
    int which_dir;

    which_dir = 0;
    is_usr_bin(cmd[prev_pipe_idx + 1], &which_dir);
    is_bin(cmd[prev_pipe_idx + 1], &which_dir);
    
    exec_executable2(cmd, prev_pipe_idx, pipe_idx, which_dir);
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
    pid_t pid;
	
	pid = fork();
    if (pid == 0)
    {
        set_pipe_child();
        process_redirection(cmd, prev_pipe_idx, pipe_idx);
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
        set_pipe_parent();
    }
}

void process_pipe(char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
    if (!strcmp(cmd[pipe_idx], "|"))
    {
        pipe(g_pipe_fd);
        perror("pipe err");
        exec_cmd(cmd, prev_pipe_idx, pipe_idx);
        *prev_pipe_idx = pipe_idx;
    }
}

void exec_last_cmd(char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
    process_redirection(cmd, prev_pipe_idx, pipe_idx);
    parse_cmd(cmd, prev_pipe_idx, pipe_idx);
}

void test(void)
{
    /* ;콜론으로 나눠진 것이 여기로 들어왔다고 가정하자! */
    // char *cmd[50] = {"ls", "-al", "|", "grep", "Sep", "|", "wc", ">",
    //         "hello1", ">", "hello2", "|", "echo", "hi", ">", "hello3", NULL};

    // char *cmd[50] = {"grep", "Sep", "<", "hello1", "|", "wc", "<", "hello1", NULL};

    // char *cmd[50] = {"ls", "-al", "|", "grep", "Sep", ">>", "hello1", "|",
    //                 "echo", "hi", ">>", "hello1", NULL};

    // char *cmd[50] = {"grep", "Sep", "<", "hello1", "|", "wc", ">>", "hello1", ">>", "hello2", NULL};
    
	char *cmd[50] = {"ls", NULL};

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