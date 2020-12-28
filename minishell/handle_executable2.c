/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_executable2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:32:20 by donglee           #+#    #+#             */
/*   Updated: 2020/12/28 14:06:06 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

int		get_argc(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
	int len;

	len = 0;
	if (prev_pipe_idx == 0)
		while (prev_pipe_idx < pipe_idx &&
			!is_redirection(cmd[prev_pipe_idx++]))
			len++;
	else
		while (++prev_pipe_idx < pipe_idx &&
			!is_redirection(cmd[prev_pipe_idx]))
			len++;
	return (len);
}

void	exec_executable(char *cmd[], int prev_pipe_idx,
	int pipe_idx, char *filepath)
{
	char	**argv;
	int		argc;
	int		i;
	int		token;

	i = 0;
	token = prev_pipe_idx;
	argv = NULL;
	argc = get_argc(cmd, prev_pipe_idx, pipe_idx);
	if (!(argv = (char **)malloc(sizeof(char *) * argc + 1)))
		exit(-1);
	while (prev_pipe_idx < pipe_idx && !is_redirection(cmd[prev_pipe_idx]))
		argv[i++] = cmd[prev_pipe_idx++];
	argv[i] = NULL;
	if (execve(filepath, argv, environ) == -1)
	{
		i = errno;
		print_exec_error(i, cmd[token]);
	}
}

void	exec_executable2(char *cmd[], int prev_pipe_idx,
	int pipe_idx, char *filepath)
{
	char	**argv;
	int		argc;
	int		i;
	int		token;

	token = prev_pipe_idx + 1;
	i = 0;
	argv = NULL;
	argc = get_argc(cmd, prev_pipe_idx, pipe_idx);
	if (!(argv = (char **)malloc(sizeof(char *) * argc + 1)))
		exit(-1);
	while (++prev_pipe_idx < pipe_idx && !is_redirection(cmd[prev_pipe_idx]))
		argv[i++] = cmd[prev_pipe_idx];
	argv[i] = NULL;
	if (execve(filepath, argv, environ) == -1)
	{
		i = errno;
		print_exec_error(i, cmd[token]);
	}
}

void	free_2d_char(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}
