/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 13:42:09 by donglee           #+#    #+#             */
/*   Updated: 2020/12/30 13:42:10 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
**	When argument is not numeric value, prints error message
**	and change exit status to 255 and exit the program.
*/

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

/*
**	Executes exit commands with or without arguments.
**	If there are more than two arguments, prints error message and returns.
**	If exit command comes after pipe, does not exit program but stores
**	exit status(numeric argument).
**	When argument is not numeric value, handle exception.
*/

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
