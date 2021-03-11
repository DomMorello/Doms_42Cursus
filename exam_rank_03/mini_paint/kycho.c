/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_mint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hycho <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 01:56:48 by hycho             #+#    #+#             */
/*   Updated: 2020/10/25 01:56:51 by hycho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
?
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
?
int ft_strlen(char *str)
{
	int	c;
?
	c = 0;
	while (*str++)
		c++;
	return (c);
}
?
int ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	return (0);
}
?
int	sq_dist(float x1, float y1, float x2, float y2)
{
	float dist_x;
	float dist_y;
?
	dist_x = (x1 - x2) * (x1 - x2);
	dist_y = (y1 - y2) * (y1 - y2);
	return (dist_x + dist_y);
}
?
int	is_paint(float x, float y, float radius, float x_axis, float y_axis)
{
	float dist;
?
	dist = sqrtf(sq_dist(x_axis, y_axis, x, y));
	dist = dist - radius;
	if (dist <= 0.000000000)
	{
		if (dist <= -1.00000000)
			return (2);
		return (1);
	}
	return (0);
}
?
int	main(int argc, char *argv[])
{
	// error check
	FILE	*file;
	int		c_width;
	int		c_height;
	char	c_color;
?
	// image malloc
	char	*image;
?
	//	read	6 elements
	int		read;	//fscanf시 EOF판단을 위해서 필요함
	char	symbol;
	float	x;
	float	y;
	float	radius;
	char	color;
?
	//	start point
	int		x_axis;
	int		y_axis;
?
	//	paint
	int		paint;
?
	if (argc != 2)
		return (ft_error("Error: argument\n"));
	if (!(file = fopen(argv[1], "r")))
		return (ft_error("Error: argument\n"));
	if (fscanf(file, "%d %d %c\n", &c_width, &c_height, &c_color) != 3)
		return (ft_error("Error: Operation file corrupted\n"));
	if (c_width <= 0 || c_width > 300 || c_height <= 0 || c_height > 300)
		return (ft_error("Error: Operation file corrupted\n"));
	image = (char *)malloc(sizeof(char) * (c_width * c_height));
	memset(image, c_color, (c_width * c_height));
	while ((read = fscanf(file, "%c %f %f %f %c\n", &symbol, &x, &y, &radius, &color)) == 5)
	{
		if ((symbol != 'C' && symbol != 'c') || radius <= 0)
		{
			free(image);
			return (ft_error("Error: Operation file corrupted\n"));
		}
		y_axis = 0;
		while (y_axis < c_height)
		{
			x_axis = 0;
			while (x_axis < c_width)
			{
				paint = is_paint(x, y, radius, (float)x_axis, (float)y_axis);
				if (paint == 1 || (paint && symbol == 'C'))//칠의 여부 지정
					image[y_axis * c_width + x_axis] = color;	
				x_axis++;
			}
			y_axis++;
		}
	}
	if (read != EOF)
	{
		free(image);
		return (ft_error("Error: Operation file corrupted\n"));
	}
	y_axis = 0;
	while (y_axis < c_height)
	{
		write(1, image + y_axis * c_width, c_width);
		write(1, "\n", 1);
		y_axis++;
	}
	free(image);
	fclose(file);
	return (0);
}