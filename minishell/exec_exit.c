/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:32:07 by donglee           #+#    #+#             */
/*   Updated: 2020/12/25 17:55:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	exec_exit(char *cmd[], int prev_pipe_idx, int pipe_idx, int argc)
{
	(void)pipe_idx;
	if (argc > 2)
	{
		ft_putstr_fd("mongshell: exit: too many arguments\n", STDERR);
		g_exit_status = 1;
		return ;
	}
	if (prev_pipe_idx == 0)
	{
		if (argc > 1)
			exit(ft_atoi(cmd[prev_pipe_idx + 1]));
		else
			exit(g_exit_status);
	}
	else
	{
		if (argc > 1)
			g_exit_status = ft_atoi(cmd[prev_pipe_idx + 2]);
	}
}