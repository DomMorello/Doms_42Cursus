/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 14:30:51 by donglee           #+#    #+#             */
/*   Updated: 2020/12/29 15:30:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
**	Finds "/usr/bin" path in PATH in environment variables.
**	If the env path exists, returns true.
*/

int		find_env_path(void)
{
	t_list	*env_tmp;
	char	*needle;
	int		is_path;

	is_path = FALSE;
	env_tmp = g_env_list;
	while (env_tmp)
	{
		if (!ft_strncmp(PATH, env_tmp->content, ft_strlen(PATH)))
		{
			is_path = TRUE;
			needle = ft_strnstr((char *)env_tmp->content, USRBIN,
				ft_strlen((char *)env_tmp->content));
			if (needle)
				return (TRUE);
		}
		env_tmp = env_tmp->next;
	}
	if (!is_path)
	{
		ft_putstr_fd("mongshell: env: command not found\n", STDERR);
		exit(127);
	}
	return (FALSE);
}

/*
**	Executes env command.
**	Only if there is /usr/bin path in PATH in environment variables, it works.
*/

void	exec_env(char *cmd[], int prev_pipe_idx, int pipe_idx)
{
	int		argc;
	t_list	*env_tmp;

	env_tmp = g_env_list;
	argc = get_argc(cmd, prev_pipe_idx, pipe_idx);
	if (argc == 1 && find_env_path())
	{
		while (env_tmp)
		{
			ft_putstr_fd((char *)env_tmp->content, STDOUT);
			ft_putstr_fd("\n", STDOUT);
			env_tmp = env_tmp->next;
		}
		exit(0);
	}
	if (argc == 1 && !find_env_path())
	{
		ft_putstr_fd("mongshell: env: command not found\n", STDERR);
		exit(127);
	}
	exit(0);
}
