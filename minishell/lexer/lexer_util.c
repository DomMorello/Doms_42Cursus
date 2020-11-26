/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:00:28 by jipark            #+#    #+#             */
/*   Updated: 2020/11/26 18:10:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	flush_buf(char *buf)
{
	int		i;

	i = 0;
	while (i < BUF_SIZE)
		buf[i++] = CHAR_NULL;
}

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
	flush_buf(buf); //모든 버퍼 0으로 초기화
	read(STDIN_FILENO, buf, BUF_SIZE); //읽기
	remove_newline(buf); //마지막 newline 지우기
}

int			initiate_token(t_token *token, int length)
{
	if ((token->data = (char *)malloc(sizeof(char) * (length + 1))) == NULL)
		return (FALSE);
	for (int i = 0; i <= length; i++) {
		token->data[i] = CHAR_NULL;
	} //token의 data에 입력된 문자열 길이만큼 malloc해주고, 문자열을 전부 0으로 초기화해줌 (쓰레기값때문에)
	token->type = TOKEN;
	token->next = NULL;
	return (TRUE);
}

void		initiate_token_status(t_status *status, char *str, int length)
{
	status->i = 0; //read나 gnl로 읽은 문자열 인덱스
	status->j = 0;
	status->state = STATE_NORMAL; //따옴표가 아닌 일반 노말
	status->length = length;
	status->command_flag = TRUE;
	status->str = str;
}
