/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 15:44:42 by donglee           #+#    #+#             */
/*   Updated: 2020/12/30 13:32:58 by donglee          ###   ########.fr       */
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

/*
**	Previous parser cannot handle this exception like "hello$user"
**	Without this function, previous parser divide tokens into two
**	such as "hello", "$user".
**	To distinguish this exception, this function exists.
*/

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

/*
**	If first token is empty string, just returns false.
**	For some reasons, empty string is added at the end of tokens.
**	So, deletes the unnecessary empty string.
*/

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
