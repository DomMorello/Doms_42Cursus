#include "./minishell.h"

extern char **environ;
t_list *g_env_list;
t_list g_env_head;
// 쉘 변수를 담을 링크드 리스트도 필요할 것 같다.

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
	t_list *env_tmp;

    path = NULL;
    ret = NULL;
	env_tmp = g_env_list;
    while (env_tmp)
    {
        if (!ft_strncmp(PATH, env_tmp->content, ft_strlen(PATH)))
        {
            path = env_tmp->content;
            break ;
        }
        env_tmp = env_tmp->next;
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
	int a = closedir(dir_p);
	if (a == -1)
		perror("closedir err");
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

char *find_home(void)
{
	t_list *env_tmp;

	env_tmp = g_env_list;
	while (env_tmp)
	{
        if (!ft_strncmp(HOME, env_tmp->content, ft_strlen(HOME)))
            return ((char *)env_tmp->content);
		env_tmp = env_tmp->next;
	}
	return (NULL);
}

void dir_to_HOME(char *cmd[], int is_pipe)
{
	char *home;

	home = find_home();
	if (home)
	{
		home += ft_strlen(HOME);
		change_dir(cmd, home, is_pipe);
	}
	else
	{
		ft_putstr_fd("mongshell: cd: ", 2);
		ft_putstr_fd("HOME not found\n", 2);
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
	else if (argc == 1)
	{
		dir_to_HOME(cmd, is_pipe);
	}
	else
	{
		change_dir(cmd, dir, is_pipe);
	}
}

void exec_unset(char *cmd[], int prev_pipe_idx, int pipe_idx, int argc)
{
	printf("unset!!\n");
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
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("getcwd err");
	else
	{
		ft_putstr_fd(cwd, STDOUT);
		ft_putstr_fd("\n", STDOUT);
		free(cwd);
	}
}

int find_env_path(void)
{
	t_list *env_tmp;
	char *needle;

	env_tmp = g_env_list;
	while (env_tmp)
	{
        if (!ft_strncmp(PATH, env_tmp->content, ft_strlen(PATH)))
        {
			needle = ft_strnstr((char *)env_tmp->content, USRBIN, ft_strlen((char *)env_tmp->content));
			if (needle)
				return (TRUE);
		}
		env_tmp = env_tmp->next;
	}
	return (FALSE);
}

void exec_env(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
	int argc;
	t_list *env_tmp;

	env_tmp = g_env_list;
	argc = get_argc(cmd, prev_pipe_idx, pipe_idx);
	if (argc == 1 && find_env_path())
	{
		while (env_tmp)
		{
			ft_putstr_fd((char *)env_tmp->content, STDOUT);
			ft_putstr_fd("\n", STDOUT);
			env_tmp = env_tmp->next;
		}
	}
}

void	sort_export(t_list **list)
{
	int swapped;
	t_list *ptr1;
	t_list *lptr;
	char *tmp;
	
	swapped = 1;
	ptr1 = NULL;
	lptr = NULL;
	tmp = NULL;
	while (swapped)
	{
		swapped = 0;
		ptr1 = *list;
		while (ptr1->next != lptr)
		{
			if (ft_strncmp(ptr1->content, ptr1->next->content, ft_strlen(ptr1->content)) > 0)
			{
				tmp = ptr1->content;
				ptr1->content = ptr1->next->content;
				ptr1->next->content = tmp;
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

void add_dquote(char *new, char *line)
{
	int i;

	i = 0;
	while (new[i])
	{
		if (new[i] == '=')
		{
			i++;
			new[i] = '\"';
			i++;
			while (new[i])
			{
				new[i] = line[i - 1];
				i++;
			}
			new[i] = line[i - 1];
			i++;
			new[i] = '\"';
			new[i + 1] = '\0';
		}
		i++;
	}
}

void print_export(char *line)
{
	char *new;
	int i;

	i = 0;
	new = (char *)malloc(sizeof(char) * ft_strlen(line) + 3);
	if (!new)
		exit(-1);	//malloc fucked up
	ft_strlcpy(new, line, ft_strlen(line) + 1);
	add_dquote(new, line);
	ft_putstr_fd("declare -x ", STDERR);
	ft_putstr_fd(new, STDERR);
	ft_putstr_fd("\n", STDERR);
}

void exec_export(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
	t_list *export_tmp;

	export_tmp = g_env_list;
	sort_export(&export_tmp);
	while (export_tmp)
	{
		print_export((char *)export_tmp->content);
		export_tmp = export_tmp->next;
	}
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
	if (!ft_strncmp(PWD, token, ft_strlen(token)))
		exec_pwd(cmd, i, pipe_idx);
	else if (!ft_strncmp(ENV, token, ft_strlen(token)))
		exec_env(cmd, i, pipe_idx);
	else if (!ft_strncmp(EXPORT, token, ft_strlen(token)))
		exec_export(cmd, i, pipe_idx);
	else
		handle_executable(token, cmd, i, pipe_idx);
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

	copy_environ();	//프로그램 종료 전에 링크드 리스트 전부 free해줘야 한다
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
    	test(cmd);	//명령어 처리 함수
		free(line);
		free_2d_char(cmd);
	}
    return 0;
}
