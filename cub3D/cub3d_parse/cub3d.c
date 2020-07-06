/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 01:39:33 by donglee           #+#    #+#             */
/*   Updated: 2020/07/06 16:24:09 by donglee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** the function allocates the string(copy) and return it
** exactly as much as 'size' from the end of the string(str)
** this is uesd for checking extension
*/

char	*ft_strfromend(char *str, int size)
{
	int		len;
	int		i;
	char	*copy;

	if ((copy = (char *)malloc(sizeof(char) * size + 1)) == NULL)
		return (NULL);
	len = ft_strlen(str);
	i = 0;
	while (size)
	{
		copy[i++] = str[len - size];
		size--;
	}
	copy[i] = '\0';
	return (copy);
}

/*
** Checks if the file extension is ".cub"
*/

void	check_extension(char const *argv, t_mlx *mlx)
{
	char *extension;

	if ((extension = ft_strfromend((char *)argv, 4)) == NULL)
		error(ERR_MEM, mlx);
	if (ft_strncmp(extension, ".cub", 5))
	{
		free(extension);
		error(ERR_EXT, mlx);
	}
	free(extension);
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->win_width,
									mlx->win_height, "DomMorello");
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->win_width,
													mlx->win_height);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp,
										&mlx->img.size_l, &mlx->img.endian);
}

/*
** main algorithm, key_press, key_release, and a red x button hooks
*/

void	mlx_event(t_mlx *mlx)
{
	mlx_hook(mlx->win_ptr, 2, 1L << 0, key_press, mlx);
	mlx_hook(mlx->win_ptr, 3, 1L << 1, key_release, mlx);
	mlx_hook(mlx->win_ptr, 17, 1L << 17, exit_hook, mlx);
	mlx_loop_hook(mlx->mlx_ptr, run_game, mlx);
	mlx_loop(mlx->mlx_ptr);
}

/*
** The main flow of the program
** first, initializes the members in the struct to NULL
** checks extension and starts parse the scene description file
** based on the result of parsing, inputs proper data in the variables
** runs the ray casting algorithm with the data from the file
*/

int		main(int argc, char const *argv[])
{
	t_mlx mlx;

	init_null(&mlx);
	if (argc != 2 && argc != 3)
		return (error_msg(ERR_TOOMANY));
	if (argv[1])
	{
		check_extension(argv[1], &mlx);
		if (parse_info(argv[1], &mlx) == ERROR)
			return (ERROR);
		init_game(&mlx);
		if (argv[2])
		{
			if (!ft_strncmp(argv[2], "--save", ft_strlen(argv[2])))
			{
				run_game(&mlx);
				save_bmp(&mlx);
			}
			else
				return (error(ERR_ARG, &mlx));
		}
		mlx_event(&mlx);
	}
	return (0);
}
