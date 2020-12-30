/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export_np.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 13:43:15 by donglee           #+#    #+#             */
/*   Updated: 2020/12/30 13:43:17 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
**	Simply gets key part like "dom" in "dom=morello".
*/

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

/*
**	If the key already exists in the environment variables,
**	update its value to new one.
*/

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
			free(key);
			key = NULL;
			if (tmp->content)
				free(tmp->content);
			tmp->content = ft_strdup(content);
			return (TRUE);
		}
		tmp = tmp->next;
	}
	if (key)
		free(key);
	return (FALSE);
}

/*
**	In arguments, only if there is a '=' character it works.
**	Makes new node and add one at the end of the list.
*/

void	do_export(char *token)
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

/*
**	Executes export with arguments not in child process.
**	If there is a pipe in the tokens, doesn't work.
*/

void	exec_export_np(char *cmd[], int prev_pipe_idx, int pipe_idx, int argc)
{
	int i;
	int size;

	(void)pipe_idx;
	i = prev_pipe_idx;
	if (i == 0)
		size = argc + i;
	else
		size = argc + i + 1;
	if (!find_pipe(cmd))
	{
		while (prev_pipe_idx < size)
		{
			do_export(cmd[prev_pipe_idx]);
			prev_pipe_idx++;
		}
	}
}
