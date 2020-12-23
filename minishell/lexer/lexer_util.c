/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 15:00:28 by jipark            #+#    #+#             */
/*   Updated: 2020/12/23 20:24:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	remove_newline(char *buf)
{
	int		i;

	i = BUF_SIZE - 1;
	while (i >= 0)
	{
		if (buf[i] == CHAR_NEWLINE)
		{
			buf[i] = CHAR_NULL;
			return ;
		}
		i--;
	}
}

void		handle_prompt(char *buf)
{
	char tmp;
	int ret;
	int i;

	ret = 0;
	i = 0;
	ft_putstr_fd("\033[0;32mmongshell\033[0;34m$ \033[0m", STDERR);
	ft_bzero(buf, BUF_SIZE);
	while (ret || tmp != '\n')
	{
		while (ret = read(STDIN, &tmp, 1) && tmp != '\n')
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

void		initiate_token_status(t_status *status, char *str, int length)
{
	status->i = 0;
	status->j = 0;
	status->state = STATE_NORMAL;
	status->length = length;
	status->str = str;
}
