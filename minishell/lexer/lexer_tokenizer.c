/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:15:05 by jipark            #+#    #+#             */
/*   Updated: 2020/12/16 15:07:51 by marvin           ###   ########.fr       */
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

void trim_end(char *str)
{
	int len;

	len = ft_strlen(str);
	while (str[len - 1])
	{
		if (str[len - 1] != CHAR_WHITESPACE)
		{
			str[len] = 0;
			return ;
		}
		len--;
	}
}

static int		convert_input_into_tokens(t_token *token, t_status *status, char *str)
{
	char		char_type;

	trim_end(str);
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

int make_dred_out(t_token *deleted, t_token *prev, int d_red_out)
{
	if (deleted && d_red_out && !ft_strncmp(deleted->data, ">", ft_strlen(">")))
	{
		prev->next = deleted->next;
		free(prev->data);
		prev->data = ft_strdup(">>");
		free(deleted->data);
		free(deleted);
		return (TRUE);
	}
	return (FALSE);
}

void check_dred_out(t_token *token)
{
	t_token *tmp;
	t_token *tmp2;
	t_token *prev;
	int d_red_out;
	
	tmp = token;
	tmp2 = token;
	while (tmp2)
	{
		tmp = tmp2;
		while (tmp)
		{
			d_red_out = FALSE;
			if (!ft_strncmp(tmp->data, ">", ft_strlen(">")))
				d_red_out = TRUE;
			prev = tmp;
			tmp = tmp->next;
			if (make_dred_out(tmp, prev, d_red_out))
				break ;
		}
		tmp2 = tmp2->next;
	}
}

void convert_to_value(char *new, char *env_content, int *i, int *j)
{
	int env_key_len;

	env_key_len = 0;
	(*i)++;
	while (env_content[env_key_len] != '=')
		env_key_len++;
	env_key_len++;
	while (env_content[env_key_len])
		new[(*j)++] = env_content[env_key_len++];
}

void convert_key_to_env(char *env_content, char **token_data, char *key, int env_idx)
{
	int env_key_len;
	char *new;
	int i;
	int j;

	env_key_len = 0;
	i = 0;
	j = 0;
	while (env_content[env_key_len] != '=')
		env_key_len++;
	if ((new = (char *)malloc(sizeof(char) * ft_strlen(*token_data) + ft_strlen(&env_content[env_key_len + 1]) - ft_strlen(key) + 1)) == NULL)
		exit(-1);
	while ((*token_data)[i])
	{
		if ((*token_data)[i] == CHAR_ENV && i == env_idx)
		{
			convert_to_value(new, env_content, &i, &j);
			i += ft_strlen(key);
		}
		new[j++] = (*token_data)[i++];
	}
	new[j] = 0;
	free(*token_data);
	*token_data = new;
}

void search_key_in_env(char *key, char **token_data, int env_idx)
{
	t_list *env_tmp;
	int env_key_len;

	env_tmp = g_env_list;
	while (env_tmp)
	{
		env_key_len = 0;
		while (((char *)(env_tmp->content))[env_key_len] != '=')
			env_key_len++;
		if (!ft_strncmp((char *)env_tmp->content, key, env_key_len > ft_strlen(key) ? env_key_len : ft_strlen(key)))
			convert_key_to_env((char *)env_tmp->content, token_data, key, env_idx);
		env_tmp = env_tmp->next;
	}
}

void copy_env_key(char **token_data)
{
	char *env;
	int i;
	int j;
	int env_idx;

	i = 0;
	env_idx = 0;
	while ((*token_data)[i])
	{
		j = 0;
		if ((*token_data)[i] == CHAR_ENV)
		{
			env_idx = i;
			if ((env = (char *)malloc(sizeof(char) * ft_strlen(*token_data) + 1)) == NULL)
				exit(-1);
			i++;
			while ((*token_data)[i] && (*token_data)[i] != ' ' && (*token_data)[i] != CHAR_ENV)
				env[j++] = (*token_data)[i++];
			env[j] = 0;
			search_key_in_env(env, token_data, env_idx);
			free(env);
		}
		i++;
	}
}

void adjust_env_in_dquote(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == CHAR_DQUOTE)
		{
			copy_env_key(&(tmp->data));
		}
		tmp = tmp->next;
	}
}

void copy_without_quote(char *data, char *new, char quote_type)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (data[i])
	{
		if (data[i] != quote_type)
			new[j++] = data[i];
		i++;
	}
	new[j] = 0;
}

void erase_quote(t_token *token, char quote_type)
{
	t_token *tmp;
	char *new;

	tmp = token;
	while (tmp)
	{
		if (tmp->type == quote_type)
		{
			if ((new = (char *)malloc(sizeof(char) * ft_strlen(tmp->data) - 1)) == NULL)
				exit(-1);
			copy_without_quote(tmp->data, new, quote_type);
			free(tmp->data);
			tmp->data = new;
		}
		tmp = tmp->next;
	}
}

int remove_empty_token(t_token *token)
{
	t_token *tmp;
	t_token *prev;

	tmp = token;
	if (!ft_strncmp(tmp->data, "", 1))
		return (FALSE);
	while (tmp)
	{
		if (!tmp->next && !ft_strncmp(tmp->data, "", 1))
		{
			prev->next = NULL;
			free(tmp->data);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return (TRUE);
}

int get_num_cmdline(t_token *token)
{
	int len;
	t_token *tmp;

	len = 0;
	tmp = token;
	while (tmp)
	{
		if (!ft_strncmp(tmp->data, ";", 1) && tmp->next)
			len++;
		tmp = tmp->next;
	}
	return (len);
}

int get_num_cmd(t_token **token)
{
	int len;

	len = 0;
	while (*token)
	{
		if (!ft_strncmp((*token)->data, ";", 1))
		{
			*token = (*token)->next;
			break ;
		}
		len++;
		*token = (*token)->next;
	}
	return (len);
}

void copy_token_to_char(t_token **token, int num_cmd, char **cmds)
{
	int i;

	i = 0;
	while (i < num_cmd)
	{
		if (!ft_strncmp((*token)->data, ";", 1))
		{
			*token = (*token)->next;
			continue ;
		}
		cmds[i] = ft_strdup((*token)->data);
		*token = (*token)->next;
		i++;
	}
	cmds[i] = NULL;
}

char ***alloc_cmds(t_token *token, char ***cmds, int len)
{
	int i;
	int num_cmd;
	t_token *tmp;
	t_token *tmp2;

	i = 0;
	tmp = token;
	tmp2 = token;
	if ((cmds = (char ***)malloc(sizeof(char **) * len + 1)) == NULL)
		exit(-1);
	cmds[len] = NULL;
	while (i < len)
	{
		num_cmd = get_num_cmd(&tmp);
		if ((cmds[i] = (char **)malloc(sizeof(char *) * num_cmd + 1)) == NULL)
			exit(-1);
		copy_token_to_char(&tmp2, num_cmd, cmds[i]);
		cmds[i][num_cmd] = NULL;
		i++;
	}
	return (cmds);
}

char ***divide_semicolon(t_token *token)
{
	char ***cmds;
	int len;
	int i;

	i = 0;
	len = 0;
	len = get_num_cmdline(token) + 1;
	cmds = alloc_cmds(token, cmds, len);
	return (cmds);
}

void start_bash(char ***cmds)
{
	int i;

	i = 0;
	while (cmds[i])
	{
		test(cmds[i]);
		i++;
	}
}
