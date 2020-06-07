#include "./main.h"

int worldMap[mapWidth][mapHeight] =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 2, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
		{1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1},
		{1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
		{1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1},
		{1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1},
		{1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 5, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int setSideDist(t_mlx *mlx)
{
	if (mlx->game.rayDirX < 0)
	{
		mlx->game.stepX = -1;
		mlx->game.sideDistX = (mlx->game.posX - mlx->game.mapX) * mlx->game.deltaDistX;
	}
	else
	{
		mlx->game.stepX = 1;
		mlx->game.sideDistX = (mlx->game.mapX + 1.0 - mlx->game.posX) * mlx->game.deltaDistX;
	}
	if (mlx->game.rayDirY < 0)
	{
		mlx->game.stepY = -1;
		mlx->game.sideDistY = (mlx->game.posY - mlx->game.mapY) * mlx->game.deltaDistY;
	}
	else
	{
		mlx->game.stepY = 1;
		mlx->game.sideDistY = (mlx->game.mapY + 1.0 - mlx->game.posY) * mlx->game.deltaDistY;
	}
	return 0;
}

int setVar(t_mlx *mlx, int i)
{
	mlx->game.cameraX = 2 * i / (double)WIN_WIDTH - 1;
	mlx->game.rayDirX = mlx->game.dirX + mlx->game.planeX * mlx->game.cameraX;
	mlx->game.rayDirY = mlx->game.dirY + mlx->game.planeY * mlx->game.cameraX;
	mlx->game.mapX = (int)mlx->game.posX;
	mlx->game.mapY = (int)mlx->game.posY;
	mlx->game.deltaDistX = (mlx->game.rayDirY == 0) ? 0 : ((mlx->game.rayDirX == 0) ? 1 : fabs(1 / mlx->game.rayDirX));
	mlx->game.deltaDistY = (mlx->game.rayDirX == 0) ? 0 : ((mlx->game.rayDirY == 0) ? 1 : fabs(1 / mlx->game.rayDirY));
	mlx->game.hit = 0;
	setSideDist(mlx);
	return 0;
}

void setDraw(t_mlx *mlx)
{
	mlx->game.lineHeight = (int)(WIN_HEIGHT / mlx->game.perpWallDist);
	mlx->game.drawStart = -mlx->game.lineHeight / 2 + WIN_HEIGHT / 2;
	if (mlx->game.drawStart < 0)
		mlx->game.drawStart = 0;
	mlx->game.drawEnd = mlx->game.lineHeight / 2 + WIN_HEIGHT / 2;
	if (mlx->game.drawEnd >= WIN_HEIGHT)
		mlx->game.drawEnd = WIN_HEIGHT - 1;
}

int performDDA(t_mlx *mlx)
{
	while (mlx->game.hit == 0)
	{
		if (mlx->game.sideDistX < mlx->game.sideDistY)
		{
			mlx->game.sideDistX += mlx->game.deltaDistX;
			mlx->game.mapX += mlx->game.stepX;
			mlx->game.side = 0;
		}
		else
		{
			mlx->game.sideDistY += mlx->game.deltaDistY;
			mlx->game.mapY += mlx->game.stepY;
			mlx->game.side = 1;
		}
		if (worldMap[mlx->game.mapX][mlx->game.mapY] > 0)
			mlx->game.hit = 1;
	}
	if (mlx->game.side == 0)
		mlx->game.perpWallDist = (mlx->game.mapX - mlx->game.posX + (1 - mlx->game.stepX) / 2) / mlx->game.rayDirX;
	else
		mlx->game.perpWallDist = (mlx->game.mapY - mlx->game.posY + (1 - mlx->game.stepY) / 2) / mlx->game.rayDirY;
	setDraw(mlx);
}

int get_side(t_mlx *mlx)
{
	int wall_side;

	if (mlx->game.side == 0 && mlx->game.rayDirX > 0)
		wall_side = NORTH;
	if (mlx->game.side == 0 && mlx->game.rayDirX < 0)
		wall_side = SOUTH;
	if (mlx->game.side == 1 && mlx->game.rayDirY > 0)
		wall_side = EAST;
	if (mlx->game.side == 1 && mlx->game.rayDirY < 0)
		wall_side = WEST;
	return (wall_side);
}

int drawVertLine(t_mlx *mlx, int i)
{
	int texNum = worldMap[mlx->game.mapX][mlx->game.mapY] - 1;
	double wallX;
	if (mlx->game.side == 0)
		wallX = mlx->game.posY + mlx->game.perpWallDist * mlx->game.rayDirY;
	else
		wallX = mlx->game.posX + mlx->game.perpWallDist * mlx->game.rayDirX;
	wallX -= floor(wallX);

	int texX = (int)(wallX * (double)TEX_WIDTH);
	if (mlx->game.side == 0 && mlx->game.rayDirX > 0)
		texX = TEX_WIDTH - texX - 1;
	if (mlx->game.side == 1 && mlx->game.rayDirX < 0)
		texX = TEX_WIDTH - texX - 1;

	double step = 1.0 * TEX_HEIGHT / mlx->game.lineHeight;
	double texPos = (mlx->game.drawStart - WIN_HEIGHT / 2 + mlx->game.lineHeight / 2) * step;

	int wall_side = get_side(mlx);
	while (mlx->game.drawStart < mlx->game.drawEnd)
	{
		int texY = (int)texPos & (TEX_HEIGHT - 1);
		texPos += step;
		int color = mlx->tex[wall_side].data[TEX_HEIGHT * texY + texX];
		/* shading? */
		mlx->img.data[i + WIN_WIDTH * mlx->game.drawStart] = color;
		mlx->game.drawStart++;
	}
	printf("aa %f\n", mlx->sprite[1].y);
}

int key_press(t_mlx *mlx)
{
	double moveSpeed = 0.018; //the constant value is in squares/second
	double rotSpeed = 0.009;  //the constant value is in radians/second
	// move forward if no wall in front of you
	if (mlx->game.move_f == 1)
	{
		printf("Moving forward\n");
		if (worldMap[(int)(mlx->game.posX + mlx->game.dirX * moveSpeed)][(int)mlx->game.posY] == 0)
			mlx->game.posX += mlx->game.dirX * moveSpeed;
		if (worldMap[(int)mlx->game.posX][(int)(mlx->game.posY + mlx->game.dirY * moveSpeed)] == 0)
			mlx->game.posY += mlx->game.dirY * moveSpeed;
	}
	//move backwards if no wall behind you
	if (mlx->game.move_b == 1)
	{
		printf("Moving backward\n");
		if (worldMap[(int)(mlx->game.posX - mlx->game.dirX * moveSpeed)][(int)mlx->game.posY] == 0)
			mlx->game.posX -= mlx->game.dirX * moveSpeed;
		if (worldMap[(int)mlx->game.posX][(int)(mlx->game.posY - mlx->game.dirY * moveSpeed)] == 0)
			mlx->game.posY -= mlx->game.dirY * moveSpeed;
	}
	//move to the right
	if (mlx->game.move_r == 1)
	{
		printf("moving right\n");
		if (worldMap[(int)(mlx->game.posX + mlx->game.planeX * 0.01)][(int)mlx->game.posY] == 0)
			mlx->game.posX += mlx->game.planeX * 0.01;
		if (worldMap[(int)mlx->game.posX][(int)(mlx->game.posY + mlx->game.planeY * 0.01)] == 0)
			mlx->game.posY += mlx->game.planeY * 0.01;
	}
	//rotate to the right
	if (mlx->game.rotate_r == 1)
	{
		printf("turning right\n");
		//both camera direction and camera plane must be rotated
		double oldDirX = mlx->game.dirX;
		mlx->game.dirX = mlx->game.dirX * cos(-rotSpeed) - mlx->game.dirY * sin(-rotSpeed);
		mlx->game.dirY = oldDirX * sin(-rotSpeed) + mlx->game.dirY * cos(-rotSpeed);
		double oldPlaneX = mlx->game.planeX;
		mlx->game.planeX = mlx->game.planeX * cos(-rotSpeed) - mlx->game.planeY * sin(-rotSpeed);
		mlx->game.planeY = oldPlaneX * sin(-rotSpeed) + mlx->game.planeY * cos(-rotSpeed);
	}
	//move to the left
	if (mlx->game.move_l == 1)
	{
		printf("moving left\n");
		if (worldMap[(int)(mlx->game.posX - mlx->game.planeX * 0.01)][(int)mlx->game.posY] == 0)
			mlx->game.posX -= mlx->game.planeX * 0.01;
		if (worldMap[(int)mlx->game.posX][(int)(mlx->game.posY - mlx->game.planeY * 0.01)] == 0)
			mlx->game.posY -= mlx->game.planeY * 0.01;
	}
	//rotate to the left
	if (mlx->game.rotate_l == 1)
	{
		printf("turning left\n");
		//both camera direction and camera plane must be rotated
		double oldDirX = mlx->game.dirX;
		mlx->game.dirX = mlx->game.dirX * cos(rotSpeed) - mlx->game.dirY * sin(rotSpeed);
		mlx->game.dirY = oldDirX * sin(rotSpeed) + mlx->game.dirY * cos(rotSpeed);
		double oldPlaneX = mlx->game.planeX;
		mlx->game.planeX = mlx->game.planeX * cos(rotSpeed) - mlx->game.planeY * sin(rotSpeed);
		mlx->game.planeY = oldPlaneX * sin(rotSpeed) + mlx->game.planeY * cos(rotSpeed);
	}
	return 0;
}

int draw_floor_ceiling(t_mlx *mlx)
{
	int y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		// rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		float rayDirX0 = mlx->game.dirX - mlx->game.planeX;
		float rayDirY0 = mlx->game.dirY - mlx->game.planeY;
		float rayDirX1 = mlx->game.dirX + mlx->game.planeX;
		float rayDirY1 = mlx->game.dirY + mlx->game.planeY;
		// Current y position compared to the center of the screen (the horizon)
		int p = y - WIN_HEIGHT / 2;
		// Vertical position of the camera.
		float posZ = 0.5 * WIN_HEIGHT;
		// Horizontal distance from the camera to the floor for the current row.
		// 0.5 is the z position exactly in the middle between floor and ceiling.
		float rowDistance = posZ / p;
		// calculate the real world step vector we have to add for each x (parallel to camera plane)
		// adding step by step avoids multiplications with a weight in the inner loop
		float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / WIN_WIDTH;
		float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / WIN_WIDTH;
		// real world coordinates of the leftmost column. This will be updated as we step to the right.
		float floorX = mlx->game.posX + rowDistance * rayDirX0;
		float floorY = mlx->game.posY + rowDistance * rayDirY0;

		for (int x = 0; x < WIN_WIDTH; ++x)
		{
			// the cell coord is simply got from the integer parts of floorX and floorY
			int cellX = (int)floorX;
			int cellY = (int)floorY;

			// get the texture coordinate from the fractional part
			int tx = (int)(TEX_WIDTH * (floorX - cellX)) & (TEX_WIDTH - 1);
			int ty = (int)(TEX_HEIGHT * (floorY - cellY)) & (TEX_HEIGHT - 1);

			floorX += floorStepX;
			floorY += floorStepY;

			int color;
			// floor
			color = mlx->tex[FLOOR].data[TEX_WIDTH * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker
			mlx->img.data[x + WIN_WIDTH * y] = color;

			//ceiling (symmetrical, at screenHeight - y - 1 instead of y)
			color = mlx->tex[CEILING].data[TEX_WIDTH * ty + tx];
			color = (color >> 1) & 8355711; // make a bit darker
			mlx->img.data[x + WIN_WIDTH * (WIN_HEIGHT - y - 1)] = color;
		}
		y++;
	}
}

int run_game(t_mlx *mlx)
{
	int i;

	i = 0;
	mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	draw_floor_ceiling(mlx);
	if (mlx->game.move_f || mlx->game.move_b || mlx->game.move_r || mlx->game.move_l || mlx->game.rotate_r || mlx->game.rotate_l)
		key_press(mlx);
	while (i < WIN_WIDTH)
	{
		setVar(mlx, i);
		performDDA(mlx);
		drawVertLine(mlx, i);
		i++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	return 0;
}

int key_press2(int key, t_mlx *mlx)
{
	if (key == KEY_W)
		mlx->game.move_f = 1;
	if (key == KEY_S)
		mlx->game.move_b = 1;
	if (key == KEY_A)
		mlx->game.move_l = 1;
	if (key == KEY_D)
		mlx->game.move_r = 1;
	if (key == KEY_LEFT)
		mlx->game.rotate_l = 1;
	if (key == KEY_RIGHT)
		mlx->game.rotate_r = 1;
}

int key_release(int key, t_mlx *mlx)
{
	if (key == KEY_W)
		mlx->game.move_f = 0;
	if (key == KEY_S)
		mlx->game.move_b = 0;
	if (key == KEY_A)
		mlx->game.move_l = 0;
	if (key == KEY_D)
		mlx->game.move_r = 0;
	if (key == KEY_LEFT)
		mlx->game.rotate_l = 0;
	if (key == KEY_RIGHT)
		mlx->game.rotate_r = 0;
}

void tmp_direction_tex(t_mlx *mlx)
{
	int a = 64;
	int b = 64;
	mlx->tex[EAST].filepath = "./textures/mossy.xpm";
	mlx->tex[WEST].filepath = "./textures/choga.xpm";
	mlx->tex[SOUTH].filepath = "./textures/greystone.xpm";
	mlx->tex[NORTH].filepath = "./textures/wood.xpm";
	mlx->tex[CEILING].filepath = "./textures/redbrick.xpm";
	mlx->tex[FLOOR].filepath = "./textures/bluestone.xpm";
	mlx->tex[SPRITE].filepath = "./textures/barrel.xpm";
	mlx->tex[EAST].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/mossy.xpm", &a, &b);
	mlx->tex[WEST].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/choga.xpm", &a, &b);
	mlx->tex[SOUTH].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/greystone.xpm", &a, &b);
	mlx->tex[NORTH].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/wood.xpm", &a, &b);
	mlx->tex[CEILING].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/redbrick.xpm", &a, &b);
	mlx->tex[FLOOR].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/bluestone.xpm", &a, &b);
	mlx->tex[SPRITE].img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, "./textures/barrel.xpm", &a, &b);
	mlx->tex[EAST].data = (int *)mlx_get_data_addr(mlx->tex[EAST].img_ptr, &mlx->tex[EAST].bpp, &mlx->tex[EAST].size_l, &mlx->tex[EAST].endian);
	mlx->tex[WEST].data = (int *)mlx_get_data_addr(mlx->tex[WEST].img_ptr, &mlx->tex[WEST].bpp, &mlx->tex[WEST].size_l, &mlx->tex[WEST].endian);
	mlx->tex[SOUTH].data = (int *)mlx_get_data_addr(mlx->tex[SOUTH].img_ptr, &mlx->tex[SOUTH].bpp, &mlx->tex[SOUTH].size_l, &mlx->tex[SOUTH].endian);
	mlx->tex[NORTH].data = (int *)mlx_get_data_addr(mlx->tex[NORTH].img_ptr, &mlx->tex[NORTH].bpp, &mlx->tex[NORTH].size_l, &mlx->tex[NORTH].endian);
	mlx->tex[CEILING].data = (int *)mlx_get_data_addr(mlx->tex[CEILING].img_ptr, &mlx->tex[CEILING].bpp, &mlx->tex[CEILING].size_l, &mlx->tex[CEILING].endian);
	mlx->tex[FLOOR].data = (int *)mlx_get_data_addr(mlx->tex[FLOOR].img_ptr, &mlx->tex[FLOOR].bpp, &mlx->tex[FLOOR].size_l, &mlx->tex[FLOOR].endian);
	mlx->tex[SPRITE].data = (int *)mlx_get_data_addr(mlx->tex[SPRITE].img_ptr, &mlx->tex[SPRITE].bpp, &mlx->tex[SPRITE].size_l, &mlx->tex[SPRITE].endian);
}

int initial_setting(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "DomMorello");
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp, &mlx->img.size_l, &mlx->img.endian);
	mlx->game.posX = 21.5;
	mlx->game.posY = 11.5;
	mlx->game.dirX = -1;
	mlx->game.dirY = 0;
	mlx->game.planeX = 0;
	mlx->game.planeY = 0.66;
	tmp_direction_tex(mlx); //일단 하드코딩으로 filepath를 넣어줬다.
	//sprite 일단 hardcoding으로
	// t_sprite tmp[2];
	// mlx->sprite = &tmp;
	mlx->sprite[0].x = 11.5;
	mlx->sprite[0].y = 9;
	mlx->sprite[1].x = 10.5;
	mlx->sprite[1].y = 10;
	// 이게 어떻게 가능한거지..? 메모리 크기도 할당하지 않았는데 값이 대입이 된다.
	// 그리고 위에 tmp로 해서 포인터를 대입해서 값을 넣으면 왜 위에서는 값을 기억 못하고 있찌?
	// 이 부분을 해결해야 다음 단계로 넘어갈 수 있다. 
	
	return 0;
}

int main(int argc, char const *argv[])
{
	t_mlx mlx;

	/* parsing map info */
	initial_setting(&mlx);
	mlx_hook(mlx.win_ptr, 2, 1L << 0, key_press2, &mlx);
	mlx_hook(mlx.win_ptr, 3, 1L << 1, key_release, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, run_game, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return 0;
}
