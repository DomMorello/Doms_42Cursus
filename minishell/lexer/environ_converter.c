/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_converter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 13:45:36 by donglee           #+#    #+#             */
/*   Updated: 2020/12/30 13:45:37 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	If "$?" comes, just returns. This one will be handled other functions.
**	If there is no key in the environment variabales,
**	just converts into empty line of "".
*/

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

/*
**	Replaces key(like $user) to environment variable value(donglee).
*/

static void			replace_key_with_value(t_token *token, int flag)
{
	char	*key;
	size_t	j;
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

/*
**	Handles exceptional case like "hel$user", "$user$path" etc.
*/

void				replace_exception_env(t_token *token)
{
	t_token *tmp;

	tmp = token;
	copy_env_key(&(tmp->data));
}

/*
**	Finds if there is one environment character in a token.
**	Ex) "$user" returns true.
**	"hi$user" returns false. "$user$path" returns false.
*/

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

/*
**	Converts environment character to environment variables value.
**	Ex) "hello$user" -> "hellodonglee"
*/

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
