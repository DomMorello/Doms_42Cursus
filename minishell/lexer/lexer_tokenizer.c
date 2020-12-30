/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 13:44:49 by donglee           #+#    #+#             */
/*   Updated: 2020/12/30 13:44:50 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Basically, tokens are divided by white space.
**	Parses the character types and handles them in relative funcs.
**	Semi colon, redirection, pipe characters also divies the token.
*/

static int		tokenize_normal(t_token *token, t_status *status,
	char c, char char_type)
{
	int	result;

	result = -1;
	if (char_type == CHAR_NORMAL)
		token->data[(status->j)++] = c;
	else if (char_type == CHAR_WHITESPACE)
		result = issue_new_token(token, status, FALSE, char_type);
	else if (char_type == CHAR_QUOTE)
		add_char_and_change_state(token, status, char_type, STATE_IN_QUOTE);
	else if (char_type == CHAR_DQUOTE)
		add_char_and_change_state(token, status, char_type, STATE_IN_DQUOTE);
	else if (char_type == CHAR_ENV)
		add_char_and_change_state(token, status, char_type, STATE_IN_ENV);
	else if (char_type == CHAR_SEMICOLON || char_type == CHAR_PIPE ||
		char_type == CHAR_RED_OUT || char_type == CHAR_RED_IN)
		result = issue_new_token(token, status, TRUE, char_type);
	return (result == -1 || result == TRUE);
}

/*
**	If parsing character(c) is in state of (double) quote,
**	just puts the characters in the token.
**	And when it confronts closing (double) quotation mark,
**	changes the state to normal.
*/

static void		tokenize_quote(t_token *token, t_status *status,
	char c, int is_end_of_quote)
{
	token->data[(status->j)++] = c;
	if (is_end_of_quote)
		status->state = STATE_NORMAL;
}

/*
**	If input is "$user", and next character is white space,
**	makes new token and links it to the list.
*/

static void		tokenize_env(t_token *token, t_status *status,
	char c)
{
	if (c == CHAR_WHITESPACE)
	{
		status->state = STATE_NORMAL;
		issue_new_token(token, status, FALSE, CHAR_WHITESPACE);
		return ;
	}
	token->data[(status->j)++] = c;
}

/*
**	If not exceptional case, tokenizes all types of inputs.
*/

static void		convert_input_into_tokens(t_token *token,
	t_status *status, char *str)
{
	char		char_type;

	trim_end(str);
	while (str[status->i])
	{
		char_type = analyze_char_type(str, status);
		if (!is_env_exception(token, status, str, char_type))
		{
			if (status->state == STATE_NORMAL)
				tokenize_normal(token, status, str[status->i], char_type);
			else if (status->state == STATE_IN_QUOTE)
				tokenize_quote(token, status, str[status->i],
					is_end_of_quote(char_type, CHAR_QUOTE));
			else if (status->state == STATE_IN_DQUOTE)
				tokenize_quote(token, status, str[status->i],
					is_end_of_quote(char_type, CHAR_DQUOTE));
			else if (status->state == STATE_IN_ENV)
				tokenize_env(token, status, str[status->i]);
		}
		while (token->next != NULL)
			token = token->next;
		examine_end_of_line(token, status, char_type);
	}
}

/*
**	Makes token list and initiates all the member variables
**	in the token and state structure.
**	Converts input into tokens.
*/

t_token			*tokenize_lexer(char *str, int length)
{
	t_token		*token;
	t_status	status;

	if ((token = (t_token *)malloc(sizeof(t_token))) == NULL)
		exit(ERROR);
	initiate_token(token, length);
	initiate_token_status(&status, str, length);
	convert_input_into_tokens(token, &status, str);
	return (token);
}
