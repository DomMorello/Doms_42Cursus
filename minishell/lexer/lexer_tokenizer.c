/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:15:05 by jipark            #+#    #+#             */
/*   Updated: 2020/11/27 00:59:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		tokenize_normal(t_token *token, t_status *status, char c, char char_type)
{
	int			result;

	result = -1;
	if (char_type == CHAR_NORMAL) //예를들어 echo hi이고, 현재 str[status->i](즉 char c)가 일반 문자인경우
		token->data[(status->j)++] = c; //계속 data에 기록해주고 j인덱스 올려줌
	else if (char_type == CHAR_WHITESPACE) //echo hi이고 현재 data에 echo까지 쓴 상태에서 다음 읽은 문자가 공백인경우
		result = issue_new_token(token, status, FALSE, char_type);
	else if (char_type == CHAR_QUOTE) //echo 'hi'이고 현재 data에 echo까지 쓴 상태에서 다음 읽은 문자가 ' 인 경우
		add_char_and_change_state(token, status, char_type, STATE_IN_QUOTE);
	else if (char_type == CHAR_DQUOTE) //echo "hi" 이고 현재 data에 echo까지 쓴 상태에서 다음 읽은 문자가 " 인 경우
		add_char_and_change_state(token, status, char_type, STATE_IN_DQUOTE);
	else if (char_type == CHAR_ENV) //똑같음
		add_char_and_change_state(token, status, char_type, STATE_IN_ENV);
	else if (char_type == CHAR_SEMICOLON || char_type == CHAR_PIPE || char_type == CHAR_RED_OUT || char_type == CHAR_RED_IN)
		result = issue_new_token(token, status, TRUE, char_type);
	//리디렉션 double output도 추가해야 한다.
	return (result == -1 || result == TRUE);
}

static void		tokenize_quote(t_token *token, t_status *status, char c, int is_end_of_quote)
{
	token->data[(status->j)++] = c; //quote인 경우는 그냥 계속 토큰에 기록
	if (is_end_of_quote) //마지막 end quote 만나면 state를 다시 normal로 변경해줌
		status->state = STATE_NORMAL;
}

static void		tokenize_env(t_token *token, t_status *status, char c, char char_type)
{
	/*
	echo $hi kkk
	$를 만난 상태에서는 status->state가 STATE_IN_ENV 상태로 바뀌는데, 공백을 만나기 전까지는 안풀림
	*/
	if (c == CHAR_WHITESPACE)
	{
		status->state = STATE_NORMAL;
		issue_new_token(token, status, FALSE, CHAR_WHITESPACE);
		return ;
	}
	token->data[(status->j)++] = c; //공백 만나기 전까지는 계속 토큰에 환경변수 이름 기록
}

static int		convert_input_into_tokens(t_token *token, t_status *status, char *str)
{
	char		char_type;

	while (str[status->i]) //read나 gnl로 읽은 문자열을 status의 i인덱스로 하나하나씩 읽음
	{
		char_type = analyze_char_type(str, status); //현재 인덱스의 문자의 타입을 결정함 (이게 특수기호인지, 아니면 문자로 취급하는 예외경우인지 등)
		if (!is_env_exception(token, status, str, char_type)) //문자열에서 현재 읽은 문자가 $일 때, echo hi$user와 같이 환경변수앞에 공백이 아니라 문자인경우 확인
		{ //위와같은 예외 사항이 아닌 경우 무조건 if 안으로 들어옴.
			if (status->state == STATE_NORMAL)
				tokenize_normal(token, status, str[status->i], char_type);
			else if (status->state == STATE_IN_QUOTE) //echo "hi my name is" 문자열에서 status->i가 h를 가리킨경우.
				tokenize_quote(token, status, str[status->i], is_end_of_quote(char_type, CHAR_QUOTE));
			else if (status->state == STATE_IN_DQUOTE)
				tokenize_quote(token, status, str[status->i], is_end_of_quote(char_type, CHAR_DQUOTE));
			else if (status->state == STATE_IN_ENV)
				tokenize_env(token, status, str[status->i], char_type);
		}
		while (token->next != NULL) //기록하면서 계속 TOEKN을 새로 생성했기 때문에, 현재 TOKEN 변수에 NEXT를 가져와줌
			token = token->next; //현재 위치에서는 그 전 TOEKN을 가리키고 있기 때문에, 다음으로 넘겨줌
		examine_end_of_line(token, status, char_type);
	}
}

t_token			*tokenize_lexer(char *str, int length)
{
	t_token		*token;
	t_status	status;

	if ((token = (t_token *)malloc(sizeof(t_token))) == NULL) //list 첫번재 원소 메모리 할당
		exit(ERROR);
	initiate_token(token, length);
	initiate_token_status(&status, str, length);
	convert_input_into_tokens(token, &status, str);
	return (token); //토큰의 가장 첫 번째 원소 주소를 반환.
}

/*
	1) $user$user 인 경우 dongleedonglee 문자열로 하나의 토큰으로 해야 한다.
	2) 큰 따옴표와 따옴표 안에 있는 환경변수를 치환해야 한다. (따로 로직)
	3) '>>' 더블 아웃풋을 파싱해야 하는데 이 또한 따로 로직으로 처리해야 할 것 같다.
	4) 세미콜론으로 나눠서 2차원 문자열 배열을 순서대로 내 함수에 넘겨줘야 한다.
	5) copy_env 를 통해 복제한 리스트를 갖고 환경변수를 치환하도록 해야 한다.
*/

void check_dred_out(t_token *token)
{
	
}

int				main(int argc, char const *argv[])
{
	t_token		*token;
	char		buf[BUF_SIZE];
	int			i;

	while (TRUE)
	{
		handle_prompt(buf);
		token = tokenize_lexer(buf, ft_strlen(buf)); //링크드 리스트의 헤드 부분 포인터 주소 반환
		if (check_basic_grammar(token))
		{
			t_token *tmp = token;
			t_token *tmp2 = token;
			adjust_env(tmp);//환경변수를 찾아서 해당 value로 바꿔줘야 함.
			check_dred_out(tmp2);
			//테스트 출력
			while (tmp) 
			{
				printf("%s			,%d\n", tmp->data, tmp->type);
				tmp = tmp->next;
			}
		}
		free_all_tokens(&token, free);
	}
	return (EXIT_SUCCESS);
}