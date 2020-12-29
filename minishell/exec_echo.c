/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:07:58 by donglee           #+#    #+#             */
/*   Updated: 2020/12/29 15:41:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
**	Prints arguments on stdout fd.
**	if there are redirection characters, does not print them.
**	Printing keep going on until it finds pipe.
*/

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

/*
**	Prints echo. If the token is just "echo" without argument,
**	simply prints "\n".
**	If there is "-n" right after "echo" option is TRUE
**	that does not print "\n" at the end of arguments.
*/

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

/*
**	Gets length of arguments which are to be printed.
*/

int		get_len(int prev_pipe_idx, int pipe_idx)
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

/*
**	Executes echo command.
**	If the command comes before first pipe, prev_pipe_idx == 0.
**	Otherwise, prev_pipe_idx != 0. This is because the indexes(i, size) are
**	diffrent depending on the location of the command.
*/

void	exec_echo(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
	int argc;
	int i;
	int size;

	argc = get_len(prev_pipe_idx, pipe_idx);
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
