/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:32:07 by donglee           #+#    #+#             */
/*   Updated: 2020/12/28 15:09:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	numeric_exception(char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			ft_putstr_fd("mongshell: exit: ", STDERR);
			ft_putstr_fd(arg, STDERR);
			ft_putstr_fd(": numeric argument required\n", STDERR);
			exit(255);
		}
		i++;
	}
}

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
		{
			numeric_exception(cmd[prev_pipe_idx + 1]);
			exit(ft_atoi(cmd[prev_pipe_idx + 1]));
		}
		else
			exit(g_exit_status);
	}
	else
	{
		if (argc > 1)
			g_exit_status = ft_atoi(cmd[prev_pipe_idx + 2]);
	}
}
