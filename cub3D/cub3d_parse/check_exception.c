/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exception.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:41:50 by donglee           #+#    #+#             */
/*   Updated: 2020/07/06 16:19:39 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** All the texture struct have to have a filapath(string)
** If the file has a RGB color like this: F 23 0  234 then the filepath will be
** "23 0  234" and it will be parsed properly later.
*/

void	check_tex(t_mlx *mlx)
{
	int i;

	i = 0;
	while (i < 7)
	{
		if (mlx->tex[i].filepath == NULL)
			error(ERR_FORMAT, mlx);
		i++;
	}
}

/*
** get_next_line function in the loop can't handle the last line in the loop
** So the last line of the file needs to be handled seperately
** with this function
*/

void	check_lastline(t_mlx *mlx, char *line)
{
	int		i;
	t_map	*new;

	new = NULL;
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '1')
		if (ft_lstaddmap_back(&mlx->maplst, new, ft_strdup(line)) == ERROR)
			error(ERR_MEM, mlx);
}
