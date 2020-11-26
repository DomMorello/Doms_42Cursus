/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_issuer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jipark <jipark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:22:18 by jipark            #+#    #+#             */
/*   Updated: 2020/11/26 14:33:52 by jipark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	issue_special_token(t_token *token, t_status *status, char char_type)
{ //보완점 <, >> 같은 경우 처리 해줘야함

/*
해당 함수는 ;, >, | 같이 1개로 끝나는 토큰 처리용
echo hi > cat.txt
는
"echo", "hi". ">" "cat.txt"
*/
	token->data[0] = char_type;
	token->data[1] = CHAR_NULL;
	token->type = char_type;
	if ((token->next = (t_token *)malloc(sizeof(t_token))) == NULL)
		return (FALSE);
	token = token->next;
	initiate_token(token, status->length - status->i);
	return (TRUE);
}

int			issue_new_token(t_token *token, t_status *status, int flag, char char_type) //flag 필요없을듯.
{
	/* 커맨드 구분 할 필요가 없어진 관계로 이부분도 생략해도 될듯싶습니다.
	if (token->type == COMMAND)
		status->command_flag = FALSE;
	else if (status->command_flag == FALSE && flag && char_type != CHAR_REDIRECTION)
		status->command_flag = TRUE;
	*/
	if (status->j > ZERO_INDEX)
	{
		token->data[status->j] = CHAR_NULL; //그러면 현재 토큰의 마지막 j자리를 null로 마무리
		if ((token->next = (t_token *)malloc(sizeof(t_token))) == NULL) //새로운 토큰 생성
			return (FALSE);  //현재 토큰의 next를 새 토큰 주소로 입력해둠
		token = token->next; //다음 토큰을 현재 토큰으로 함(땡겨줌)
		initiate_token(token, status->length - status->i); //초기화 하고
		status->j = ZERO_INDEX; //다시 첫번째부터 기록해야하기 때문에 j를 0으로
	}
	if (flag && !issue_special_token(token, status, char_type))
		return (FALSE);
	return (TRUE);
}

void		check_command_flag(t_token *token, t_status *status)
{
	if (status->command_flag == TRUE)
		token->type = COMMAND;
	else
		token->type = TOKEN;
}

void		add_char_and_change_state(t_token *token, t_status *status, char char_type, int state)
{ //공백 만나고 새로 발급된 토큰의 가장 첫 번째 글자는 char_type (따옴표, 쌍따옴표, 환경변수 기호)로 기록해줌
	token->data[(status->j)++] = char_type;
	token->type = char_type;
	status->state = state; //state_in_quote, dquote, env 등으로 성격을 명시
}
