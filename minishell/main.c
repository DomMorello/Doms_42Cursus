#include "./minishell.h"

extern char **environ;
t_list *g_env_list;
t_list g_env_head;

int g_pipe_fd[2];
int g_red_out_fd;
int g_red_in_fd;

void set_red_out(char *title)
{
	if ((g_red_out_fd = open(title, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) != ERROR)
	{
		int a = dup2(g_red_out_fd, 1);
		if (a == -1)
			perror("dup2");
		close(g_red_out_fd);
	}
	if (g_red_out_fd == -1)
		perror("red out open");
	
}

void set_red_in(char *title, char *token)
{
	struct stat file;

	if (!stat(title, &file))
	{
		if (S_ISDIR(file.st_mode))
		{
			ft_putstr_fd(token, 2);
			ft_putstr_fd(": (standard input): Is a directory\n", 2);
			exit(-1);
		}
		else
		{
			if ((g_red_in_fd = open(title, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) != ERROR)
			{
				int a = dup2(g_red_in_fd, 0);
				if (a == -1)
					perror("dup2");
				close(g_red_in_fd);
			}
			if (g_red_in_fd == -1)
				perror("red in open");		
		}	
	}
	else
	{
		ft_putstr_fd("momgshell: ", 2);
		ft_putstr_fd(title, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(-1);
	}
}

void set_red_double_out(char *title)
{
    if ((g_red_out_fd = open(title, O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR)) != ERROR)
	{
		int a = dup2(g_red_out_fd, 1);
		if (a == -1)
			perror("dup2");
		close(g_red_out_fd);
	}
	if (g_red_out_fd == -1)
		perror("red double out open");
}

void set_pipe_child()
{
	close(g_pipe_fd[0]);
	int a = dup2(g_pipe_fd[1], 1);
	if (a == -1)
		perror("pipe dup2");
	close(g_pipe_fd[1]);
}

void set_pipe_parent()
{
	close(g_pipe_fd[1]);
	int a = dup2(g_pipe_fd[0], 0);
	if (a == -1)
		perror("pipe dup2");
	close(g_pipe_fd[0]);
}

void process_redirection(char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
    int i;
	char *token;

    i = *prev_pipe_idx;
	if (i == 0)
		token = cmd[i];
	else
		token = cmd[i + 1];
    while (cmd[i] && i < pipe_idx)
    {
        if (!strcmp(cmd[i], ">"))
            set_red_out(cmd[i + 1]);
        if (!strcmp(cmd[i], "<"))
            set_red_in(cmd[i + 1], token);
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
			exit(-1);	//종료상태 구현해야 함.
		}
		else
		{
			ft_putstr_fd("mongshell: ", STDERR);
			ft_putstr_fd(cmd[token], STDERR);
			ft_putstr_fd(": ", STDERR);
			ft_putstr_fd(strerror(errno), STDERR);
			exit(-1);
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
			ft_putstr_fd("mongshell: ", STDERR);
			ft_putstr_fd(cmd[token], STDERR);
			ft_putstr_fd(": command not found\n", STDERR);	
			exit(-1);
		}
		else
		{
			ft_putstr_fd("mongshell: ", STDERR);
			ft_putstr_fd(cmd[token], STDERR);
			ft_putstr_fd(": ", STDERR);
			ft_putstr_fd(strerror(errno), STDERR);
			exit(-1);
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
		if (!dir)
			perror("read dir err");
        while (dir)
        {
            if (!strcmp(dir->d_name, token))
                return (TRUE);
            dir = readdir(dir_p);
        }
    }
	else
		perror("opendir err");
	
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

void handle_executable(char *token, char *cmd[], int prev_pipe_idx, int pipe_idx)
{
	char **path;
    char *filepath;

    path = get_path();
    filepath = get_filepath(token, path);	//free 불가
	if (prev_pipe_idx == 0)
    	exec_executable(cmd, prev_pipe_idx, pipe_idx, filepath);
	else
		exec_executable2(cmd, prev_pipe_idx, pipe_idx, filepath);
}

// void handle_executable2(char *cmd[], int prev_pipe_idx, int pipe_idx)
// {
// 	char **path;
//     char *filepath;

//     path = get_path();
//     filepath = get_filepath(cmd[prev_pipe_idx + 1], path);	//free 불가
//     exec_executable2(cmd, prev_pipe_idx, pipe_idx, filepath);
// }

void exec_echo(char *cmd[], int prev_pipe_idx, int pipe_idx, int argc)
{
	printf("echo!!\n");
}

int find_pipe(char *cmd[])
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (!strcmp(cmd[i], "|"))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void change_dir(char *cmd[], char *dir, int is_pipe)
{
	struct stat file;
	char buf[100];
	char *cwd;

	//이 부분에서 cd만 들어왔을 경우 stat에 들어가면서
	//dir이 없는데도 실행하니까 세그폴트가 나는 것이다. 
	if (!stat(dir, &file))
	{
		if (!is_pipe)
		{
			if (!chdir(dir))
			{
				cwd = getcwd(buf, sizeof(buf));	//test
				ft_putstr_fd(cwd, 2);
				ft_putstr_fd("\n", 2);
			}
			else
			{
				// perror("chdir err");
				ft_putstr_fd("mongshell: cd: ", 2);
				ft_putstr_fd(dir, 2);
				ft_putstr_fd(": Not a directory\n", 2);
			}
		}
	}
	else
	{
		// perror("stat err");
		ft_putstr_fd("mongshell: cd: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

void exec_cd(char *cmd[], int prev_pipe_idx, int pipe_idx, int argc)
{
	int is_pipe;
	char *dir;

	if (prev_pipe_idx == 0)
		dir = cmd[prev_pipe_idx + 1];
	else
		dir = cmd[prev_pipe_idx + 2];
	
	is_pipe = find_pipe(cmd);	//이게 1이면 chdir을 하지 않는다.
	if (argc > 2)
	{
		if (prev_pipe_idx == 0)
		{
			ft_putstr_fd("mongshell: ", 2);
			ft_putstr_fd(cmd[prev_pipe_idx], 2);
			ft_putstr_fd(": too many arguments\n", 2);
		}
		else
		{
			ft_putstr_fd("mongshell: ", 2);
			ft_putstr_fd(cmd[prev_pipe_idx + 1], 2);
			ft_putstr_fd(": too many arguments\n", 2);
		}
	}
	else
	{
		change_dir(cmd, dir, is_pipe);
	}
	//이 부분에서 argc를 확인하고 분기해서 cd만 입력이 들어왔을 경우
	//HOME을 찾아서 이동시키는 함수를 구현해야 한다.
}

void exec_export(char *cmd[], int prev_pipe_idx, int pipe_idx, int argc)
{
	printf("export!!\n");
}

void exec_unset(char *cmd[], int prev_pipe_idx, int pipe_idx, int argc)
{
	printf("unset!!\n");
}

void exec_env(char *cmd[], int prev_pipe_idx, int pipe_idx, int argc)
{
	printf("env!!\n");
}

void exec_exit(char *cmd[], int prev_pipe_idx, int pipe_idx, int argc)
{
	printf("exit!!\n");
}

void exec_nprocess_built_in(void (*exec_func)(char **, int, int, int), char **cmd, int *prev_pipe_idx, int pipe_idx)
{
	int argc;
	int prev_pipe;

	prev_pipe = *prev_pipe_idx;
    argc = get_argc(cmd, prev_pipe, pipe_idx);
	process_redirection(cmd, prev_pipe_idx, pipe_idx);
	exec_func(cmd, prev_pipe, pipe_idx, argc);
}

void exec_pwd(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
	printf("pwd!!\n");
}

void parse_cmd(char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
    int i;
	char *token;

    i = *prev_pipe_idx;
	if (i == 0)
		token = cmd[i];
	else
		token = cmd[i + 1];
	//process로 진행해야 할 명령어들 그 외에는 execve로 실행
	if (!strcmp(token, PWD))
		exec_pwd(cmd, i, pipe_idx);
	else
		handle_executable(token, cmd, i, pipe_idx);
	

    // if (i == 0)
    // 	handle_executable(token, cmd, i, pipe_idx);
    // else
	// 	handle_executable2(cmd, i, pipe_idx);
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

int is_no_process(char *token)
{
	if (!strcmp(token, CD))	//더 추가돼야 하는데 일단은 cd만
		return (TRUE);
	return (FALSE);
}

void handle_cmd(char *token, char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
	// if (!strcmp(token, ECHO))
	// 	exec_built_in(exec_echo, cmd, *prev_pipe_idx, pipe_idx);
	/*else */if (!strcmp(token, CD))
		exec_nprocess_built_in(exec_cd, cmd, prev_pipe_idx, pipe_idx);
	// else if (!strcmp(token, PWD))
	// 	exec_built_in(exec_pwd, cmd, prev_pipe_idx, pipe_idx);
	// else if (!strcmp(token, EXPORT))
	// 	exec_built_in(exec_export, cmd, prev_pipe_idx, pipe_idx);
	// else if (!strcmp(token, UNSET))
	// 	exec_built_in(exec_unset, cmd, prev_pipe_idx, pipe_idx);
	// else if (!strcmp(token, ENV))
	// 	exec_built_in(exec_env, cmd, prev_pipe_idx, pipe_idx);
	// else if (!strcmp(token, EXIT))
	// 	exec_built_in(exec_exit, cmd, prev_pipe_idx, pipe_idx);
	else
		exec_cmd(cmd, prev_pipe_idx, pipe_idx);
}

void process_pipe(char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
	char *token;

	if (*prev_pipe_idx == 0)
		token = cmd[*prev_pipe_idx];
	else
		token = cmd[*prev_pipe_idx + 1];
    if (!strcmp(cmd[pipe_idx], "|"))
    {
        int a = pipe(g_pipe_fd);
        if (a == -1)
			perror("pipe err");
		/* 여기서 명령어를 파싱해서 fork인지 아닌지를 판별 */
		// if (is_no_process(token))	//cd export 등등
		// 	handle_no_process();	//함수 실행하는 부분
		// else
        	// exec_cmd(cmd, prev_pipe_idx, pipe_idx);	//그게 아닌 경우 프로세스로 진행
		handle_cmd(token, cmd, prev_pipe_idx, pipe_idx);
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
		exit(1);
	}
	else if (pid < 0)
    {
        perror("fork err");
    }
	else
	{
		wait(NULL);
	}
}

void handle_last_cmd(char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
	char *token;
	int i;

	i = *prev_pipe_idx;
	if (i == 0)
		token = cmd[i];
	else
		token = cmd[i + 1];
	// if (!strcmp(token, ECHO))
	// 	exec_built_in(exec_echo, cmd, i, pipe_idx);
	/*else */if (!strcmp(token, CD))
		exec_nprocess_built_in(exec_cd, cmd, prev_pipe_idx, pipe_idx);
	// else if (!strcmp(token, PWD))
	// 	exec_built_in(exec_pwd, cmd, prev_pipe_idx, pipe_idx);
	// else if (!strcmp(token, EXPORT))
	// 	exec_built_in(exec_export, cmd, prev_pipe_idx, pipe_idx);
	// else if (!strcmp(token, UNSET))
	// 	exec_built_in(exec_unset, cmd, prev_pipe_idx, pipe_idx);
	// else if (!strcmp(token, ENV))
	// 	exec_built_in(exec_env, cmd, prev_pipe_idx, pipe_idx);
	// else if (!strcmp(token, EXIT))
	// 	exec_built_in(exec_exit, cmd, prev_pipe_idx, pipe_idx);
	else
		exec_last_cmd(cmd, prev_pipe_idx, pipe_idx);
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

    // char *cmd[50] = {"grep", "Sep", "<", "hello1", "|", "wc", ">>",
					// "hello1", ">>", "hello2", NULL};

	// char *cmd[50] = {"ls", "-al", "|", "grep", "Sep", NULL};
	// char *cmd[50] = {"cd", "libft", "|", "echo", "hi", NULL};

	int i;
	int prev_pipe_idx;

	int stdin_tmp = dup(0);
	if (stdin_tmp == -1)
		perror("set up dup");
	int stdout_tmp = dup(1);
	if (stdout_tmp == -1)
		perror("set up dup");

	prev_pipe_idx = 0;
	i = 0;
	while (cmd[i])
	{
		process_pipe(cmd, &prev_pipe_idx, i);
		i++;
		if (!cmd[i])
			handle_last_cmd(cmd, &prev_pipe_idx, i);
	}
	int a = dup2(stdin_tmp, 0);
	if (a == -1)
		perror("take back dup2");
	int b = dup2(stdout_tmp, 1);
	if (b == -1)
		perror("take back dup2");
}

int main(int argc, char *argv[])
{
	int ret = 0;
	char *line;

	copy_environ();
	while (1)
	{
		char **cmd;
		ft_putstr_fd("\033[0;32mmongshell\033[0;34m$ \033[0m", 2);
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
