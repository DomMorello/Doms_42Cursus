/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 13:41:46 by donglee           #+#    #+#             */
/*   Updated: 2020/12/31 12:43:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
**	sets redirection output.
*/

void	set_red_out(char *title)
{
	if ((g_red_out_fd = open(title, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR))
		!= ERROR)
	{
		dup2(g_red_out_fd, 1);
		close(g_red_out_fd);
	}
}

/*
**	sets redirection input.
*/

void	set_red_in(char *title, char *token, int is_process)
{
	struct stat file;

	if (!stat(title, &file))
	{
		if (S_ISDIR(file.st_mode))
		{
			ft_putstr_fd(token, 2);
			ft_putstr_fd(": (standard input): Is a directory\n", STDERR);
			g_exit_status = 1;
			if (is_process)
				exit(1);
		}
		else
		{
			if ((g_red_in_fd = open(title, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR))
				!= ERROR)
			{
				dup2(g_red_in_fd, 0);
				close(g_red_in_fd);
			}
		}
	}
	else
		print_error_red_in(title, is_process);
}

/*
**	sets redirection double output('>>').
*/

void	set_red_double_out(char *title)
{
	if ((g_red_out_fd = open(title, O_CREAT | O_RDWR | O_APPEND,
		S_IRUSR | S_IWUSR)) != ERROR)
	{
		dup2(g_red_out_fd, 1);
		close(g_red_out_fd);
	}
}

/*
**	it returns TRUE if token is redirection character.
*/

int		is_redirection(char *token)
{
	if (!ft_strncmp(token, ">", ft_strlen(token) > 1 ? ft_strlen(token) : 1) ||
		!ft_strncmp(token, ">>", ft_strlen(token) > 2 ? ft_strlen(token) : 2) ||
		!ft_strncmp(token, "<", ft_strlen(token) > 1 ? ft_strlen(token) : 1))
		return (TRUE);
	return (FALSE);
}

/*
**	when it finds redirection character in the tokens, sets the redirections.
*/

void	process_redirection(char *cmd[], int *prev_pipe_idx,
	int pipe_idx, int is_process)
{
	int		i;
	char	*token;

	i = *prev_pipe_idx;
	if (i == 0)
		token = cmd[i];
	else
		token = cmd[i + 1];
	while (cmd[i] && i < pipe_idx)
	{
		if (!ft_strncmp(cmd[i], ">", ft_strlen(cmd[i])
			> 1 ? ft_strlen(cmd[i]) : 1))
			set_red_out(cmd[i + 1]);
		if (!ft_strncmp(cmd[i], "<", ft_strlen(cmd[i])
			> 1 ? ft_strlen(cmd[i]) : 1))
			set_red_in(cmd[i + 1], token, is_process);
		if (!ft_strncmp(cmd[i], ">>", ft_strlen(cmd[i])
			> 2 ? ft_strlen(cmd[i]) : 2))
			set_red_double_out(cmd[i + 1]);
		i++;
	}
}
