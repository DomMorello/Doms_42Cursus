/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_env_in_dquote.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:08:50 by donglee           #+#    #+#             */
/*   Updated: 2020/12/29 17:21:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Converts key to value. 
*/

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

/*
**	Allocates exact size of new token(new).
**	Puts new string(converted to the value) to token and free old one. 
*/

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

/*
**	Searches the key in the environment variables.
**	If there is exact same key, converts it to the value.
*/

void	search_key_in_env(char *key, char **token_data, int env_idx)
{
	t_list	*env_tmp;
	size_t	env_key_len;

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

/*
**	Allocates env string as much as token length(maximum).
**	Stores key to string env.
**	Ex) "hello$user hi" -> env == "user".
*/

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

/*
**	After conversion of environment variable in other functions.
**	Still cannot convert environment vairable in double quotatation marks.
**	So, this func handles environment variables in double quote state. 
*/

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
