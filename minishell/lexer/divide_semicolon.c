/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_semicolon.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:09:38 by donglee           #+#    #+#             */
/*   Updated: 2020/12/30 13:32:07 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Gets the number of commnad lines.
**	Ex) echo hi ; echo hi2 ; echo hi3 -> three comand lines.
*/

int		get_num_cmdline(t_token *token)
{
	int		len;
	t_token	*tmp;

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

/*
**	Gets the number of tokens in a single command line.
**	Ex) echo hello world ; echo hi -> first line has three tokens, 2nd one tho.
*/

int		get_num_cmd(t_token **token)
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

/*
**	 copies the token value to cmds.
*/

void	copy_token_to_char(t_token **token,
		int num_cmd, char **cmds)
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

/*
**	Allocates exact size of cmds.
*/

char	***alloc_cmds(t_token *token, char ***cmds, int len)
{
	int		i;
	int		num_cmd;
	t_token	*tmp;
	t_token	*tmp2;

	i = 0;
	tmp = token;
	tmp2 = token;
	if ((cmds = (char ***)malloc(sizeof(char **) * len + 1)) == NULL)
		exit(-1);
	cmds[len] = NULL;
	while (i < len)
	{
		num_cmd = get_num_cmd(&tmp);
		if (!(cmds[i] = (char **)malloc(sizeof(char *) * num_cmd + 1)))
			exit(-1);
		copy_token_to_char(&tmp2, num_cmd, cmds[i]);
		cmds[i][num_cmd] = NULL;
		i++;
	}
	return (cmds);
}

/*
**	Divides tokens by semi colons.
**	Makes three dimensional array divided by semi colons.
**	Copies the token(linked list) to char array.
*/

char	***divide_semicolon(t_token *token)
{
	char	***cmds;
	int		len;

	cmds = NULL;
	len = 0;
	len = get_num_cmdline(token) + 1;
	cmds = alloc_cmds(token, cmds, len);
	return (cmds);
}
