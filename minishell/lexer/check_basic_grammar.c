/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_basic_grammar.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 18:18:29 by donglee           #+#    #+#             */
/*   Updated: 2020/12/30 13:31:49 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	If the token is not fully covered by (double)quotation marks, returns false.
**	Ex) "hello
*/

int				check_grammar1(t_token *token)
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

/*
**	If >>> comes, returns false.
**	If << comes, returns false.
**	If || comes returns false.
*/

int				check_grammar2(t_token *token)
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

/*
**	If ; comes first, returns false.
**	Checks basic grammar.
*/

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
