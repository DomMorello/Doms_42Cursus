/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_analyzer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:02:10 by jipark            #+#    #+#             */
/*   Updated: 2020/11/26 23:37:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	get_char_type(char c)
{
	if (c == '\'')
		return CHAR_QUOTE;
	if (c == '\"')
		return CHAR_DQUOTE;
	if (c == '|')
		return CHAR_PIPE;
	if (c == ' ')
		return CHAR_WHITESPACE;
	if (c == ';')
		return CHAR_SEMICOLON;
	if (c == '>')
		return CHAR_RED_OUT;	//파싱에서 double out은 어떻게 처리할까?
	if (c == '<')
		return CHAR_RED_IN;
	if (c == '$')
		return CHAR_ENV;
	if (c == '\0')
		return CHAR_NULL;
	return CHAR_NORMAL;
}

int			is_normal_env(char c1, char c2) //앞에 글자가 $일 때 뒤에가 아래와 같은 경우 $를 환경변수가 아닌 일반 문자로 인식
{
	return (c1 == '$' && (c2 == ' ' || c2 == '\0' || c2 == ';' || c2 == '\\'));
}

int			is_normal_special_char(char c1, char c2) //현재 status->i 문자가 이스케이프 문자일 때 다음 문자가 특수기호인경우
{
	return (c1 == '\\' && (c2 == '<' || c2 == '>' || c2 == '|' || c2 == '$' || c2 == '\"' || c2 == '\'' || c2 == '\\' || c2 == ';'));
}

char		analyze_char_type(char *str, t_status *status)
{
	if (is_normal_env(str[status->i], str[status->i + 1]))
		return (CHAR_NORMAL); //현재 문자가 $인데 이것을 일반 문자로 인식해야할 경우, NORMAL 캐릭터 리턴
	if (is_normal_special_char(str[status->i], str[status->i + 1])) //특수 기호 예외 찾으러 감
	{
		(status->i)++; //이스케이프문자는 토큰에 담을 필요가 없어서 i를 1 증가시킴
		return (CHAR_NORMAL); //normal 리턴
	}
	if (status->state == STATE_IN_QUOTE && str[status->i] != CHAR_QUOTE)
	{ //state는 normal 혹은 quote/dquote 상태를 의미
		/* 여기서 예외를 만들어서 환경변수를 처리해야 할까?
			아니면 마지막쯤에 예외를 만들어서 해야 할까? 
			만약에 여기서 환경변수를 CHAR_ENV 로 바꾸고 상태도 STATR_IN_ENV로
			바꾸면 token으로 나눠져버리려나? 
			여기서는 뭔가 바꾸기가 어려울 것 같다. 전부 token으로 나누는 로직이다.
			아마도 다른 곳에서 마지막쯤에 env로 바꿔주는 로직이 따로 필요할 듯 */
		return (CHAR_NORMAL); //현재 quote에 들어온 상태에서는 모든 문자를 normal로 인식함 echo "hihihihihi" 있으면 따옴표 안의 모든 문자는 normal 인식
	}
	if (status->state == STATE_IN_DQUOTE && str[status->i] != CHAR_DQUOTE) { //쌍따옴표인경우
		return (CHAR_NORMAL);
	}
	return (get_char_type(str[status->i]));
}

int				is_end_of_quote(char char_type, char c)
{
	return (char_type == c);
}
