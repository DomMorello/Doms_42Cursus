/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_converter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:22:37 by donglee           #+#    #+#             */
/*   Updated: 2020/12/24 18:22:41 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void			handle_empty_environ(t_token *token)
{
	if (!ft_strncmp(token->data, "$?", 2))
		return ;
	else
	{
		free(token->data);
		token->data = ft_strdup("");
		token->type = TOKEN;
	}
}

static void			replace_key_with_value(t_token *token, int flag)
{
	char	*key;
	int		j;
	t_list	*env_tmp;

	env_tmp = g_env_list;
	key = token->data + sizeof(char);
	while (env_tmp)
	{
		j = 0;
		while (((char *)(env_tmp->content))[j] != '=')
			j++;
		if (!ft_strncmp((char *)(env_tmp->content), key, j >
			ft_strlen(token->data + 1) ? j : ft_strlen(token->data + 1)))
		{
			free(token->data);
			token->data = ft_strdup((char *)(env_tmp->content) + j + 1);
			token->type = TOKEN;
			flag = TRUE;
			return ;
		}
		env_tmp = env_tmp->next;
	}
	if (!flag)
		handle_empty_environ(token);
}

void				replace_exception_env(t_token *token)
{
	t_token *tmp;

	tmp = token;
	copy_env_key(&(tmp->data));
}

int					is_one_env(t_token *token)
{
	int i;
	int num_env;

	i = 0;
	num_env = 0;
	if (token->data[i] != CHAR_ENV)
		return (FALSE);
	while (token->data[i])
	{
		if (num_env > 1)
			return (FALSE);
		if (token->data[i] == CHAR_ENV)
			num_env++;
		i++;
	}
	return (TRUE);
}

void				adjust_env(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp != NULL)
	{
		if (tmp->type == CHAR_ENV)
		{
			if (is_one_env(tmp))
				replace_key_with_value(tmp, FALSE);
			else
				replace_exception_env(tmp);
		}
		tmp = tmp->next;
	}
}
