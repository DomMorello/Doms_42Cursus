/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:00:28 by jipark            #+#    #+#             */
/*   Updated: 2020/12/08 16:41:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_newline(char *buf)
{
	int		i;

	i = BUF_SIZE - 1;
	while (i >= 0)
	{
		if (buf[i] == CHAR_NEWLINE)
		{
			buf[i] = CHAR_NULL;
			return ;
		}
		i--;
	}
}

void		handle_prompt(char *buf)
{
	ft_putstr_fd("minishell % ", 1);
	ft_bzero(buf, BUF_SIZE);
	read(STDIN, buf, BUF_SIZE); //읽기
	remove_newline(buf); //마지막 newline 지우기
}

void			initiate_token(t_token *token, int length)
{
	if ((token->data = (char *)malloc(sizeof(char) * (length + 1))) == NULL)
		exit(ERROR);
	ft_bzero((void *)token->data, length + 1);
	token->type = TOKEN;
	token->next = NULL;
}

void		initiate_token_status(t_status *status, char *str, int length)
{
	status->i = 0; //read나 gnl로 읽은 문자열 인덱스
	status->j = 0;
	status->state = STATE_NORMAL; //따옴표가 아닌 일반 노말
	status->length = length;
	status->str = str;
}
