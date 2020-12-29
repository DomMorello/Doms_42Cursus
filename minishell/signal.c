/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:33:21 by donglee           #+#    #+#             */
/*   Updated: 2020/12/28 18:10:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
**	when the user inputs CTRL + C, the prompt just print \n and
**	changes exit status to 1.
*/

void	sig_int(int signo)
{
	(void)signo;
	if (g_pid == 0)
	{
		ft_putstr_fd("\b\b  \b\b", STDERR);
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd("\033[0;32mmongshell\033[0;34m$ \033[0m", STDERR);
		g_exit_status = 1;
	}
	else
		ft_putstr_fd("\n", STDERR);
}

/*
**	When user inputs CTRL + \, does nothing.
**	\b is intended for deleteing unnecessary character like \^.
**	if SIGQUIT comes in when the child process is doing something,
**	"Quit: 3\n" is printed on the terminal.
*/

void	sig_quit(int signo)
{
	(void)signo;
	if (g_pid == 0)
		ft_putstr_fd("\b\b  \b\b", STDERR);
	else
		ft_putstr_fd("Quit: 3\n", STDERR);
}
