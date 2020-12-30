/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 13:43:40 by donglee           #+#    #+#             */
/*   Updated: 2020/12/30 13:43:41 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
**	If there is pipe in the tokens, parses what command is.
**	If the command is not cd, unset, exit, then execute exsec_cmd_p.
*/

void	handle_cmd(char *token, char *cmd[], int *prev_pipe_idx, int pipe_idx)
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

/*
**	when there is pipe, sets pipe and process commands in handle_cmd func.
*/

void	process_pipe(char *cmd[], int *prev_pipe_idx, int pipe_idx)
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

/*
**	after last pipe, handles last command.
**	sets redirection if it is included in the commands.
**	parses what the command is in parse_cmd func.
**	if fork fails, program ends.
**	stores exit status when it is terminated normally or stopped by signal.
*/

void	exec_last_cmd(char *cmd[], int *prev_pipe_idx, int pipe_idx)
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

/*
**	after last pipe or in case of just single command, this function works.
**	nprocess means that thoes commands are not handled in child process by fork.
**	if the token is cd, export(in case of registering environment), unset,
**	and exit, then they are handled nprocess funcs.
*/

void	handle_last_cmd(char *cmd[], int *prev_pipe_idx, int pipe_idx)
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

/*
**	when empty string comes in this function, just returns.
**	In case of redirections and pipes, stores stdout, stdin fds
**	in the stdin_tmp, stdout_tmp to restore them after processing
**	redirections and pipes.
**	when it finds pipe in cmds(tokens), the fucntion handles command
**	before the found pipe and keep go on in regular sequence.
**	In handle_last_cmd, handles last command.
**	if single commands without pipe comes in this function,
**	the commands will be handled in handle_last_cmd func.
*/

void	handle_process(char **cmd)
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
