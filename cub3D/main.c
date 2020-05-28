#include "./main.h"
#include <math.h>

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

typedef struct		s_game
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
}					t_game;

int key_press(int key, t_game *mola)
{
	static int i = 0;
	//speed modifiers
	double moveSpeed = 3; //the constant value is in squares/second
	double rotSpeed = 3;  //the constant value is in radians/second
	//move forward if no wall in front of you
	if (key == 65362)
	{
		if (worldMap[(int)(mola->posX + mola->dirX * moveSpeed)][(int)mola->posY] == 0)
			mola->posX += mola->dirX * moveSpeed;
		if (worldMap[(int)mola->posX][(int)(mola->posY + mola->dirY * moveSpeed)] == 0)
			mola->posY += mola->dirY * moveSpeed;
	}
	//move backwards if no wall behind you
	if (key == 65364)
	{
		if (worldMap[(int)(mola->posX - mola->dirX * moveSpeed)][(int)mola->posY] == 0)
			mola->posX -= mola->dirX * moveSpeed;
		if (worldMap[(int)mola->posX][(int)(mola->posY - mola->dirY * moveSpeed)] == 0)
			mola->posY -= mola->dirY * moveSpeed;
	}
	//rotate to the right
	if (key == 65363)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = mola->dirX;
		mola->dirX = mola->dirX * cos(-rotSpeed) - mola->dirY * sin(-rotSpeed);
		mola->dirY = oldDirX * sin(-rotSpeed) + mola->dirY * cos(-rotSpeed);
		double oldPlaneX = mola->planeX;
		mola->planeX = mola->planeX * cos(-rotSpeed) - mola->planeY * sin(-rotSpeed);
		mola->planeY = oldPlaneX * sin(-rotSpeed) + mola->planeY * cos(-rotSpeed);
	}
	//rotate to the left
	if (key == 65361)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = mola->dirX;
		mola->dirX = mola->dirX * cos(rotSpeed) - mola->dirY * sin(rotSpeed);
		mola->dirY = oldDirX * sin(rotSpeed) + mola->dirY * cos(rotSpeed);
		double oldPlaneX = mola->planeX;
		mola->planeX = mola->planeX * cos(rotSpeed) - mola->planeY * sin(rotSpeed);
		mola->planeY = oldPlaneX * sin(rotSpeed) + mola->planeY * cos(rotSpeed);
	}
	return (0);
}

int main()
{
	t_mlx mlx;
	t_game mola;

	// printf("%lu\n", sizeof(ptr));
	int (*test)(int, t_game *) = key_press;

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "DomMorello");
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx.img.data = (int *)mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bpp, &mlx.img.size_l, &mlx.img.endian);

	// double posX = 22, posY = 12;	  //x and y start position
	// double dirX = -1, dirY = 0;		  //initial direction vector
	// double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	mola.posX = 22;
	mola.posY = 12;
	mola.dirX = -1;
	mola.dirY = 0;
	mola.planeX = 0;
	mola.planeY = 0.66;

	int flag = 1;
	while (flag)
	{
		for (int x = 0; x < WIN_WIDTH; x++)
		{
			// //calculate ray position and direction
			// double cameraX = 2 * x / (double)WIN_WIDTH - 1; //x-coordinate in camera space
			// double rayDirX = dirX + planeX * cameraX;
			// double rayDirY = dirY + planeY * cameraX;
			// //which box of the map we're in
			// int mapX = (int)posX;
			// int mapY = (int)posY;

			//calculate ray position and direction
			double cameraX = 2 * x / (double)WIN_WIDTH - 1; //x-coordinate in camera space
			double rayDirX = mola.dirX + mola.planeX * cameraX;
			double rayDirY = mola.dirY + mola.planeY * cameraX;
			//which box of the map we're in
			int mapX = (int)mola.posX;
			int mapY = (int)mola.posY;			

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
				sideDistX = (mola.posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - mola.posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (mola.posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - mola.posY) * deltaDistY;
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
				perpWallDist = (mapX - mola.posX + (1 - stepX) / 2) / rayDirX;
			else
				perpWallDist = (mapY - mola.posY + (1 - stepY) / 2) / rayDirY;

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
			while (drawStart <= drawEnd)
			{
				mlx.img.data[x + WIN_WIDTH * drawStart] = color;
				drawStart++;
			}
			mlx_hook(mlx.win_ptr, 2, 1L<<0, key_press, &mola);
		}
	}
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img.img_ptr, 0, 0);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}