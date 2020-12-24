#include "./minishell.h"

void handle_cmd(char *token, char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
	if (!ft_strncmp(token, CD, ft_strlen(token) > ft_strlen(CD) ?
		ft_strlen(token) : ft_strlen(CD)))
		exec_nprocess_built_in(exec_cd, cmd, prev_pipe_idx, pipe_idx);
	else if (!ft_strncmp(token, UNSET, ft_strlen(token) > ft_strlen(UNSET) ?
		ft_strlen(token) : ft_strlen(UNSET)))
		exec_nprocess_built_in(exec_unset, cmd, prev_pipe_idx, pipe_idx);
	else if (!ft_strncmp(token, EXIT, ft_strlen(token) > ft_strlen(EXIT) ?
		ft_strlen(token) : ft_strlen(EXIT)))
		exec_nprocess_built_in(exec_exit, cmd, prev_pipe_idx, pipe_idx);
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
    if (ft_strncmp(cmd[pipe_idx], "", ft_strlen(cmd[pipe_idx]))
		&& !ft_strncmp(cmd[pipe_idx], "|", ft_strlen(cmd[pipe_idx])))
    {
        pipe(g_pipe_fd);
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
	}
}

void handle_last_cmd(char *cmd[], int *prev_pipe_idx, int pipe_idx)
{
	char	*token;
	int		i;
	int		argc;

	i = *prev_pipe_idx;
	argc = get_argc(cmd, i, pipe_idx);
	if (i == 0)
		token = cmd[i];
	else
		token = cmd[i + 1];
	if (!ft_strncmp(token, CD, ft_strlen(token) > ft_strlen(CD) ?
		ft_strlen(token) : ft_strlen(CD)))
		exec_nprocess_built_in(exec_cd, cmd, prev_pipe_idx, pipe_idx);
	else if (!ft_strncmp(token, EXPORT, ft_strlen(token) > ft_strlen(EXPORT) ?
		ft_strlen(token) : ft_strlen(EXPORT)) && argc > 1)
		exec_nprocess_built_in(exec_export_np, cmd, prev_pipe_idx, pipe_idx);
	else if (!ft_strncmp(token, UNSET, ft_strlen(token) > ft_strlen(UNSET) ?
		ft_strlen(token) : ft_strlen(UNSET)))
		exec_nprocess_built_in(exec_unset, cmd, prev_pipe_idx, pipe_idx);
	else if (!ft_strncmp(token, EXIT, ft_strlen(token) > ft_strlen(EXIT) ?
		ft_strlen(token) : ft_strlen(EXIT)))
		exec_nprocess_built_in(exec_exit, cmd, prev_pipe_idx, pipe_idx);
	else
		exec_last_cmd(cmd, prev_pipe_idx, pipe_idx);
}

void handle_process(char **cmd)
{
	int i;
	int prev_pipe_idx;
	int stdin_tmp;
	int stdout_tmp;

	if (!ft_strncmp(cmd[0], "", ft_strlen(cmd[0])))
	{
		g_exit_status = 0;
		return ;
	}
	stdin_tmp = dup(0);
	stdout_tmp = dup(1);
	prev_pipe_idx = 0;
	i = 0;
	while (cmd[i])
	{
		process_pipe(cmd, &prev_pipe_idx, i);
		i++;
		if (!cmd[i])
			handle_last_cmd(cmd, &prev_pipe_idx, i);
	}
	dup2(stdin_tmp, 0);
	dup2(stdout_tmp, 1);
}