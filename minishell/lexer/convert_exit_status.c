/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_exit_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:30:23 by donglee           #+#    #+#             */
/*   Updated: 2020/12/29 16:11:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
**	Makes new token converting $? into exit status number.
**	Ex) "hi$?$?hello" -> "hi127127hello" 
*/

void	make_new_cmd(char *new, char *cmd)
{
	int		i;
	int		j;
	int		k;
	char	*exit_status;

	i = 0;
	j = 0;
	exit_status = ft_itoa(g_exit_status);
	while (cmd[i])
	{
		k = 0;
		if (cmd[i] == '$' && cmd[i + 1] && cmd[i + 1] == '?')
		{
			while (exit_status[k])
				new[j++] = exit_status[k++];
			i += 2;
			continue ;
		}
		new[j] = cmd[i];
		j++;
		i++;
	}
	free(exit_status);
}

/*
**	Counts the number of exit status character("$?") in a token.
**	Ex) if a token is "$?$?hello$?", the number of $? will be three. 
*/

int		get_num_exit_status(char *cmd)
{
	int i;
	int cnt;

	i = 0;
	cnt = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$' && cmd[i + 1] && cmd[i + 1] == '?')
		{
			cnt++;
			i++;
		}
		i++;
	}
	return (cnt);
}

/*
**	Allocates exact size of reseult length.
**	For example, "$?$?$?" if exit status is 127, "127127127".
**	Its result length is 9.
*/

char	*alloc_new(char *cmd)
{
	int		cmd_len;
	int		exit_cnt;
	char	*exit_status;
	char	*ret;

	ret = NULL;
	exit_cnt = get_num_exit_status(cmd);
	cmd_len = ft_strlen(cmd);
	exit_status = ft_itoa(g_exit_status);
	if ((ret = (char *)malloc(sizeof(char) * (cmd_len - (2 * exit_cnt) +
		(ft_strlen(exit_status) * exit_cnt)) + 1)) == NULL)
		exit(-1);
	ret[cmd_len - (2 * exit_cnt) + (ft_strlen(exit_status) * exit_cnt)] = 0;
	free(exit_status);
	return (ret);
}

/*
**	If the token is "$?", converts it into exit status number.
*/

void	convert_exit_status(t_token *token)
{
	char	*new;
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		if (ft_strnstr(tmp->data, "$?", ft_strlen(tmp->data)))
		{
			if (tmp->type != CHAR_QUOTE)
			{
				new = alloc_new(tmp->data);
				make_new_cmd(new, tmp->data);
				free(tmp->data);
				tmp->data = new;
			}
		}
		tmp = tmp->next;
	}
}
