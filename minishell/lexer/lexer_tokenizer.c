/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jipark <jipark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:15:05 by jipark            #+#    #+#             */
/*   Updated: 2020/11/26 14:52:03 by jipark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		tokenize_normal(t_token *token, t_status *status, char c, char char_type)
{
	int			result;

	result = -1;
	if (char_type == CHAR_NORMAL) //예를들어 echo hi이고, 현재 str[status->i](즉 char c)가 일반 문자인경우
	{
		token->data[(status->j)++] = c; //계속 data에 기록해주고 j인덱스 올려줌
		//check_command_flag(token, status); (지워도 문제없을듯 ㅋ, 현재 token이 명령어인지 아닌지 ㅊ ㅔ크)
	}
	else if (char_type == CHAR_WHITESPACE) //echo hi이고 현재 data에 echo까지 쓴 상태에서 다음 읽은 문자가 공백인경우
		result = issue_new_token(token, status, FALSE, char_type);
	else if (char_type == CHAR_QUOTE) //echo 'hi'이고 현재 data에 echo까지 쓴 상태에서 다음 읽은 문자가 ' 인 경우
		add_char_and_change_state(token, status, char_type, STATE_IN_QUOTE);
	else if (char_type == CHAR_DQUOTE) //echo "hi" 이고 현재 data에 echo까지 쓴 상태에서 다음 읽은 문자가 " 인 경우
		add_char_and_change_state(token, status, char_type, STATE_IN_DQUOTE);
	else if (char_type == CHAR_ENV) //똑같음
		add_char_and_change_state(token, status, char_type, STATE_IN_ENV);
	else if (char_type == CHAR_SEMICOLON || char_type == CHAR_PIPE || char_type == CHAR_REDIRECTION)
		result = issue_new_token(token, status, TRUE, char_type);
	return (result == -1 || result == TRUE); //exit 처리 고려
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
			{
				if (!tokenize_normal(token, status, str[status->i], char_type))
					return (FALSE);
			}
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
	return (TRUE); //문자 검사 마치면 TRUE 리턴.
}

t_token			*tokenize_lexer(char *str, int length)
{
	t_token		*token;
	t_status	status;

	if ((token = (t_token *)malloc(sizeof(t_token))) == NULL) //list 첫번재 원소 메모리 할당
		return (NULL);
	if (!initiate_token(token, length))
		return (NULL); //TODO : free token.
	initiate_token_status(&status, str, length);
	if (!convert_input_into_tokens(token, &status, str))
		return (NULL); //TODO : free all tokens.
	return (token); //토큰의 가장 첫 번째 원소 주소를 반환.
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
			/*
			현재는 echo $user hi 이런식으로 생긴 토큰을 echo donglee hi로 변경해줘야함.
			*/
			adjust_env(tmp);

			//테스트 출력
			while (tmp) {
				printf("%s\n", tmp->data);
				tmp = tmp->next;
			}

			/*
			1) quote/dquote environment
			*/

			/*
			adjust_env(tmp);
			*/
			/*
			while (tmp)
			{
				if (tmp->white_space_flag == TRUE)
					printf("%s, next white space : yes\n", tmp->data);
				else if (tmp->white_space_flag == FALSE)
					printf("%s, next white space : no\n", tmp->data);
				tmp = tmp->next;
			}
			*/
			/*
			while (tmp) {
				printf("%s\n", tmp->data);
				tmp = tmp->next;
			}
			*/
		}

		//{
			/*
			adjust_env(token);
			*/
		/*
			i = 0;
			t_token **tokens = convert_list_into_array(token);
			while (tokens[i])
			{
				if (tokens[i]->type == COMMAND)
					printf("%15s, status : COMMAND\n", tokens[i]->data);
				else if (tokens[i]->type == CHAR_ENV)
					printf("%15s, status : ENV\n", tokens[i]->data);
				else if (tokens[i]->type == CHAR_QUOTE)
					printf("%15s, status : QUOTE\n", tokens[i]->data);
				else if (tokens[i]->type == CHAR_DQUOTE)
					printf("%15s, status : DQUOTE\n", tokens[i]->data);
				else if (tokens[i]->type == TOKEN)
					printf("%15s, status : TOKEN\n", tokens[i]->data);
				else if (tokens[i]->type == CHAR_PIPE)
					printf("%15s, status : PIPE\n", tokens[i]->data);
				else if (tokens[i]->type == CHAR_REDIRECTION)
					printf("%15s, status : REDIRECTION\n", tokens[i]->data);
				else if (tokens[i]->type == CHAR_SEMICOLON)
					printf("%15s, status : SEMICOLON\n", tokens[i]->data);
				else
					printf("null");
				i++;
			}
		*/
		free_all_tokens(&token, free);
	}
	return (EXIT_SUCCESS);
}



/*


TODO

1. Reset all logics.
2. Tokenize를 initiate하기
3. quote에 한해서만 convert작업 실행. $ 발견했을때 치환해주기.





*/
