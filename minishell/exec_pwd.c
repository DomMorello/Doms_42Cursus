/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:32:14 by donglee           #+#    #+#             */
/*   Updated: 2020/12/24 17:48:57 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	exec_pwd(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, STDOUT);
	ft_putstr_fd("\n", STDOUT);
	free(cwd);
	exit(0);
}
