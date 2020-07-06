/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_tex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:43:37 by donglee           #+#    #+#             */
/*   Updated: 2020/07/06 16:24:39 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		which_tex(char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		return (NORTH);
	else if (line[0] == 'S' && line[1] == 'O')
		return (SOUTH);
	else if (line[0] == 'W' && line[1] == 'E')
		return (WEST);
	else if (line[0] == 'E' && line[1] == 'A')
		return (EAST);
	else if (line[0] == 'S')
		return (SPRITE);
	else if (line[0] == 'F')
		return (FLOOR);
	else if (line[0] == 'C')
		return (CEILING);
	else if (line[0] == 0 || line[0] == '1' || line[0] == 'R')
		return (PASS);
	else
		return (ERROR);
}

/*
** In the file, reads the texture part and stores the filepath
** in the struct of textures
*/

int		input_tex(t_mlx *mlx, int tex, char *line)
{
	int space;
	int i;

	i = 0;
	if (tex != ERROR && tex != PASS)
	{
		if (tex >= 0 && tex <= 3)
			space = 2;
		else
			space = 1;
		while (space--)
			i++;
		while (ft_isspace(line[i]))
			i++;
		if ((mlx->tex[tex].filepath = ft_strdup(&line[i])) == NULL)
			return (error(ERR_MEM, mlx));
	}
	return (TRUE);
}

/*
** The variable static int start_end will let the program know whether
** the get_next_line funtion starts to read map part of the file
** or it reads the last line of the map contents.
** If there is a empty line between map contents, returns an error.
** Checks if invalid letters is included in the map contents
** If there's no error in the map contents,
** copy the line in the list called maplst
*/

void	copy_map(t_mlx *mlx, char *line)
{
	int			i;
	t_map		*new;
	static int	start_end = 0;

	i = 0;
	new = NULL;
	while (ft_isspace(line[i]))
		i++;
	if ((start_end == 0 && line[i] == 0))
		return ;
	if (start_end == 1 && line[i] == 0)
		error(ERR_MAP_SUR, mlx);
	if (line[i] != '1')
		error(ERR_MAP_SUR, mlx);
	else
		start_end = 1;
	if (start_end == 1 && is_end_line(&line[i]))
		start_end = 0;
	while (line[i])
	{
		if (!is_valid_letter(line[i++]))
			error(ERR_LETTER, mlx);
	}
	if (ft_lstaddmap_back(&mlx->maplst, new, ft_strdup(line)) == ERROR)
		error(ERR_MEM, mlx);
}

/*
** In the map contents, only below letters are valid
*/

int		is_valid_letter(char c)
{
	if (c == '0' || c == '1' || c == '2' || c == 'N' ||
		c == 'S' || c == 'W' || c == 'E')
		return (TRUE);
	else if (ft_isspace(c) || c == '\r' || c == '\n')
		return (TRUE);
	return (FALSE);
}

/*
** Adds the new node to the end of the list
*/

int		ft_lstaddmap_back(t_map **lst, t_map *new, char *row)
{
	t_map *tmp;

	if (lst)
	{
		if ((new = ft_lstnewmap(row)) == NULL)
			return (ERROR);
		tmp = *lst;
		if (!tmp)
			*lst = new;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
	return (TRUE);
}
