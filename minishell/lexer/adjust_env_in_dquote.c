/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_env_in_dquote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:17:49 by donglee           #+#    #+#             */
/*   Updated: 2020/12/24 18:18:22 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	convert_to_value(char *new, char *env_content, int *i, int *j)
{
	int env_key_len;

	env_key_len = 0;
	(*i)++;
	while (env_content[env_key_len] != '=')
		env_key_len++;
	env_key_len++;
	while (env_content[env_key_len])
		new[(*j)++] = env_content[env_key_len++];
}

void	convert_key_to_env(char *env_content, char **token_data,
	char *key, int env_idx)
{
	int		env_key_len;
	char	*new;
	int		i;
	int		j;

	env_key_len = 0;
	i = 0;
	j = 0;
	while (env_content[env_key_len] != '=')
		env_key_len++;
	if ((new = (char *)malloc(sizeof(char) * ft_strlen(*token_data) +
		ft_strlen(&env_content[env_key_len + 1]) - ft_strlen(key) + 1)) == NULL)
		exit(-1);
	while ((*token_data)[i])
	{
		if ((*token_data)[i] == CHAR_ENV && i == env_idx)
		{
			convert_to_value(new, env_content, &i, &j);
			i += ft_strlen(key);
		}
		new[j++] = (*token_data)[i++];
	}
	new[j] = 0;
	free(*token_data);
	*token_data = new;
}

void	search_key_in_env(char *key, char **token_data, int env_idx)
{
	t_list	*env_tmp;
	int		env_key_len;

	env_tmp = g_env_list;
	while (env_tmp)
	{
		env_key_len = 0;
		while (((char *)(env_tmp->content))[env_key_len] != '=')
			env_key_len++;
		if (!ft_strncmp((char *)env_tmp->content, key, env_key_len >
			ft_strlen(key) ? env_key_len : ft_strlen(key)))
			convert_key_to_env((char *)env_tmp->content,
				token_data, key, env_idx);
		env_tmp = env_tmp->next;
	}
}

void	copy_env_key(char **tokens)
{
	char	*env;
	int		i;
	int		j;
	int		env_idx;

	i = 0;
	env_idx = 0;
	while ((*tokens)[i])
	{
		j = 0;
		if ((*tokens)[i] == CHAR_ENV)
		{
			env_idx = i;
			if (!(env = (char *)malloc(sizeof(char) * ft_strlen(*tokens) + 1)))
				exit(-1);
			i++;
			while ((*tokens)[i] && (*tokens)[i] != ' '
				&& (*tokens)[i] != CHAR_ENV)
				env[j++] = (*tokens)[i++];
			env[j] = 0;
			search_key_in_env(env, tokens, env_idx);
			free(env);
		}
		i++;
	}
}

void	adjust_env_in_dquote(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == CHAR_DQUOTE)
			copy_env_key(&(tmp->data));
		tmp = tmp->next;
	}
}
