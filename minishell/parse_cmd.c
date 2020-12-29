/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:06:59 by donglee           #+#    #+#             */
/*   Updated: 2020/12/28 18:03:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
**	when handles nprocess(which means not being handled in child process)
**	it sets redirection in process_redirection func, and execute
**	the command in the exec_func func. 
*/

void	exec_nprocess_built_in(void (*exec_func)(char **, int, int, int),
	char **cmd, int *prev_pipe_idx, int pipe_idx)
{
	int argc;
	int prev_pipe;

	prev_pipe = *prev_pipe_idx;
	argc = get_argc(cmd, prev_pipe, pipe_idx);
	process_redirection(cmd, prev_pipe_idx, pipe_idx, FALSE);
	exec_func(cmd, prev_pipe, pipe_idx, argc);
}

/*
**	finds out what the command is.
**	if the redirection character('>', '<', '>>') comes in this func,
**	just igonres.
*/

void	parse_cmd(char *cmd[], int *prev_pipe_idx, int pipe_idx)
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

/*
**	Between pipes, this func works.
**	sets the pipe linking the result(printed on terminal) of previous fd
**	to the later command input fd.
**	sets redirection if it is included in the commands.
**	parses what the command is in parse_cmd func.
**	if fork fails, program ends.
**	stores exit status when it is terminated normally or stopped by signal.
*/

void	exec_cmd_p(char *cmd[], int *prev_pipe_idx, int pipe_idx)
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

/*
**	In the main function, environmant variables are given through the third
**	argument. and this func copies it in g_env_list which is liked list. 
*/

void	copy_environ(char **envp)
{
	int		i;
	t_list	*tmp;

	g_env_head.content = ft_strdup(envp[0]);
	g_env_head.next = NULL;
	g_env_list = &g_env_head;
	i = 1;
	while (envp[i])
	{
		tmp = ft_lstnew(ft_strdup(envp[i]));
		ft_lstadd_back(&g_env_list, tmp);
		i++;
	}
}
