/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:23:45 by jipark            #+#    #+#             */
/*   Updated: 2020/12/12 16:35:06 by marvin           ###   ########.fr       */
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
	if (char_type == CHAR_ENV && (str[status->i - 1] != ' ' && str[status->i + 1] != ' ')
		&& status->state != STATE_IN_QUOTE && status->state != STATE_IN_DQUOTE)
	{
		token->type = CHAR_ENV;
		token->data[(status->j)++] = CHAR_ENV; //새로운 토큰의 첫번째 문자를 $로 기록하고, j를 1 증가시켜줌
		status->state = STATE_IN_ENV;
		return (TRUE);
	}
	return (FALSE);
}

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
	if (token && !ft_strncmp((*token).data, ";", 1))
	{
		ft_putstr_fd("minishell : syntax error near unexpected token `;'\n", STDERR);
		return (FALSE);
	}
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
				ft_putstr_fd("minishell : syntax error near '", STDERR);
				ft_putstr_fd(token->data, STDERR);
				ft_putstr_fd("'\n", STDERR);
				return (FALSE);
			}
		}
		if (token->type == CHAR_SEMICOLON && token->next && token->next->type == CHAR_SEMICOLON) //echo hi;;
		{
			ft_putstr_fd("minishell : syntax error near ';;'\n", STDERR);
			return (FALSE);
		}
		if (!token->next && (token->type == CHAR_PIPE || token->type == CHAR_RED_OUT || token->type == CHAR_RED_IN || token->type == '\\'))
		{
			ft_putstr_fd("minishell : syntax error near unexpected token `newline'\n", STDERR);
			return (FALSE);
		}
		if (token->type != CHAR_DQUOTE && token->type != CHAR_QUOTE)
		{
			if (!ft_strncmp(token->data, ">", 1) && token->next && !ft_strncmp(token->next->data, ">", 1) && token->next->next && !ft_strncmp(token->next->next->data, ">", 1))
			{
				ft_putstr_fd("minishell : syntax error near unexpected token `>'\n", STDERR);
				return (FALSE);
			}
			if (!ft_strncmp(token->data, "<", 1) && token->next && !ft_strncmp(token->next->data, "<", 1))
			{
				ft_putstr_fd("minishell : syntax error near unexpected token `<'\n", STDERR);
				return (FALSE);
			}
			if (!ft_strncmp(token->data, "|", 1) && token->next && !ft_strncmp(token->next->data, "|", 1))
			{
				ft_putstr_fd("minishell : syntax error near unexpected token `|'\n", STDERR);
				return (FALSE);
			}
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
