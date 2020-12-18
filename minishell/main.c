#include "./minishell.h"

extern char **environ;
t_list *g_env_list;
t_list g_env_head;

int g_pipe_fd[2];
int g_red_out_fd;
int g_red_in_fd;
int g_exit_status;
pid_t g_pid;

void set_red_out(char *title)
{
	if ((g_red_out_fd = open(title, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) != ERROR)
	{
		int a = dup2(g_red_out_fd, 1);
		if (a == -1)
			perror("dup2");
		close(g_red_out_fd);
	}
	else
		perror("red out open");
}

void set_red_in(char *title, char *token, int is_process)
{
	struct stat file;

	if (!stat(title, &file))
	{
		if (S_ISDIR(file.st_mode))
		{
			ft_putstr_fd(token, 2);
			ft_putstr_fd(": (standard input): Is a directory\n", 2);
			g_exit_status = 1;
			if (is_process)
				exit(1);
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
		g_exit_status = 1;
		if (is_process)
			exit(1);
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

void process_redirection(char *cmd[], int *prev_pipe_idx, int pipe_idx, int is_process)
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
            set_red_in(cmd[i + 1], token, is_process);
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
		if (errno == 2)
		{
			ft_putstr_fd("mongshell: ", STDERR);
			ft_putstr_fd(cmd[token], STDERR);
			ft_putstr_fd(": command not found\n", STDERR);	
			exit(127);
		}
		else
		{
			ft_putstr_fd("mongshell: ", STDERR);
			ft_putstr_fd(cmd[token], STDERR);
			ft_putstr_fd(": ", STDERR);
			ft_putstr_fd(strerror(errno), STDERR);
			exit(1);
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
			exit(127);
		}
		else
		{
			ft_putstr_fd("mongshell: ", STDERR);
			ft_putstr_fd(cmd[token], STDERR);
			ft_putstr_fd(": ", STDERR);
			ft_putstr_fd(strerror(errno), STDERR);
			exit(1);
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
    filepath = get_filepath(token, path);
	if (prev_pipe_idx == 0)
    	exec_executable(cmd, prev_pipe_idx, pipe_idx, filepath);
	else
		exec_executable2(cmd, prev_pipe_idx, pipe_idx, filepath);
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

void update_env(char *cwd, char *key)
{
	t_list *tmp;
	char *new;

	tmp = g_env_list;
	if ((new = (char *)malloc(sizeof(char) * (ft_strlen(key) + ft_strlen(cwd)) + 1)) == NULL)
		exit(-1);
	ft_strlcpy(new, key, ft_strlen(key) + 1);
	ft_strlcat(new, cwd, ft_strlen(key) + ft_strlen(cwd) + 1);
	while (tmp)
	{
		if (!ft_strncmp(key, (char *)tmp->content, ft_strlen(key)))
		{
			free((char *)tmp->content);
			tmp->content = new;
		}
		tmp = tmp->next;
	}
}

void change_dir(char *cmd[], char *dir, int is_pipe)
{
	struct stat file;
	char buf[100];
	char *cwd;
 
	cwd = getcwd(buf, sizeof(buf));
	if (!stat(dir, &file))
	{
		if (!is_pipe)
		{
			if (!chdir(dir))
			{
				update_env(cwd, OLDPWD);
				cwd = getcwd(buf, sizeof(buf));
				update_env(cwd, PWD2);
				/* showing result (must be deleted) */
				ft_putstr_fd(cwd, 2);
				ft_putstr_fd("\n", 2);
				g_exit_status = 0;
			}
			else
			{
				ft_putstr_fd("mongshell: cd: ", 2);
				ft_putstr_fd(dir, 2);
				ft_putstr_fd(": Not a directory\n", 2);
				g_exit_status = 1;
			}
		}
	}
	else
	{
		ft_putstr_fd("mongshell: cd: ", 2);
		ft_putstr_fd(dir, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_exit_status = 1;
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
		g_exit_status = 1;
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
	// if (argc > 2)
	// {
	// 	if (prev_pipe_idx == 0)
	// 	{
	// 		ft_putstr_fd("mongshell: ", 2);
	// 		ft_putstr_fd(cmd[prev_pipe_idx], 2);
	// 		ft_putstr_fd(": too many arguments\n", 2);
	// 	}
	// 	else
	// 	{
	// 		ft_putstr_fd("mongshell: ", 2);
	// 		ft_putstr_fd(cmd[prev_pipe_idx + 1], 2);
	// 		ft_putstr_fd(": too many arguments\n", 2);
	// 	}
	// }
	/*else */if (argc == 1)
	{
		dir_to_HOME(cmd, is_pipe);
	}
	else
	{
		change_dir(cmd, dir, is_pipe);
	}
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
	process_redirection(cmd, prev_pipe_idx, pipe_idx, FALSE);
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
	exit(0);
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
	exit(0);
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
			if (new[i])
			{
				while (new[i])
				{
					new[i] = line[i - 1];
					i++;
				}
				new[i] = line[i - 1];
				i++;
			}
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
		exit(-1);
	ft_strlcpy(new, line, ft_strlen(line) + 1);
	add_dquote(new, line);
	ft_putstr_fd("declare -x ", STDOUT);
	ft_putstr_fd(new, STDOUT);
	ft_putstr_fd("\n", STDOUT);
	g_exit_status = 0;
}

void exec_export_p(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
	t_list *export_tmp;
	int argc;

	argc = get_argc(cmd, prev_pipe_idx, pipe_idx);
	if (argc == 1)
	{
		export_tmp = g_env_list;
		sort_export(&export_tmp);
		while (export_tmp)
		{
			print_export((char *)export_tmp->content);
			export_tmp = export_tmp->next;
		}
	}
	exit(0);
}

void print_echo(char *cmd[], int start, int end)
{
	int option;

	option = FALSE;
	if (!cmd[start])
		ft_putstr_fd("\n", STDOUT);
	if (!ft_strncmp(cmd[start], N_OPTION, ft_strlen(cmd[start]) > ft_strlen(N_OPTION) ? ft_strlen(cmd[start]) : ft_strlen(N_OPTION)))
	{
		start++;
		option = TRUE;
	}
	while (start < end)
	{
		if (is_redirection(cmd[start]))
		{
			start += 2;
			continue ;
		}
		if (ft_strncmp(cmd[start], "|", ft_strlen(cmd[start])))
		{
			ft_putstr_fd(cmd[start], STDOUT);
			ft_putstr_fd(" ", STDOUT);
		}
		start++;
	}
	if (!option)
		ft_putstr_fd("\n", STDOUT);
}

int get_len(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
    int len;
	int start;

    len = 0;
	if (prev_pipe_idx == 0)
		start = 0;
	else
		start = 1;		
    while (start++ < pipe_idx)
        len++;
    return (len);
}

void exec_echo(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
	int argc;
	int i;
	int size;

	argc = get_len(cmd, prev_pipe_idx, pipe_idx);
	if (prev_pipe_idx == 0)
	{
		i = prev_pipe_idx + 1;
		size = argc;
	}
	else
	{
		i = prev_pipe_idx + 2;
		size = argc + prev_pipe_idx + 1;
	}
	print_echo(cmd, i, size);
	exit(0);
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
	if (!ft_strncmp(PWD, token, ft_strlen(token) > ft_strlen(PWD) ? ft_strlen(token) : ft_strlen(PWD)))
		exec_pwd(cmd, i, pipe_idx);
	else if (!ft_strncmp(ENV, token, ft_strlen(token) > ft_strlen(ENV) ? ft_strlen(token) : ft_strlen(ENV)))
		exec_env(cmd, i, pipe_idx);
	else if (!ft_strncmp(EXPORT, token, ft_strlen(token) > ft_strlen(EXPORT) ? ft_strlen(token) : ft_strlen(EXPORT)))
		exec_export_p(cmd, i, pipe_idx);
	else if (!ft_strncmp(ECHO, token, ft_strlen(token) > ft_strlen(ECHO) ? ft_strlen(token) : ft_strlen(ECHO)))
		exec_echo(cmd, i, pipe_idx);
	else if (is_redirection(token))
		;
	else
		handle_executable(token, cmd, i, pipe_idx);
}

void exec_cmd_p(char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
	int status;

	g_pid = fork();
    if (g_pid == 0)
    {
        set_pipe_child();
        process_redirection(cmd, prev_pipe_idx, pipe_idx, TRUE);
        parse_cmd(cmd, prev_pipe_idx, pipe_idx);
        // exit(1);
    }
    else if (g_pid < 0)
    {
        perror("fork err");
    }
    else
    {
        wait(&status);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			printf("signal!!! %d\n", WTERMSIG(status));
        set_pipe_parent();
    }
}

char *get_key(char *content)
{
	int key_len;
	char *ret;

	key_len = 0;
	ret = NULL;
	while (content[key_len] != '=')
		key_len++;
	if ((ret = (char *)malloc(sizeof(char) * key_len + 2)) == NULL)
		exit(-1);
	ft_strlcpy(ret, content, key_len + 2);
	return (ret);
}

int check_update(char *content)
{
	char *key;
	t_list *tmp;

	tmp = g_env_list;
	key = get_key(content);
	while (tmp)
	{
		if (!ft_strncmp(key, (char *)tmp->content, ft_strlen(key)))
		{
			if (tmp->content)
				free(tmp->content);
			
			tmp->content = ft_strdup(content);
			return (TRUE);
		}
		tmp = tmp->next;
	}
	free(key);
	return (FALSE);
}

void exec_export_np(char *cmd[], int prev_pipe_idx, int pipe_idx, int argc)
{
	int i;
	t_list *new;
	char *new_content;
	int size;

	i = prev_pipe_idx;
	if (i == 0)
		size = argc + i;
	else
		size = argc + i + 1;
	if (!find_pipe(cmd))
	{
		while (prev_pipe_idx < size)
		{
			new_content = NULL;
			new = NULL;
			if (ft_strrchr(cmd[prev_pipe_idx], '='))
			{
				if (!check_update(cmd[prev_pipe_idx]))
				{
					new_content = ft_strdup(cmd[prev_pipe_idx]);
					new = ft_lstnew(new_content);
					ft_lstadd_back(&g_env_list, new);
				}
			}
			prev_pipe_idx++;
		}
	}
}

void delete_env_node(char *token)
{
	t_list *tmp;
	t_list *prev;

	tmp = g_env_list;
	prev = tmp;
	while (tmp)
	{
		if (!ft_strncmp(token, (char *)tmp->content, ft_strlen(token)))
		{
			if (((char *)tmp->content)[ft_strlen(token)] == '=')
			{
				prev->next = tmp->next;
				ft_lstdelone(tmp, free);
			}
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void exec_unset(char *cmd[], int prev_pipe_idx, int pipe_idx, int argc)
{
	int i;
	int size;

	i = prev_pipe_idx;
	if (!find_pipe(cmd))
	{
		if (i == 0)
			size = argc + i;
		else
			size = argc + i + 1;
		while (prev_pipe_idx < size)
		{
			delete_env_node(cmd[prev_pipe_idx]);
			prev_pipe_idx++;
		}
	}
}

void handle_cmd(char *token, char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
	if (!ft_strncmp(token, CD, ft_strlen(token) > ft_strlen(CD) ? ft_strlen(token) : ft_strlen(CD)))
		exec_nprocess_built_in(exec_cd, cmd, prev_pipe_idx, pipe_idx);
	else if (!ft_strncmp(token, UNSET, ft_strlen(token) > ft_strlen(UNSET) ? ft_strlen(token) : ft_strlen(UNSET)))
		exec_nprocess_built_in(exec_unset, cmd, prev_pipe_idx, pipe_idx);
	else
		exec_cmd_p(cmd, prev_pipe_idx, pipe_idx);
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
		handle_cmd(token, cmd, prev_pipe_idx, pipe_idx);
        *prev_pipe_idx = pipe_idx;
    }
}

void exec_last_cmd(char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
	int status;

	g_pid = fork();
	if (g_pid == 0)
	{
		process_redirection(cmd, prev_pipe_idx, pipe_idx, TRUE);
		parse_cmd(cmd, prev_pipe_idx, pipe_idx);
		// exit(1);
	}
	else if (g_pid < 0)
    {
        perror("fork err");
    }
	else
	{
		wait(&status);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
		{
			printf("signal!!! %d\n", WTERMSIG(status));
		}
	}
}

void handle_last_cmd(char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
	char *token;
	int i;
	int argc;

	i = *prev_pipe_idx;
	argc = get_argc(cmd, i, pipe_idx);
	if (i == 0)
		token = cmd[i];
	else
		token = cmd[i + 1];
	if (!ft_strncmp(token, CD, ft_strlen(token) > ft_strlen(CD) ? ft_strlen(token) : ft_strlen(CD)))
		exec_nprocess_built_in(exec_cd, cmd, prev_pipe_idx, pipe_idx);
	else if (!ft_strncmp(token, EXPORT, ft_strlen(token) > ft_strlen(EXPORT) ? ft_strlen(token) : ft_strlen(EXPORT)) && argc > 1)
		exec_nprocess_built_in(exec_export_np, cmd, prev_pipe_idx, pipe_idx);
	else if (!ft_strncmp(token, UNSET, ft_strlen(token) > ft_strlen(UNSET) ? ft_strlen(token) : ft_strlen(UNSET)))
		exec_nprocess_built_in(exec_unset, cmd, prev_pipe_idx, pipe_idx);
	else
		exec_last_cmd(cmd, prev_pipe_idx, pipe_idx);
}

void copy_environ(void)
{
	int i;
	t_list *tmp;

	g_env_head.content = ft_strdup(environ[0]);
	g_env_head.next = NULL;
	g_env_list = &g_env_head;
	i = 1;
	while (environ[i])
	{
		tmp = ft_lstnew(ft_strdup(environ[i]));
		ft_lstadd_back(&g_env_list, tmp);
		i++;
	}
}

void handle_process(char **cmd)
{
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

void free_env(void)
{
	while (g_env_list)
	{
		free(g_env_list->content);
		g_env_list = g_env_list->next;
	}
	ft_lstclear(&g_env_list, free);
}

void sig_int(int signo)
{
	(void)signo;
	if (g_pid == 0)
	{
		ft_putstr_fd("\b\b  \b\b", STDERR);
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd("\033[0;32mmongshell\033[0;34m$ \033[0m", STDERR);
		// g_exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		// g_exit_status = 130;
	}
}

void sig_quit(int signo)
{
	(void)signo;
	if (g_pid == 0)
		ft_putstr_fd("\b\b  \b\b", STDERR);
	else
	{
		ft_putstr_fd("Quit: 3\n", STDERR);
		ft_putstr_fd("\033[0;32mmongshell\033[0;34m$ \033[0m", STDERR);
		// g_exit_status = 131;
	}
}

void free_cmds(char ***cmds)
{
	int i;
	int j;

	i = 0;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i][j])
		{
			free(cmds[i][j]);
			j++;
		}
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

void make_new_cmd(char *new, char *cmd)
{
	int i;
	int j;
	int k;
	char *exit_status;

	i = 0;
	j = 0;
	exit_status = ft_itoa(g_exit_status);
	while (cmd[i])
	{
		k = 0;
		if (cmd[i] == '$' && cmd[i + 1] && cmd[i + 1] == '?')
		{
			while (exit_status[k])
				new[j++] = exit_status[k++];
			i += 2;
			continue ;
		}
		new[j] = cmd[i];
		j++;
		i++;
	}
	free(exit_status);
}

int get_num_exit_status(char *cmd)
{
	int i;
	int cnt;

	i = 0;
	cnt = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$' && cmd[i + 1] && cmd[i + 1] == '?')
		{
			cnt++;
			i++;
		}
		i++;
	}
	return (cnt);
}

char *alloc_new(char *cmd)
{
	int cmd_len;
	int exit_cnt;
	char *exit_status;
	char *ret;

	ret = NULL;
	exit_cnt = get_num_exit_status(cmd);
	cmd_len = ft_strlen(cmd);
	exit_status = ft_itoa(g_exit_status);
	if ((ret = (char *)malloc(sizeof(char) * (cmd_len - (2 * exit_cnt) + (ft_strlen(exit_status) * exit_cnt)) + 1)) == NULL)
		exit(-1);
	ret[cmd_len - (2 * exit_cnt) + (ft_strlen(exit_status) * exit_cnt)] = 0;
	free(exit_status);
	return (ret);
}

void convert_exit_status(t_token *token)
{
	char *new;
	t_token *tmp;

	tmp = token;
	while (tmp)
	{
		if (ft_strnstr(tmp->data, "$?", ft_strlen(tmp->data)))
		{
			if (tmp->type != CHAR_QUOTE)
			{
				new = alloc_new(tmp->data);
				make_new_cmd(new, tmp->data);
				free(tmp->data);
				tmp->data = new;
			}
		}
		tmp = tmp->next;
	}
}

int				main(int argc, char const *argv[])
{
	t_token		*token;
	char		buf[BUF_SIZE];
	char 		***cmds;

	signal(SIGQUIT, sig_quit);
	signal(SIGINT, sig_int);
	copy_environ();
	while (TRUE)
	{
		g_pid = 0;
		handle_prompt(buf);
		token = tokenize_lexer(buf, ft_strlen(buf));
		if (!remove_empty_token(token))
		{
			free_all_tokens(token, free);
			continue ;
		}
		if (check_basic_grammar(token))
		{
			adjust_env(token);
			check_dred_out(token);
			erase_quote(token, CHAR_DQUOTE);
			erase_quote(token, CHAR_QUOTE);
			adjust_env_in_dquote(token);
			convert_exit_status(token);
			cmds = divide_semicolon(token);
			start_bash(cmds);
			free_cmds(cmds);
		}
		free_all_tokens(token, free);
	}
	free_env();
	return (EXIT_SUCCESS);
}