/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:23:45 by jipark            #+#    #+#             */
/*   Updated: 2020/12/23 20:38:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			examine_end_of_line(t_token *token,
	t_status *status, char char_type)
{
	(status->i)++;
	if (char_type != CHAR_NULL || status->j <= 0)
		return ;
	token->data[status->j] = CHAR_NULL;
	status->j = 0;
}

int				is_env_exception(t_token *token, t_status *status,
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

t_token			**convert_list_into_array(t_token *token)
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

int	check_grammar1(t_token *token)
{
	if (token->type == CHAR_QUOTE || token->type == CHAR_DQUOTE)
	{
		if (token->data[ft_strlen(token->data) - 1] != token->type)
		{
			ft_putstr_fd(ERR_QUOTE, STDERR);
			ft_putstr_fd(token->data, STDERR);
			ft_putstr_fd("'\n", STDERR);
			return (FALSE);
		}
	}
	if (token->type == CHAR_SEMICOLON && token->next &&
		token->next->type == CHAR_SEMICOLON)
	{
		ft_putstr_fd(ERR_DSEMI, STDERR);
		return (FALSE);
	}
	if (!token->next && (token->type == CHAR_PIPE || token->type ==
		CHAR_RED_OUT || token->type == CHAR_RED_IN || token->type == '\\'))
	{
		ft_putstr_fd(ERR_NEWL, STDERR);
		return (FALSE);
	}
	return (TRUE);
}

int check_grammar2(t_token *token)
{
	if (token->type != CHAR_DQUOTE && token->type != CHAR_QUOTE)
	{
		if (!ft_strncmp(token->data, ">", 1) && token->next && 
		!ft_strncmp(token->next->data, ">", 1) && token->next->next &&
		!ft_strncmp(token->next->next->data, ">", 1))
		{
			ft_putstr_fd(ERR_REDOUT, STDERR);
			return (FALSE);
		}
		if (!ft_strncmp(token->data, "<", 1) && token->next &&
			!ft_strncmp(token->next->data, "<", 1))
		{
			ft_putstr_fd(ERR_REDIN, STDERR);
			return (FALSE);
		}
		if (!ft_strncmp(token->data, "|", 1) && token->next &&
			!ft_strncmp(token->next->data, "|", 1))
		{
			ft_putstr_fd(ERR_PIPE, STDERR);
			return (FALSE);
		}
	}
	return (TRUE);
}

int				check_basic_grammar(t_token *token)
{
	if (token && !ft_strncmp((*token).data, ";", 1))
	{
		ft_putstr_fd(ERR_SEMI, STDERR);
		return (FALSE);
	}
	while (token != NULL)
	{
		if (!check_grammar1(token))
			return (FALSE);
		if (!check_grammar2(token))
			return (FALSE);
		token = token->next;
	}
	return (TRUE);
}

void			free_all_tokens(t_token *token, void (*del)(void *))
{
	if (!token)
		return ;
	while (token)
	{
		del(token->data);
		del(token);
		token = token->next;
	}
}
