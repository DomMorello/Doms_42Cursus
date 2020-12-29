/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:05:46 by donglee           #+#    #+#             */
/*   Updated: 2020/12/29 14:49:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
**	executes pwd command; simply shows current directory. 
*/

void	exec_pwd(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
	char *cwd;

	(void)cmd;
	(void)prev_pipe_idx;
	(void)pipe_idx;
	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, STDOUT);
	ft_putstr_fd("\n", STDOUT);
	free(cwd);
	exit(0);
}
