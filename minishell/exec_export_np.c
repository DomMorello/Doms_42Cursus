/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export_np.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:32:50 by donglee           #+#    #+#             */
/*   Updated: 2020/12/24 18:02:18 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

char	*get_key(char *content)
{
	int		key_len;
	char	*ret;

	key_len = 0;
	ret = NULL;
	while (content[key_len] != '=')
		key_len++;
	if ((ret = (char *)malloc(sizeof(char) * key_len + 2)) == NULL)
		exit(-1);
	ft_strlcpy(ret, content, key_len + 2);
	return (ret);
}

int		check_update(char *content)
{
	char	*key;
	t_list	*tmp;

	tmp = g_env_list;
	key = get_key(content);
	while (tmp)
	{
		if (!ft_strncmp(key, (char *)tmp->content, ft_strlen(key)))
		{
			if (tmp->content)
				free(tmp->content);
			tmp->content = ft_strdup(content);
			return (TRUE);
		}
		tmp = tmp->next;
	}
	free(key);
	return (FALSE);
}

void	do_export(char *token, int prev_pipe_idx)
{
	char	*new_content;
	t_list	*new;

	if (ft_strrchr(token, '='))
	{
		if (!check_update(token))
		{
			new_content = ft_strdup(token);
			new = ft_lstnew(new_content);
			ft_lstadd_back(&g_env_list, new);
		}
	}
}

void	exec_export_np(char *cmd[], int prev_pipe_idx, int pipe_idx, int argc)
{
	int i;
	int size;

	i = prev_pipe_idx;
	if (i == 0)
		size = argc + i;
	else
		size = argc + i + 1;
	if (!find_pipe(cmd))
	{
		while (prev_pipe_idx < size)
		{
			do_export(cmd[prev_pipe_idx], prev_pipe_idx);
			prev_pipe_idx++;
		}
	}
}
