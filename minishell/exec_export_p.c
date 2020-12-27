/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export_p.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:31:17 by donglee           #+#    #+#             */
/*   Updated: 2020/12/25 17:51:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void	sort_export(t_list **list)
{
	int		swapped;
	t_list	*ptr1;
	t_list	*lptr;
	char	*tmp;

	swapped = 1;
	lptr = NULL;
	while (swapped)
	{
		swapped = 0;
		ptr1 = *list;
		while (ptr1->next != lptr)
		{
			if (ft_strncmp(ptr1->content, ptr1->next->content,
				ft_strlen(ptr1->content)) > 0)
			{
				tmp = ptr1->content;
				ptr1->content = ptr1->next->content;
				ptr1->next->content = tmp;
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

void	add_dquote(char *new, char *line)
{
	int i;

	i = 0;
	while (new[i])
	{
		if (new[i] == '=')
		{
			i++;
			new[i] = '\"';
			i++;
			if (new[i])
			{
				while (new[i])
				{
					new[i] = line[i - 1];
					i++;
				}
				new[i] = line[i - 1];
				i++;
			}
			new[i] = '\"';
			new[i + 1] = '\0';
		}
		i++;
	}
}

void	print_export(char *line)
{
	char	*new;

	new = (char *)malloc(sizeof(char) * ft_strlen(line) + 3);
	if (!new)
		exit(-1);
	ft_strlcpy(new, line, ft_strlen(line) + 1);
	add_dquote(new, line);
	ft_putstr_fd("declare -x ", STDOUT);
	ft_putstr_fd(new, STDOUT);
	ft_putstr_fd("\n", STDOUT);
	free(new);
	g_exit_status = 0;
}

void	exec_export_p(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
	t_list	*export_tmp;
	int		argc;

	argc = get_argc(cmd, prev_pipe_idx, pipe_idx);
	if (argc == 1)
	{
		export_tmp = g_env_list;
		sort_export(&export_tmp);
		while (export_tmp)
		{
			print_export((char *)export_tmp->content);
			export_tmp = export_tmp->next;
		}
	}
	exit(0);
}
