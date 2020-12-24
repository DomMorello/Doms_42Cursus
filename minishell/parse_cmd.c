#include "./minishell.h"

void exec_nprocess_built_in(void (*exec_func)(char **, int, int, int),
	char **cmd, int *prev_pipe_idx, int pipe_idx)
{
	int argc;
	int prev_pipe;

	prev_pipe = *prev_pipe_idx;
    argc = get_argc(cmd, prev_pipe, pipe_idx);
	process_redirection(cmd, prev_pipe_idx, pipe_idx, FALSE);
	exec_func(cmd, prev_pipe, pipe_idx, argc);
}

void parse_cmd(char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
    int		i;
	char	*token;

    i = *prev_pipe_idx;
	if (i == 0)
		token = cmd[i];
	else
		token = cmd[i + 1];
	if (!ft_strncmp(PWD, token, ft_strlen(token) > ft_strlen(PWD) ?
		ft_strlen(token) : ft_strlen(PWD)))
		exec_pwd(cmd, i, pipe_idx);
	else if (!ft_strncmp(ENV, token, ft_strlen(token) > ft_strlen(ENV) ?
		ft_strlen(token) : ft_strlen(ENV)))
		exec_env(cmd, i, pipe_idx);
	else if (!ft_strncmp(EXPORT, token, ft_strlen(token) > ft_strlen(EXPORT) ?
		ft_strlen(token) : ft_strlen(EXPORT)))
		exec_export_p(cmd, i, pipe_idx);
	else if (!ft_strncmp(ECHO, token, ft_strlen(token) > ft_strlen(ECHO) ?
		ft_strlen(token) : ft_strlen(ECHO)))
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
    }
    else if (g_pid < 0)
		exit(-1);
    else
    {
        wait(&status);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_exit_status = WTERMSIG(status) + 128;
        set_pipe_parent();
    }
}

void copy_environ(void)
{
	int		i;
	t_list	*tmp;

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