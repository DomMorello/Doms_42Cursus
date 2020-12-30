/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_err.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:33:17 by donglee           #+#    #+#             */
/*   Updated: 2020/12/30 13:30:51 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
**	prints not a directory err message.
*/

void	print_err_not_dir(char *dir)
{
	ft_putstr_fd("mongshell: cd: ", STDERR);
	ft_putstr_fd(dir, STDERR);
	ft_putstr_fd(": Not a directory\n", STDERR);
	g_exit_status = 1;
}

/*
**	prints no such file err messages.
*/

void	print_err_no_dir(char *dir)
{
	ft_putstr_fd("mongshell: cd: ", STDERR);
	ft_putstr_fd(dir, STDERR);
	ft_putstr_fd(": No such file or directory\n", STDERR);
	g_exit_status = 1;
}

/*
**	prints err messages when it fails to execute executable commands like ls.
*/

void	print_exec_error(int errnum, char *token)
{
	if (errnum == ENOENT)
	{
		ft_putstr_fd("mongshell: ", STDERR);
		ft_putstr_fd(token, STDERR);
		ft_putstr_fd(": command not found\n", STDERR);
		exit(127);
	}
	else
	{
		ft_putstr_fd("mongshell: ", STDERR);
		ft_putstr_fd(token, STDERR);
		ft_putstr_fd(": ", STDERR);
		ft_putstr_fd(strerror(errno), STDERR);
		exit(1);
	}
}

/*
**	prints no such file err message in redirection input.
*/

void	print_error_red_in(char *title, int is_process)
{
	ft_putstr_fd("momgshell: ", STDERR);
	ft_putstr_fd(title, STDERR);
	ft_putstr_fd(": No such file or directory\n", STDERR);
	g_exit_status = 1;
	if (is_process)
		exit(1);
}
