/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:09:20 by donglee           #+#    #+#             */
/*   Updated: 2020/12/28 17:09:21 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			handle_prompt(char *buf)
{
	char	tmp;
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	tmp = 0;
	ft_putstr_fd("\033[0;32mmongshell\033[0;34m$ \033[0m", STDERR);
	ft_bzero(buf, BUF_SIZE);
	while (tmp != '\n')
	{
		while ((ret = read(STDIN, &tmp, 1)) && tmp != '\n')
			buf[i++] = tmp;
		if (tmp != '\n' && i == 0 && !ret)
		{
			ft_putstr_fd("exit\n", STDERR);
			exit(EXIT_SUCCESS);
		}
	}
}

void			initiate_token(t_token *token, int length)
{
	if ((token->data = (char *)malloc(sizeof(char) * (length + 1))) == NULL)
		exit(ERROR);
	ft_bzero((void *)token->data, length + 1);
	token->type = TOKEN;
	token->next = NULL;
}

void			initiate_token_status(t_status *status, char *str, int length)
{
	status->i = 0;
	status->j = 0;
	status->state = STATE_NORMAL;
	status->length = length;
	status->str = str;
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
