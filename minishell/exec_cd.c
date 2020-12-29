/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:07:15 by donglee           #+#    #+#             */
/*   Updated: 2020/12/29 16:03:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
**	Updates key(2nd parameter) value to cwd(current directory). 
*/

void	update_env(char *cwd, char *key)
{
	t_list	*tmp;
	char	*new;

	tmp = g_env_list;
	if ((new = (char *)malloc(sizeof(char) *
		(ft_strlen(key) + ft_strlen(cwd)) + 1)) == NULL)
		exit(-1);
	ft_strlcpy(new, key, ft_strlen(key) + 1);
	ft_strlcat(new, cwd, ft_strlen(key) + ft_strlen(cwd) + 1);
	while (tmp)
	{
		if (!ft_strncmp(key, (char *)tmp->content, ft_strlen(key)))
		{
			free((char *)tmp->content);
			tmp->content = new;
		}
		tmp = tmp->next;
	}
}

/*
**	Checks if the argument is directory by using stat func.
**	Changes current directory to argument directory.
**	Updates OLDPWD, PWD path in environment variable.
*/

void	change_dir(char *dir, int is_pipe)
{
	struct stat	file;
	char		buf[BUF_SIZE];
	char		*cwd;

	cwd = getcwd(buf, sizeof(buf));
	if (!stat(dir, &file))
	{
		if (!is_pipe)
		{
			if (!chdir(dir))
			{
				update_env(cwd, OLDPWD);
				cwd = getcwd(buf, sizeof(buf));
				update_env(cwd, PWD2);
				g_exit_status = 0;
			}
			else
				print_err_not_dir(dir);
		}
	}
	else
		print_err_no_dir(dir);
}

/*
**	Finds HOME path in environment variables. 
*/

char	*find_home(void)
{
	t_list *env_tmp;

	env_tmp = g_env_list;
	while (env_tmp)
	{
		if (!ft_strncmp(HOME, env_tmp->content, ft_strlen(HOME)))
			return ((char *)env_tmp->content);
		env_tmp = env_tmp->next;
	}
	return (NULL);
}

/*
**	If user inputs "cd" without argument, finds HOME path
**	in environment variables and changes directory
**	to the HOME path if it exits.
**	Otherwise, prints error message and change exit status to 1.
*/

void	dir_to_home(int is_pipe)
{
	char *home;

	home = find_home();
	if (home)
	{
		home += ft_strlen(HOME);
		change_dir(home, is_pipe);
	}
	else
	{
		ft_putstr_fd("mongshell: cd: ", 2);
		ft_putstr_fd("HOME not found\n", 2);
		g_exit_status = 1;
	}
}

/*
**	Executes cd command. 
*/

void	exec_cd(char *cmd[], int prev_pipe_idx, int pipe_idx, int argc)
{
	int		is_pipe;
	char	*dir;

	(void)pipe_idx;
	if (prev_pipe_idx == 0)
		dir = cmd[prev_pipe_idx + 1];
	else
		dir = cmd[prev_pipe_idx + 2];
	is_pipe = find_pipe(cmd);
	if (argc == 1)
		dir_to_home(is_pipe);
	else
		change_dir(dir, is_pipe);
}
