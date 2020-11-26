/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_converter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:26:45 by jipark            #+#    #+#             */
/*   Updated: 2020/11/27 01:01:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void			handle_empty_environ(t_token *token)
{
	free(token->data);
	token->data = ft_strdup(""); //빈문자열을 반환.
	token->type = TOKEN;
}
static void			replace_key_with_value(t_token *token, char **environ)
{
	char			*key;
	int				i;
	int				j;
	int				flag;

	i = 0;
	flag = FALSE;
	key = token->data + sizeof(char); //현재 문자가 $user면 당장 필요한건 user라는 문자이기 때문에 포인터 주소 올려줌.
	while (environ[i] != NULL) //환경변수 반복문 돌면서
	{
		j = 0;
		while (environ[i][j] != '=') //환경변수들이 xx=yy 형태이기때문에, key(xx)의 길이를 구함
			j++;
		if (!ft_strncmp(environ[i], key, j)) //key(user)랑 environ[i](xx)를 비교
		{
			free(token->data); //만약 일치하는 환경변수가 있으면 기존 token의 문자열($user) data 지우고
			token->data = ft_strdup(&environ[i][j + 1]); //해당 data에 환경변수 value를 복사해옴
			token->type = TOKEN; //이런거는 사실 필요없을듯
			flag = TRUE; //환경변수가 존재하지 않는 경우 ""로 대체하기 위해 flag세움
			return ;
		}
		i++;
	}
	if (!flag) //환경변수 못찾은 경우
		handle_empty_environ(token);
}

// static void			search_and_replace_env(t_token **token, char **environ)
// {
// 	t_token			*new_token;
// 	t_token 		*new_token_tmp;
// 	t_token 		*last;

// 	(*token)->next->data += sizeof(char);
// 	(*token)->next->data[ft_strlen((*token)->next->data) - 1] = CHAR_NULL;
// 	new_token = tokenize_lexer((*token)->next->data, ft_strlen((*token)->next->data));
// 	new_token_tmp = new_token;
// 	while (new_token_tmp)
// 	{
// 		if (new_token_tmp->type == CHAR_ENV)
// 			replace_key_with_value(new_token_tmp, environ);
// 		new_token_tmp = new_token_tmp->next;
// 	}
// 	last = (*token)->next->next;
// 	(*token)->next->data -= sizeof(char);
// 	free((*token)->next->data);
// 	free((*token)->next);
// 	(*token)->next = new_token;
// 	while (new_token->next != NULL)
// 		new_token = new_token->next;
// 	new_token->next = last;
// }

void			adjust_env(t_token *token)
{
	extern char	**environ;
	/* 여기서 내가 복사한 전역변수를 검사하도록 수정해야 한다. */
	t_token		*tmp;

	tmp = token;
	while (tmp != NULL)
	{
		if (tmp->type == CHAR_ENV) //environment 토큰 찾고
			replace_key_with_value(tmp, environ); //key를 value로 변환
		// 보완점 : 따옴표 안의 환경변수를 처리해야함. 여기다가.
		tmp = tmp->next;
	}
	tmp = token;
	while (token != NULL) 
	{
		if (token->data[0] == CHAR_NULL) 
		{
			free(token->data);
			tmp->next = NULL;
			free(token);
			return;
		}
		tmp = token;
		token = token->next;
	}
	/* 이 코드는 왜 있는지 jipark한테 함 물어보자 */
}
