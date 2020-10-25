#include "./minishell.h"

extern char **environ;
t_list *g_env_list;
t_list g_env_head;

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

int is_redirection(char *token)
{
    if (!strcmp(token, ">") || !strcmp(token, ">>")
        || !strcmp(token, "<"))
        return (TRUE);
    return (FALSE);
}

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

// void exec_executable(char *cmd[], int prev_pipe_idx, int pipe_idx, int which_dir)
// {
//     char **argv;
// 	char *filepath;
//     int argc;
//     int i;

//     i = 0;
//     argv = NULL;
//     argc = get_argc(cmd, prev_pipe_idx, pipe_idx);
// 	filepath = get_filepath(cmd[prev_pipe_idx], which_dir);
//     if (!(argv = (char **)malloc(sizeof(char *) * argc + 1)))
//         exit(-1);   //malloc 실패 아웃!
//     while (prev_pipe_idx < pipe_idx && !is_redirection(cmd[prev_pipe_idx]))
//         argv[i++] = cmd[prev_pipe_idx++];
// 	argv[i] = NULL;
// 	execve(filepath, argv, environ);
// }

// void exec_executable2(char *cmd[], int prev_pipe_idx, int pipe_idx, int which_dir)
// {
//     char **argv;
// 	char *filepath;
//     int argc;
// 	int i;

// 	i = 0;
//     argv = NULL;
//     argc = get_argc(cmd, prev_pipe_idx, pipe_idx);
// 	filepath = get_filepath(cmd[prev_pipe_idx + 1], which_dir);
// 	if (!(argv = (char **)malloc(sizeof(char *) * argc + 1)))
//         exit(-1);   //malloc 실패 아웃!
//     while (++prev_pipe_idx < pipe_idx && !is_redirection(cmd[prev_pipe_idx]))
//         argv[i++] = cmd[prev_pipe_idx];
// 	argv[i] = NULL;
// 	execve(filepath, argv, environ);
// }

char **get_path(void)
{
    char *path;
    char **ret;

    path = NULL;
    ret = NULL;
    while (g_env_list)
    {
        if (!ft_strncmp(PATH, g_env_list->content, ft_strlen(PATH)))
        {
            path = g_env_list->content;
            break ;
        }
        g_env_list = g_env_list->next;
    }
    if (path)
    {
        path += ft_strlen(PATH);
        ret = ft_split(path, ':');
    }
    return (ret);
}

int search_dir(char *token, char *path)
{
    struct dirent *dir;
    DIR *dir_p;

    if (dir_p = opendir(path))
    {
        dir = readdir(dir_p);
        while (dir)
        {
            if (!strcmp(dir->d_name, token))
                return (TRUE);
            dir = readdir(dir_p);
        }
    }
    return (FALSE);
}

// char *get_filepath(char *token, int which_dir)
// {
// 	char *ret;

// 	ret = NULL;
// 	if (which_dir == 1)
// 	{
// 		if (!(ret = (char *)malloc(sizeof(char) * (ft_strlen(USR_BIN_STR) + ft_strlen(token) + 1))))
// 			exit(-1); //malloc fail -> boom
// 		ft_strlcpy(ret, USR_BIN_STR, ft_strlen(USR_BIN_STR) + 1);
// 		ret[ft_strlen(USR_BIN_STR)] = '\0';
// 		ft_strlcat(ret, token, ft_strlen(ret) + ft_strlen(token) + 1);
// 	}
// 	else if (which_dir == 2)
// 	{
// 		if (!(ret = (char *)malloc(sizeof(char) * (ft_strlen(BIN_STR) + ft_strlen(token) + 1))))
// 			exit(-1); //malloc fail -> boom
// 		ft_strlcpy(ret, BIN_STR, ft_strlen(BIN_STR) + 1);
// 		ret[ft_strlen(BIN_STR)] = '\0';
// 		ft_strlcat(ret, token, ft_strlen(ret) + ft_strlen(token) + 1);
// 	}
// 	return (ret);
// }

    // if (tmp)
    //     ft_strlcat(tmp, "/", ft_strlen(tmp) + 2);
	// ret = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + ft_strlen(token) + 1));
    // ret = tmp;
    // ft_strlcat(ret, token, ft_strlen(token) + ft_strlen(ret) + 1);
    // printf("ret: %s\n", ret);

void cat_filepath(char **ret, char **tmp, char *token)
{
	if (*tmp)
	{
		ft_strlcat(*tmp, "/", ft_strlen(*tmp) + 2);
		*ret = (char *)malloc(sizeof(char) * (ft_strlen(*tmp) + ft_strlen(token) + 1));
		*ret = *tmp;
		ft_strlcat(*ret, token, ft_strlen(token) + ft_strlen(*ret) + 1);
	}
	else
		*ret = token;
}


char *get_filepath(char *token, char **path)
{
    char *tmp;
    char *ret;
    int i;

    tmp = NULL;
    ret = NULL;
    i = 0;
    while (path[i])
    {
        if (search_dir(token, path[i]))
        {
            tmp = path[i];
            break ;
        }
        i++;
    }
	cat_filepath(&ret, &tmp, token);
	printf("ret: %s\n", ret);
}

void handle_executable(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
	char **path;
    char *filepath;

    path = get_path();
    filepath = get_filepath(cmd[prev_pipe_idx], path);
	/* 여기서 절대경로나 상대경로로 와도 filepath를 적절하게 얻어와서
		exec_executable함수로 filepath를 매개변수로 넘겨주면서 하면 될 듯 */
	
    // int which_dir;

    // which_dir = 0;
    // is_usr_bin(cmd[prev_pipe_idx], &which_dir);
    // is_bin(cmd[prev_pipe_idx], &which_dir);
    
    // exec_executable(cmd, prev_pipe_idx, pipe_idx, which_dir);
}

void handle_executable2(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
    // int which_dir;

    // which_dir = 0;
    // is_usr_bin(cmd[prev_pipe_idx + 1], &which_dir);
    // is_bin(cmd[prev_pipe_idx + 1], &which_dir);
    
    // exec_executable2(cmd, prev_pipe_idx, pipe_idx, which_dir);
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

void copy_environ(void)
{
	int i;
	t_list *tmp;

	g_env_head.content = environ[0];
	g_env_head.next = NULL;
	g_env_list = &g_env_head;
	i = 1;
	while (environ[i])
	{
		tmp = ft_lstnew(environ[i]);
		ft_lstadd_back(&g_env_list, tmp);
		i++;
	}
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

	// char *cmd[50] = {"/bin/ls", NULL};
	char *cmd[50] = {"ls", NULL};
    
	int i;
    int prev_pipe_idx;

    prev_pipe_idx = 0;
    i = 0;
	copy_environ();
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