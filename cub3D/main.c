#include "./main.h"

int worldMap[mapWidth][mapHeight] =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int		key_press(int key, void *param)
{
	printf("input keyCode: %d\n", key);
	return (0);
}

int main()
{
	t_mlx mlx;
	int (*test)() = key_press;

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "DomMorello");
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l, &mlx.img.endian);

	double posX = 22, posY = 12;	  //x and y start position
	double dirX = -1, dirY = 0;		  //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	double time = 0;	//time of current frame
	double oldTime = 0; //time of previous frame
	int flag = 1;

	while (flag)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			//calculate ray position and direction
			double cameraX = 2 * x / (double)WIN_WIDTH - 1; //x-coordinate in camera space
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;
			//which box of the map we're in
			int mapX = (int)posX;
			int mapY = (int)posY;

			//length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;

			//length of ray from one x or y-side to next x or y-side
			double deltaDistX = fabs(1 / rayDirX);
			double deltaDistY = fabs(1 / rayDirY);
			double perpWallDist;

			//what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; //was there a wall hit?
			int side;	 //was a NS or a EW wall hit?
			//calculate step and initial sideDist
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
			}
			//perform DDA
			while (hit == 0)
			{
				//jump to next map square, OR in x-direction, OR in y-direction
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				//Check if ray has hit a wall
				if (worldMap[mapX][mapY] > 0)
				{
					hit = 1;
					flag = 0;
				}
			}
			//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
			if (side == 0)
				perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
			else
				perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

			//Calculate height of line to draw on screen
			int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
			if (drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
			if (drawEnd >= WIN_HEIGHT)
				drawEnd = WIN_HEIGHT - 1;

			int color;

			//choose wall color
			switch (worldMap[mapX][mapY])
			{
			case 1:
				color = 0xFF0000;
				break; //red
			case 2:
				color = 0x00FF00;
				break; //green
			case 3:
				color = 0x0000FF;
				break; //blue
			case 4:
				color = 0xFFFFFF;
				break; //white
			default:
				color = 0xFFEB5A;
				break; //yellow
			}

			//give x and y sides different brightness
			if (side == 1)
			{
				color = color / 2;
			}

			//draw the pixels of the stripe as a vertical line
			// verLine(mlx, x, drawStart, drawEnd, color);	//�Ű����� 5���� �ϴ� �Լ�ȭ���� �ʾ���
			while (drawStart <= drawEnd)
			{
				mlx.img.data[x + WIN_WIDTH * drawStart] = color;
				drawStart++;
			}

			
		}
		// //speed modifiers
		// double moveSpeed = 10 * 5.0; //the constant value is in squares/second
		// double rotSpeed = 10 * 3.0;	//the constant value is in radians/second
		// readKeys();
		// //move forward if no wall in front of you
		// if (keyDown(SDLK_UP))
		// {
		// 	if (worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false)
		// 		posX += dirX * moveSpeed;
		// 	if (worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false)
		// 		posY += dirY * moveSpeed;
		// }
		// //move backwards if no wall behind you
		// if (keyDown(SDLK_DOWN))
		// {
		// 	if (worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false)
		// 		posX -= dirX * moveSpeed;
		// 	if (worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false)
		// 		posY -= dirY * moveSpeed;
		// }
		// //rotate to the right
		// if (keyDown(SDLK_RIGHT))
		// {
		// 	//both camera direction and camera plane must be rotated
		// 	double oldDirX = dirX;
		// 	dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		// 	dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		// 	double oldPlaneX = planeX;
		// 	planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		// 	planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
		// }
		// //rotate to the left
		// if (keyDown(SDLK_LEFT))
		// {
		// 	//both camera direction and camera plane must be rotated
		// 	double oldDirX = dirX;
		// 	dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		// 	dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		// 	double oldPlaneX = planeX;
		// 	planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		// 	planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
		// }
	}

	mlx_key_hook(mlx.win_ptr, test, 0);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img.img_ptr, 0, 0);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}