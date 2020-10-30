#include "./minishell.h"

extern char **environ;
t_list *g_env_list;
t_list g_env_head;

int g_pipe_fd[2];
int g_stdin;
int g_stdout;
int g_red_out_fd;
int g_red_in_fd;

void set_red_out(char *title)
{
	if ((g_red_out_fd = open(title, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) != ERROR)
	{
		perror("red out open");
		dup2(g_red_out_fd, 1);
		perror("dup2");
		close(g_red_out_fd);
	}
}

void set_red_in(char *title)
{
	if ((g_red_in_fd = open(title, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) != ERROR)
	{
		perror("red in open");
		dup2(g_red_in_fd, 0);
		perror("dup2");
		close(g_red_in_fd);
	}
}

void set_red_double_out(char *title)
{
    if ((g_red_out_fd = open(title, O_CREAT | O_RDWR | O_APPEND)) != ERROR)
	{
		perror("double open");
		dup2(g_red_out_fd, 1);
		perror("dup2");
		close(g_red_out_fd);
	}
}

void set_pipe_child()
{
	close(g_pipe_fd[0]);
	dup2(g_pipe_fd[1], 1);
	perror("pipe dup2");
	close(g_pipe_fd[1]);
}

void set_pipe_parent()
{
	close(g_pipe_fd[1]);
	dup2(g_pipe_fd[0], 0);
	perror("pipe dup2");
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

void exec_executable(char *cmd[], int prev_pipe_idx, int pipe_idx, char *filepath)
{
    char **argv;
    int argc;
    int i;
	int token;

    i = 0;
	token = prev_pipe_idx;
    argv = NULL;
    argc = get_argc(cmd, prev_pipe_idx, pipe_idx);
    if (!(argv = (char **)malloc(sizeof(char *) * argc + 1)))
        exit(-1);   //malloc 실패 아웃!
    while (prev_pipe_idx < pipe_idx && !is_redirection(cmd[prev_pipe_idx]))
        argv[i++] = cmd[prev_pipe_idx++];
	argv[i] = NULL;
	if (execve(filepath, argv, environ) == -1)
	{
		/* 에러 구체화해서 에러메세지 처리할 필요 있음 */
		if (errno == 2)
		{
			ft_putstr_fd("mongshell: ", STDERR);
			ft_putstr_fd(cmd[token], STDERR);
			ft_putstr_fd(": command not found\n", STDERR);	
		}
		else
		{
			ft_putstr_fd("mongshell: ", STDERR);
			ft_putstr_fd(cmd[token], STDERR);
			ft_putstr_fd(": ", STDERR);
			strerror(errno);
		}
	}
}

void exec_executable2(char *cmd[], int prev_pipe_idx, int pipe_idx, char *filepath)
{
    char **argv;
    int argc;
	int i;
	int token;

	token = prev_pipe_idx + 1;
	i = 0;
    argv = NULL;
    argc = get_argc(cmd, prev_pipe_idx, pipe_idx);
	if (!(argv = (char **)malloc(sizeof(char *) * argc + 1)))
        exit(-1);   //malloc 실패 아웃!
    while (++prev_pipe_idx < pipe_idx && !is_redirection(cmd[prev_pipe_idx]))
        argv[i++] = cmd[prev_pipe_idx];
	argv[i] = NULL;
	if (execve(filepath, argv, environ) == -1)
	{
		if (errno == 2)
		{
			ft_putstr_fd(cmd[token], STDERR);
			ft_putstr_fd(": command not found\n", STDERR);	
		}
		else
		{
			ft_putstr_fd(cmd[token], STDERR);
			ft_putstr_fd(": ", STDERR);
			strerror(errno);
		}
	}
}

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

void		free_2d_char(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
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
	free_2d_char(path);
	return (ret);
}

void handle_executable(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
	char **path;
    char *filepath;

    path = get_path();
    filepath = get_filepath(cmd[prev_pipe_idx], path);	//free 불가
    exec_executable(cmd, prev_pipe_idx, pipe_idx, filepath);
}

void handle_executable2(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
	char **path;
    char *filepath;

    path = get_path();
    filepath = get_filepath(cmd[prev_pipe_idx + 1], path);	//free 불가
    exec_executable2(cmd, prev_pipe_idx, pipe_idx, filepath);
}

void exec_echo(char *cmd[], char *token, int prev_pipe_idx, int pipe_idx)
{
	printf("%s\n", token);
}

void exec_cd(char *cmd[], char *token, int prev_pipe_idx, int pipe_idx)
{
	int argc;
	char **argv;
	int i;

	i = 0;
    argv = NULL;
    argc = get_argc(cmd, prev_pipe_idx, pipe_idx);
    if (!(argv = (char **)malloc(sizeof(char *) * argc + 1)))
        exit(-1);   //malloc 실패 아웃!
    while (prev_pipe_idx < pipe_idx && !is_redirection(cmd[prev_pipe_idx]))
        argv[i++] = cmd[prev_pipe_idx++];
	argv[i] = NULL;
}

void exec_pwd(char *cmd[], char *token, int prev_pipe_idx, int pipe_idx)
{
	printf("%s\n", token);
}

void exec_export(char *cmd[], char *token, int prev_pipe_idx, int pipe_idx)
{
	printf("%s\n", token);
}

void exec_unset(char *cmd[], char *token, int prev_pipe_idx, int pipe_idx)
{
	printf("%s\n", token);
}

void exec_env(char *cmd[], char *token, int prev_pipe_idx, int pipe_idx)
{
	printf("%s\n", token);
}

void exec_exit(char *cmd[], char *token, int prev_pipe_idx, int pipe_idx)
{
	printf("%s\n", token);
}

/*
	어떻게 해야 중복된 함수를 만들지 않고 함수 포인터를 써서 잘 할 수 있을까? 
*/
// int handle_built_in(char *cmd[], int prev_pipe_idx, int pipe_idx)
// {
// 	if (!strcmp(cmd[prev_pipe_idx], ECHO))
// 		exec_built_in(exec_echo);
// 	if (!strcmp(cmd[prev_pipe_idx], CD))
// 		exec_built_in(exec_cd);
// 	if (!strcmp(cmd[prev_pipe_idx], PWD))
// 		exec_built_in(exec_pwd);
// 	if (!strcmp(cmd[prev_pipe_idx], EXPORT))
// 		exec_built_in(exec_export);
// 	if (!strcmp(cmd[prev_pipe_idx], UNSET))
// 		exec_built_in(exec_unset);
// 	if (!strcmp(cmd[prev_pipe_idx], ENV))
// 		exec_built_in(exec_env);
// 	if (!strcmp(cmd[prev_pipe_idx], EXIT))
// 		exec_built_in(exec_exit);
// }

// int handle_built_in2(char *cmd[], int prev_pipe_idx, int pipe_idx)
// {
// 	if (!strcmp(cmd[prev_pipe_idx + 1], ECHO))
// 		exec_built_in(exec_echo);
// 	if (!strcmp(cmd[prev_pipe_idx + 1], CD))
// 		exec_built_in(exec_cd);
// 	if (!strcmp(cmd[prev_pipe_idx + 1], PWD))
// 		exec_built_in(exec_pwd);
// 	if (!strcmp(cmd[prev_pipe_idx + 1], EXPORT))
// 		exec_built_in(exec_export);
// 	if (!strcmp(cmd[prev_pipe_idx + 1], UNSET))
// 		exec_built_in(exec_unset);
// 	if (!strcmp(cmd[prev_pipe_idx + 1], ENV))
// 		exec_built_in(exec_env);
// 	if (!strcmp(cmd[prev_pipe_idx + 1], EXIT))
// 		exec_built_in(exec_exit);
// }

int is_built_in(char *token)
{
	if (!strcmp(token, ECHO) || !strcmp(token, CD) ||
		!strcmp(token, PWD) || !strcmp(token, EXPORT)
		|| !strcmp(token, UNSET) || !strcmp(token, ENV)
		|| !strcmp(token, EXIT))
	  	return (TRUE);
	return (FALSE);
}

void parse_cmd(char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
    int i;

    i = *prev_pipe_idx;
    if (i == 0)
	{
		if (is_built_in(cmd[i]))
			;// handle_built_in(cmd, i, pipe_idx);
		else
        	handle_executable(cmd, i, pipe_idx);
	}
    else
	{
		if (is_built_in(cmd[i + 1]))
			;// handle_built_in2(cmd, i, pipe_idx);
		else
    		handle_executable2(cmd, i, pipe_idx);
	}
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
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		process_redirection(cmd, prev_pipe_idx, pipe_idx);
		parse_cmd(cmd, prev_pipe_idx, pipe_idx);
	}
	else
	{
		wait(NULL);
	}
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

void test(char **cmd)
{
    /* ;콜론으로 나눠진 것이 여기로 들어왔다고 가정하자! */
    // char *cmd[50] = {"ls", "-al", "|", "/bin/grep", "Sep", "|", "/usr/bin/wc", ">",
    //         "hello1", ">", "hello2", /*"|", "echo", "hi", ">", "hello3",*/ NULL};

    // char *cmd[50] = {"grep", "Sep", "<", "hello1", "|", "wc", "<", "hello1", NULL};

    // char *cmd[50] = {"ls", "-al", "|", "grep", "Sep", ">>", "hello1", "|",
    //                 "echo", "hi", ">>", "hello1", NULL};

    // char *cmd[50] = {"grep", "Sep", "<", "hello1", "|", "wc", ">>", "hello1", ">>", "hello2", NULL};

	// char *cmd[50] = {"ls", "-al", "|", "grep", "Sep", NULL};
	// char *cmd[50] = {"cd", "libft", "|", "echo", "hi", NULL};

	int i;
	int prev_pipe_idx;

	g_stdin = dup(0);
	perror("setup std dup");
	g_stdout = dup(1);
	perror("setup std dup");

	prev_pipe_idx = 0;
	i = 0;
	while (cmd[i])
	{
		process_pipe(cmd, &prev_pipe_idx, i);
		i++;
		if (!cmd[i])
			exec_last_cmd(cmd, &prev_pipe_idx, i);
	}
	dup2(g_stdin, 0);
	perror("take back dup2");
	dup2(g_stdout, 1);
	perror("take back dup2");
}

int main(int argc, char *argv[])
{
	int ret = 0;
	char *line;

	copy_environ();	//이건 테스트코드가 아니다.
	while (1)
	{
		char **cmd;
		if ((ret = get_next_line(0, &line)) < 0)
		{
			printf("gnl error\n");
			free(line);
			exit(0);
		}
		cmd = ft_split(line, ' ');
    	test(cmd);
		free(line);
		free_2d_char(cmd);
	}

    return 0;
}
