/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_executable1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: donglee <donglee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 13:41:23 by donglee           #+#    #+#             */
/*   Updated: 2020/12/30 13:41:24 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

/*
**	gets all the paths from PATH in environment variables.
**	stores in the path(two dimensional array) and returns it.
*/

char	**get_path(void)
{
	char	*path;
	char	**ret;
	t_list	*env_tmp;

	path = NULL;
	ret = NULL;
	env_tmp = g_env_list;
	while (env_tmp)
	{
		if (!ft_strncmp(PATH, env_tmp->content, ft_strlen(PATH)))
		{
			path = env_tmp->content;
			break ;
		}
		env_tmp = env_tmp->next;
	}
	if (path)
	{
		path += ft_strlen(PATH);
		ret = ft_split(path, ':');
	}
	return (ret);
}

/*
**	Searches all paths in the PATH in environment variables.
*/

int		search_dir(char *token, char *path)
{
	struct dirent	*dir;
	DIR				*dir_p;

	if ((dir_p = opendir(path)))
	{
		dir = readdir(dir_p);
		while (dir)
		{
			if (!ft_strncmp(dir->d_name, token,
			ft_strlen(dir->d_name) > ft_strlen(token) ?
			ft_strlen(dir->d_name) : ft_strlen(token)))
				return (TRUE);
			dir = readdir(dir_p);
		}
		closedir(dir_p);
	}
	return (FALSE);
}

/*
**	If input is "ls", then this func append filepath before the "ls" and makes
**	"/bin/ls".
*/

void	cat_filepath(char **ret, char **tmp, char *token)
{
	if (*tmp)
	{
		ft_strlcat(*tmp, "/", ft_strlen(*tmp) + 2);
		*ret = (char *)malloc(sizeof(char) *
			(ft_strlen(*tmp) + ft_strlen(token) + 1));
		if (!*ret)
			exit(-1);
		*ret = *tmp;
		ft_strlcat(*ret, token, ft_strlen(token) + ft_strlen(*ret) + 1);
	}
	else
		*ret = token;
}

/*
**	To launch executable commands, gets filepath through the PATH
**	in environment variables.
**	To launch executable commands without path like 'ls' not '/bin/ls',
**	make filepath string in ret and returns it.
*/

char	*get_filepath(char *token, char **path)
{
	char	*tmp;
	char	*ret;
	int		i;

	tmp = NULL;
	ret = NULL;
	i = 0;
	while (path[i])
	{
		if (search_dir(token, path[i]))
		{
			tmp = path[i];
			break ;
		}
		i++;
	}
	cat_filepath(&ret, &tmp, token);
	free_2d_char(path);
	return (ret);
}

/*
**	handles executable commands like ls.
**	reads PATH in environment variables and if there's no PATH in it,
**	print error message and exit child process.
*/

void	handle_executable(char *token, char *cmd[],
	int prev_pipe_idx, int pipe_idx)
{
	char	**path;
	char	*filepath;

	path = get_path();
	if (!path)
	{
		ft_putstr_fd("mongshell: ", STDERR);
		ft_putstr_fd(token, STDERR);
		ft_putstr_fd(": No such file or directory\n", STDERR);
		exit(127);
	}
	filepath = get_filepath(token, path);
	if (prev_pipe_idx == 0)
		exec_executable(cmd, prev_pipe_idx, pipe_idx, filepath);
	else
		exec_executable2(cmd, prev_pipe_idx, pipe_idx, filepath);
}
