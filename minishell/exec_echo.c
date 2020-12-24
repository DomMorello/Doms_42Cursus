/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:32:39 by donglee           #+#    #+#             */
/*   Updated: 2020/12/24 18:01:08 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	do_echo(int start, int end, char *cmd[])
{
	while (cmd[start] && start < end)
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
}

void	print_echo(char *cmd[], int start, int end, int option)
{
	if (!cmd[start])
	{
		ft_putstr_fd("\n", STDOUT);
		exit(0);
	}
	if (!ft_strncmp(cmd[start], N_OPTION, ft_strlen(cmd[start])
		> ft_strlen(N_OPTION) ? ft_strlen(cmd[start]) : ft_strlen(N_OPTION)))
	{
		option = TRUE;
		start++;
	}
	do_echo(start, end, cmd);
	if (!option)
		ft_putstr_fd("\n", STDOUT);
}

int		get_len(char *cmd[], int prev_pipe_idx, int pipe_idx)
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

void	exec_echo(char *cmd[], int prev_pipe_idx, int pipe_idx)
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
	print_echo(cmd, i, size, FALSE);
	exit(0);
}
