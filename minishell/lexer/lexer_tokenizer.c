/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:15:05 by jipark            #+#    #+#             */
/*   Updated: 2020/12/23 20:25:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int		tokenize_normal(t_token *token, t_status *status,
	char c, char char_type)
{
	int			result;

	result = -1;
	if (char_type == CHAR_NORMAL)
		token->data[(status->j)++] = c;
	else if (char_type == CHAR_WHITESPACE)
		result = issue_new_token(token, status, FALSE, char_type);
	else if (char_type == CHAR_QUOTE)
		add_char_and_change_state(token, status, char_type, STATE_IN_QUOTE);
	else if (char_type == CHAR_DQUOTE)
		add_char_and_change_state(token, status, char_type, STATE_IN_DQUOTE);
	else if (char_type == CHAR_ENV)
		add_char_and_change_state(token, status, char_type, STATE_IN_ENV);
	else if (char_type == CHAR_SEMICOLON || char_type == CHAR_PIPE ||
		char_type == CHAR_RED_OUT || char_type == CHAR_RED_IN)
		result = issue_new_token(token, status, TRUE, char_type);
	return (result == -1 || result == TRUE);
}

static void		tokenize_quote(t_token *token, t_status *status,
	char c, int is_end_of_quote)
{
	token->data[(status->j)++] = c;
	if (is_end_of_quote)
		status->state = STATE_NORMAL;
}

static void		tokenize_env(t_token *token, t_status *status,
	char c, char char_type)
{
	if (c == CHAR_WHITESPACE)
	{
		status->state = STATE_NORMAL;
		issue_new_token(token, status, FALSE, CHAR_WHITESPACE);
		return ;
	}
	token->data[(status->j)++] = c;
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

static int		convert_input_into_tokens(t_token *token, 
	t_status *status, char *str)
{
	char		char_type;

	trim_end(str);
	while (str[status->i])
	{
		char_type = analyze_char_type(str, status);
		if (!is_env_exception(token, status, str, char_type))
		{
			if (status->state == STATE_NORMAL)
				tokenize_normal(token, status, str[status->i], char_type);
			else if (status->state == STATE_IN_QUOTE)
				tokenize_quote(token, status, str[status->i],
					is_end_of_quote(char_type, CHAR_QUOTE));
			else if (status->state == STATE_IN_DQUOTE)
				tokenize_quote(token, status, str[status->i],
					is_end_of_quote(char_type, CHAR_DQUOTE));
			else if (status->state == STATE_IN_ENV)
				tokenize_env(token, status, str[status->i], char_type);
		}
		while (token->next != NULL)
			token = token->next;
		examine_end_of_line(token, status, char_type);
	}
}

t_token			*tokenize_lexer(char *str, int length)
{
	t_token		*token;
	t_status	status;

	if ((token = (t_token *)malloc(sizeof(t_token))) == NULL)
		exit(ERROR);
	initiate_token(token, length);
	initiate_token_status(&status, str, length);
	convert_input_into_tokens(token, &status, str);
	return (token);
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

void convert_key_to_env(char *env_content, char **token_data,
	char *key, int env_idx)
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
	if ((new = (char *)malloc(sizeof(char) * ft_strlen(*token_data) +
		ft_strlen(&env_content[env_key_len + 1]) - ft_strlen(key) + 1)) == NULL)
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
		if (!ft_strncmp((char *)env_tmp->content, key, env_key_len >
			ft_strlen(key) ? env_key_len : ft_strlen(key)))
			convert_key_to_env((char *)env_tmp->content,
				token_data, key, env_idx);
		env_tmp = env_tmp->next;
	}
}

void copy_env_key(char **tokens)
{
	char *env;
	int i;
	int j;
	int env_idx;

	i = 0;
	env_idx = 0;
	while ((*tokens)[i])
	{
		j = 0;
		if ((*tokens)[i] == CHAR_ENV)
		{
			env_idx = i;
			if (!(env = (char *)malloc(sizeof(char) * ft_strlen(*tokens) + 1)))
				exit(-1);
			i++;
			while ((*tokens)[i] && (*tokens)[i] != ' '
				&& (*tokens)[i] != CHAR_ENV)
				env[j++] = (*tokens)[i++];
			env[j] = 0;
			search_key_in_env(env, tokens, env_idx);
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
			copy_env_key(&(tmp->data));
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
			if ((new = (char *)malloc(sizeof(char) *
				ft_strlen(tmp->data) - 1)) == NULL)
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
		handle_process(cmds[i]);
		i++;
	}
}
