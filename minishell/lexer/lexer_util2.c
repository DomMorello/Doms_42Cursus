/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 15:44:42 by donglee           #+#    #+#             */
/*   Updated: 2020/12/25 15:45:40 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		examine_end_of_line(t_token *token,
	t_status *status, char char_type)
{
	(status->i)++;
	if (char_type != CHAR_NULL || status->j <= 0)
		return ;
	token->data[status->j] = CHAR_NULL;
	status->j = 0;
}

int			is_env_exception(t_token *token, t_status *status,
	char *str, char char_type)
{
	if (char_type == CHAR_ENV && (str[status->i - 1] != ' '
		&& str[status->i + 1] != ' ')
		&& status->state != STATE_IN_QUOTE && status->state != STATE_IN_DQUOTE)
	{
		token->type = CHAR_ENV;
		token->data[(status->j)++] = CHAR_ENV;
		status->state = STATE_IN_ENV;
		return (TRUE);
	}
	return (FALSE);
}

t_token		**convert_list_into_array(t_token *token)
{
	t_token		*tmp;
	t_token		**dest;
	int			size;
	int			i;

	size = 0;
	tmp = token;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		size++;
	}
	if ((dest = (t_token **)malloc(sizeof(t_token *) * (size + 1))) == NULL)
		return (NULL);
	dest[size] = NULL;
	i = 0;
	while (i < size)
	{
		dest[i] = token;
		i++;
		token = token->next;
	}
	return (dest);
}

void		trim_end(char *str)
{
	int len;

	len = ft_strlen(str);
	while (str[len - 1])
	{
		if (str[len - 1] != CHAR_WHITESPACE)
		{
			str[len] = 0;
			return ;
		}
		len--;
	}
}

int			remove_empty_token(t_token *token)
{
	t_token *tmp;
	t_token *prev;

	tmp = token;
	if (!ft_strncmp(tmp->data, "", 1))
		return (FALSE);
	while (tmp)
	{
		if (!tmp->next && !ft_strncmp(tmp->data, "", 1))
		{
			prev->next = NULL;
			free(tmp->data);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (TRUE);
}
