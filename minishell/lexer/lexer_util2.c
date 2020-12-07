/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:23:45 by jipark            #+#    #+#             */
/*   Updated: 2020/12/07 22:37:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			examine_end_of_line(t_token *token, t_status *status, char char_type)
{
	(status->i)++; //norm때문에 i를 여기서 올려줌
	if (char_type != CHAR_NULL || status->j <= 0) //여기서 말하는 char_type은 gnl로 읽은 문자열의 마지막 문자가 null인지
		return ; //status->j 에 대한 조건은 없어도 될것같음. 보완점.
	token->data[status->j] = CHAR_NULL;
	status->j = 0;
}

int				is_env_exception(t_token *token, t_status *status, char *str, char char_type)
{
	/*
	** 현재 읽은 문자가 $인데, 예외 케이스로 일반 문자로 인식하는 경우가 아니면 무조건 환경변수에 대한 문자임.
	** 환경변수 인 경우 if 절에 들어감.
	** 보완점 : echo $user$user인 경우, token 반환시 'echo', 'dongleedonglee' 두개를 반환하도록 해야함...
	*/
	// if (char_type == CHAR_ENV && (str[status->i - 1] != ' ' && str[status->i + 1] != ' ')
	// 	&& status->state != STATE_IN_QUOTE && status->state != STATE_IN_DQUOTE) //예시 : echo hi my name is$user, 현재 i가 $를 가리킴.,
	// 	//$앞에 공백이 아닌 경우에 대한 예외 처리. $앞이 공백인 경우는 다른 곳에서 잘 처리되기 때문.
	// {
	// 	token->data[status->j] = CHAR_NULL; //현재 token->data : name/0
	// 	if ((token->next = (t_token *)malloc(sizeof(t_token))) == NULL) //token->next를 생성해주고
	// 		exit(ERROR);
	// 	token = token->next; //token이 다음 token을 읽게 해줌.
	// 	initiate_token(token, status->length - status->i); //token초기화.
	// 	status->j = 0; //다시 j를 0으로 초기화
	// 	token->type = CHAR_ENV;
	// 	token->data[(status->j)++] = CHAR_ENV; //새로운 토큰의 첫번째 문자를 $로 기록하고, j를 1 증가시켜줌
	// 	status->state = STATE_IN_ENV;
	// 	return (TRUE);
	// }
	// return (FALSE);
	/* 이 부분을 통째로 바꿔야 한다. 앞에랑 붙어있으면 붙어있는 그대로 token 하나로 해야된다. */
	if (char_type == CHAR_ENV && (str[status->i - 1] != ' ' && str[status->i + 1] != ' ')
		&& status->state != STATE_IN_QUOTE && status->state != STATE_IN_DQUOTE)
	{
		// token->data[status->j] = CHAR_NULL; //현재 token->data : name/0
		// if ((token->next = (t_token *)malloc(sizeof(t_token))) == NULL) //token->next를 생성해주고
			// exit(ERROR);
		// token = token->next; //token이 다음 token을 읽게 해줌.
		// initiate_token(token, status->length - status->i); //token초기화.
		// status->j = 0; //다시 j를 0으로 초기화
		token->type = CHAR_ENV;
		token->data[(status->j)++] = CHAR_ENV; //새로운 토큰의 첫번째 문자를 $로 기록하고, j를 1 증가시켜줌
		status->state = STATE_IN_ENV;
		return (TRUE);
	}
	return (FALSE);
}
/*
gnl로 읽은 문자 : echo hi
문자열 길이 : 7
가장 처음 token 초기화 : token->data length를 7로 초기화함.
echo hi를 계속 읽음
data[0] = e
data[1] = c
data[2] = h
data[3] = o
(0, 1, 2, 3, 4는 모두 status->j)
if 공백을 만나면
	data[4] = \0;
	new_token = malloc
	token->next = new_token;
	new_token->data = malloc(status->length - status->i); //길이의 최대치를 할당
*/

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
		return (NULL); //TODO : free all tokens.
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

int				check_basic_grammar(t_token *token)
{
	while (token != NULL) //echo, "hi", ;, cd
	{
		if (token->type == CHAR_QUOTE || token->type == CHAR_DQUOTE)
		{
			if (token->data[ft_strlen(token->data) - 1] != token->type) //따옴표가 안닫혀있는경우 == 맨 마지막 문자가 동등하지 않은경우
			{
				/*
				printf("--------------debug grammar spot-----------\n");
				printf("token data : %s\n", token->data);
				printf("token data length : %ld\n", ft_strlen(token->data));
				printf("last character : %c\n", token->data[ft_strlen(token->data) - 1]);
				printf("token type : %d (34 == \")\n", token->type);
				printf("--------------debug grammar spot-----------\n");
				*/
				ft_putstr_fd("minishell : syntax error near '", 1);
				ft_putstr_fd(token->data, 1);
				ft_putstr_fd("'\n", 1);
				return (FALSE);
			}
		}
		if (token->type == CHAR_SEMICOLON && token->next->type == CHAR_SEMICOLON) //echo hi;;
		{
			ft_putstr_fd("minishell : syntax error near ';;'\n", 1);
			return (FALSE);
		}
		/* 따옴표 상황이 아닌데 >>> || << 이런식으로 오면 에러처리 해야 함*/
		if (!token->next && (token->type == CHAR_PIPE || token->type == CHAR_RED_OUT || token->type == CHAR_RED_IN || token->type == '\\'))
		{
			/* 이거 하기 전에 마지막에 내용없는 노드를 삭제해야함. */
			ft_putstr_fd("minishell : syntax error near ';;'\n", 1);
			return (FALSE);
		}
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
