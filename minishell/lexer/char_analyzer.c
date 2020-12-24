/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_analyzer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:28:31 by donglee           #+#    #+#             */
/*   Updated: 2020/12/24 18:30:37 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	get_char_type(char c)
{
	if (c == '\'')
		return (CHAR_QUOTE);
	if (c == '\"')
		return (CHAR_DQUOTE);
	if (c == '|')
		return (CHAR_PIPE);
	if (c == ' ')
		return (CHAR_WHITESPACE);
	if (c == ';')
		return (CHAR_SEMICOLON);
	if (c == '>')
		return (CHAR_RED_OUT);
	if (c == '<')
		return (CHAR_RED_IN);
	if (c == '$')
		return (CHAR_ENV);
	if (c == '\0')
		return (CHAR_NULL);
	return (CHAR_NORMAL);
}

int			is_normal_env(char c1, char c2)
{
	return (c1 == '$' && (c2 == ' ' || c2 == '\0' || c2 == ';' || c2 == '\\'));
}

int			is_normal_special_char(char c1, char c2)
{
	return (c1 == '\\' && (c2 == '<' || c2 == '>' || c2 == '|' || c2 == '$'
		|| c2 == '\"' || c2 == '\'' || c2 == '\\' || c2 == ';'));
}

char		analyze_char_type(char *str, t_status *status)
{
	if (is_normal_env(str[status->i], str[status->i + 1]))
		return (CHAR_NORMAL);
	if (is_normal_special_char(str[status->i], str[status->i + 1]))
	{
		(status->i)++;
		return (CHAR_NORMAL);
	}
	if (status->state == STATE_IN_QUOTE && str[status->i] != CHAR_QUOTE)
		return (CHAR_NORMAL);
	if (status->state == STATE_IN_DQUOTE && str[status->i] != CHAR_DQUOTE)
		return (CHAR_NORMAL);
	return (get_char_type(str[status->i]));
}

int			is_end_of_quote(char char_type, char c)
{
	return (char_type == c);
}
