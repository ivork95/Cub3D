#include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../includes/cub3d.h"

int worldMap1[mapHeight][mapWidth]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	my_mlx_pixel_put(t_win *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

t_settings *init_window(void)
{
	t_settings *data;

	data = malloc(sizeof(t_settings));
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, screenWidth, screenHeight, "Hello world!");
	data->img.img = mlx_new_image(data->mlx, screenWidth, screenHeight);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length,
								&data->img.endian);
	return (data);
}

void	init_player(t_settings *data)
{
	data->posX = 320;
	data->posY = 360;
	data->dirX = -1;
	data->dirY = 0;
	data->deltaX = 0;
	data->deltaY = 0;
	data->angle = 2 * PI;
	data->planeX = 0;
	data->planeY = 0.66;
}

void	create_top_view(t_settings *data)
{
	int x;
	int y;

	x = 0;
	while (x < screenWidth)
	{
		y = 0;
		while (y < screenHeight)
		{
			int type = (data->map)[y / 26][x / 26];
			if (type != 0 && x)
				my_mlx_pixel_put(&data->img, x, y, 0x00FFFFFF);
			else

				my_mlx_pixel_put(&data->img, x, y, 0x00000000);
			if (x % 26 == 0 || y % 26 == 0)
				my_mlx_pixel_put(&data->img, x, y, 0x00808080);
			y++;
		}
		x++;
	}
}

void draw_sky(t_settings *data)
{
	for(int x = 0; x < screenHeight; x += 1)
	{
		for (int y = 0; y < screenWidth / 2; y++)
				my_mlx_pixel_put(&data->img, x, y, 0x0000FFFF);
	}
}

void draw_ground(t_settings *data)
{
	for(int x = 0; x < screenHeight; x += 1)
	{
		for (int y = 0; y < screenWidth / 2; y++)
				my_mlx_pixel_put(&data->img, x, screenWidth - y, 0x00A0522D);
	}
}

void draw_player(t_settings *data)
{
	int x1;
	int y1;

	// draw_line(data, data->angle, 250, 0x00FF0000);
	for(int i = 0; i < 360; i += 1)
    {
		for (int r = 0; r < 6; r++)
		{
            x1 = r * cos(i * PI / 180);
            y1 = r * sin(i * PI / 180);
            my_mlx_pixel_put(&data->img, data->posX + x1, data->posY + y1, 0x00ffff00);
      	}
	}
	draw_line(data, data->angle, 50, 0x00ffff00);
}

double get_ray_length_y(t_settings *data, double angle)
{
	int	j;
	double ray_length;
	double rad;
	int nextY;
	int nextX;
	int deltaY;
	int deltaX;

	j = 0;
	while (j < mapHeight)
	{
		if (angle == 1.5 * PI || angle == 0.5 * PI)
		{
			ray_length = 100000000;
			j++;
			continue ; 
		}
		if (0.5 * PI < angle && angle < 1.5 * PI)
		{
			nextY = (((((int)data->posY / (screenHeight / mapHeight))) - 0.0001) - j) * (screenHeight / mapHeight);
			rad = angle - PI;
			nextX = data->posX - tan(rad) * abs((int)data->posY - nextY);
			// if (j != 0)
			// 	nextY += y_off;
			// nextX = data->posX - (j * TAN + x_off);
		}
		else
		{
			nextY = ((int)data->posY / (screenHeight / mapHeight) + 1 + j) * (screenHeight / mapHeight);
			rad = angle;
			nextX = data->posX + tan(rad) * abs((int)data->posY - nextY);
			// if (j != 0)
			// 	nextY += y_off;
			// nextX = data->posX + (j * TAN + x_off);
		}
		deltaX = abs((int)data->posX - nextX); 
		deltaY = abs((int)data->posY - nextY);
		ray_length = sqrt(deltaX * deltaX + deltaY * deltaY);
		if (nextX >= 0 && nextX <= 624 && nextY >= 0 && nextY <= 624)
		{
			if (worldMap1[nextY / 26][nextX / 26] != 0)
				break ;
		}
		ray_length = 1000000000;
		j++;
	}
	return (ray_length);
}

double get_ray_length_x(t_settings *data, double angle)
{
	int	z;
	double ray_length;
	double rad;
	int nextY;
	int nextX;
	int deltaY;
	int deltaX;

	z = 0;
	while (z < mapWidth)
	{
		if (angle == 2 * PI || angle == 0)
		{
			z++;	
			ray_length = 10000000;
			continue ;
		}
		if (angle > PI)
		{
			nextX = (((((int)data->posX / (screenHeight / mapHeight)) - z) - 0.0001)) * (screenHeight / mapHeight);
			rad = 2 * PI - angle;
			nextY = data->posY + abs((int)data->posX - nextX) / tan(rad);
		}
		else
		{
			nextX = ((int)data->posX / (screenHeight / mapHeight) + z + 1) * (screenHeight / mapHeight);
			rad = angle;
			nextY = data->posY + abs((int)data->posX - nextX) / tan(rad);
		}
		deltaX = abs((int)data->posX - nextX); 
		deltaY = abs((int)data->posY - nextY);
		ray_length = sqrt(deltaX * deltaX + deltaY * deltaY);
		if (nextX > 0 && nextX < 624 && nextY > 0 && nextY < 624)
		{
			if (worldMap1[nextY / 26][nextX / 26] != 0)
				break ;
		}
		ray_length = 10000000;
		z++;
	}
	return (ray_length);
}