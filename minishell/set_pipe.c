/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:32:32 by donglee           #+#    #+#             */
/*   Updated: 2020/12/30 13:29:16 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
**	sets pipe in child process.
*/

void	set_pipe_child(void)
{
	close(g_pipe_fd[0]);
	dup2(g_pipe_fd[1], 1);
	close(g_pipe_fd[1]);
}

/*
**	sets pipe in parent process.
*/

void	set_pipe_parent(void)
{
	close(g_pipe_fd[1]);
	dup2(g_pipe_fd[0], 0);
	close(g_pipe_fd[0]);
}

/*
**	returns if token is pipe character('|').
*/

int		find_pipe(char *cmd[])
{
	int i;

	i = 0;
	while (cmd[i])
	{
		if (!ft_strncmp(cmd[i], "|", ft_strlen(cmd[i])
			> 1 ? ft_strlen(cmd[i]) : 1))
			return (TRUE);
		i++;
	}
	return (FALSE);
}
