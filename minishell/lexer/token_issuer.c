/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_issuer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 15:45:54 by donglee           #+#    #+#             */
/*   Updated: 2020/12/29 17:07:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	 
*/

static int	issue_special_token(t_token *token,
		t_status *status, char char_type)
{
	token->data[0] = char_type;
	token->data[1] = CHAR_NULL;
	token->type = char_type;
	if ((token->next = (t_token *)malloc(sizeof(t_token))) == NULL)
		exit(ERROR);
	token = token->next;
	initiate_token(token, status->length - status->i);
	return (TRUE);
}

/*
**	Makes new token and initiates it. 
*/

int			issue_new_token(t_token *token, t_status *status,
	int flag, char char_type)
{
	if (status->j > 0)
	{
		token->data[status->j] = CHAR_NULL;
		if ((token->next = (t_token *)malloc(sizeof(t_token))) == NULL)
			exit(ERROR);
		token = token->next;
		initiate_token(token, status->length - status->i);
		status->j = 0;
	}
	if (flag && !issue_special_token(token, status, char_type))
		return (FALSE);
	return (TRUE);
}

void		add_char_and_change_state(t_token *token, t_status *status,
	char char_type, int state)
{
	token->data[(status->j)++] = char_type;
	token->type = char_type;
	status->state = state;
}
