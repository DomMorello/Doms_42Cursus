/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 13:43:29 by donglee           #+#    #+#             */
/*   Updated: 2020/12/30 13:43:30 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
**	When user inputs "unset XX", deletes environment variables of which
**	key value is XX in the linked list(g_env_list).
*/

void	delete_env_node(char *token)
{
	t_list *tmp;
	t_list *prev;

	tmp = g_env_list;
	prev = tmp;
	while (tmp)
	{
		if (!ft_strncmp(token, (char *)tmp->content, ft_strlen(token)))
		{
			if (((char *)tmp->content)[ft_strlen(token)] == '=')
			{
				prev->next = tmp->next;
				ft_lstdelone(tmp, free);
			}
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

/*
**	handles unset. But if tokens have pipe, it doesn't work.
*/

void	exec_unset(char *cmd[], int prev_pipe_idx, int pipe_idx, int argc)
{
	int i;
	int size;

	(void)pipe_idx;
	i = prev_pipe_idx;
	if (!find_pipe(cmd))
	{
		if (i == 0)
			size = argc + i;
		else
			size = argc + i + 1;
		while (prev_pipe_idx < size)
		{
			delete_env_node(cmd[prev_pipe_idx]);
			prev_pipe_idx++;
		}
	}
}
