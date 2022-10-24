#include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../includes/cub3d.h"

int worldMap[mapHeight][mapWidth]=
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

void draw_line(t_settings *data, double angle, int line_lenght, long color)
{
	int x1;
	int y1;

	for(int i = 0; i < line_lenght; i += 1)
    {
		x1 = i * sin(angle) + data->posX;
		y1 = i * cos(angle) + data->posY;
		if (x1 < screenWidth && x1 > 0  && y1 < screenHeight && y1 > 0)
			my_mlx_pixel_put(&data->img, x1, y1, color);
	}
	// printf("x value = %d, y value = %d\n", x1, y1);
}

void draw_line2(t_settings *data, double angle, int line_lenght, long color)
{
	int x1;
	int y1;
    
	for(int i = 0; i < line_lenght; i += 1)
    {
		x1 = i * sin(angle) + data->posX;
		y1 = i * cos(angle) + data->posY;
		if (x1 < screenWidth && x1 > 0  && y1 < screenHeight && y1 > 0)
			my_mlx_pixel_put(&data->img, x1, y1, color);
	}
	// printf("x value = %d, y value = %d\n", x1, y1);
}
void draw_point(t_settings *data, int x0, int y0)
{
	int x1;
	int y1;

	for(int i = 0; i < 360; i += 1)
	{
		for (int r = 0; r < 4; r++)
		{
			x1 = r * cos(i * PI / 180);
			y1 = r * sin(i * PI / 180);
			// if (0 <= x0 && x0 <= screenWidth)
			if (0 <= x0 + x1 && x0 + x1 <= screenWidth && 0 <= y0 + y1 && y0 + y1 <= screenHeight)
				my_mlx_pixel_put(&data->img, x0 + x1, y0 + y1, 0x00658354);
		}
	}
}

void draw_rays(t_settings *data)
{

	double angle;
	int nextY;
	int nextX;
	double rad;
	int ray_length_y;
	int ray_length_x;
	int deltaX;
	int deltaY;
	int iter;
	double y_off;
	double x_off;
	int i;
	int j;
	double TAN;
	// horizontal
	i = 0;
	while (i < screenWidth)
	{
		angle = data->angle + ((float)FOV / 2 - ((float)i / screenWidth * FOV)) * RAD;
		if (angle > 2 * PI)
			angle -= 2 * PI;
		if (angle < 0)
			angle += 2 * PI;
		if (0.5 * PI < angle && angle < 1.5 * PI)
		{
			nextY = (((((int)data->posY / (screenHeight / mapHeight))) - 0.0001)) * (screenHeight / mapHeight);
			rad = angle - PI;
			nextX = data->posX - tan(rad) * abs((int)data->posY - nextY);
			// printf("tan rad = %f\n", tan(rad));
			TAN = 26 * (tan(rad));
			y_off = -26;
			x_off = tan(rad) * abs((int)data->posY - nextY);
			// printf("x_off = %f\n", x_off);
			// printf("ATN = %f\n", TAN);

		}
		else
		{
			nextY = ((int)data->posY / (screenHeight / mapHeight) + 1) * (screenHeight / mapHeight);
			rad = angle;
			nextX = data->posX + tan(rad) * abs((int)data->posY - nextY);
			y_off = 26;
			TAN = 26 * (tan(rad));
			x_off = tan(rad) * abs((int)data->posY - nextY);
		}
		j = 0;
		while (j < mapHeight)
		{
			if (angle == 1.5 * PI || angle == 0.5 * PI)
			{
				ray_length_y = 1000000;
				continue ; 
			}
			if (0.5 * PI < angle && angle < 1.5 * PI)
			{
				nextY = (((((int)data->posY / (screenHeight / mapHeight))) - 0.0001)) * (screenHeight / mapHeight);
				rad = angle - PI;
				nextX = data->posX - tan(rad) * abs((int)data->posY - nextY);
				// if (j != 0)
				// 	nextY += y_off;
				// nextX = data->posX - (j * TAN + x_off);
			}
			else
			{
				if (j != 0)
					nextY += y_off;
				nextX = data->posX + (j * TAN + x_off);
			}
			deltaX = abs((int)data->posX - nextX); 
			deltaY = abs((int)data->posY - nextY);
			ray_length_y = sqrt(deltaX * deltaX + deltaY * deltaY);
			if (nextX >= 0 && nextX <= 624 && nextY >= 0 && nextY <= 624)
			{
				if (worldMap[nextY / 26][nextX / 26] != 0)
					break ;
			}
			ray_length_y = 1000000000;
			j++;
		}
		for (int z = 0; z < mapWidth; z += 1)
		{
			if (angle == 2 * PI || angle == 0)
				continue ;
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
			ray_length_x = sqrt(deltaX * deltaX + deltaY * deltaY);
			if (nextX > 0 && nextX < 624 && nextY > 0 && nextY < 624)
			{
				if (worldMap[nextY / 26][nextX / 26] != 0)
					break ;
			}
			ray_length_x = 10000000;
		}
		int shortest;
		if (ray_length_x < ray_length_y)
			shortest = ray_length_x;
		else
			shortest = ray_length_y;
		// int line_heigth = (26 * 624) / shortest;
		// if (line_heigth > 624)
		// 	line_heigth = 624;
		// for (int z = 0; z < screenHeight; z++)
		// {
		// 	if (screenHeight - z <  (screenHeight + line_heigth) / 2)
		// 	{
		// 		for (int ir = 0; ir < line_heigth; ir++)
		// 			my_mlx_pixel_put(&data->img, i, screenHeight - z - ir, 0x00F0F0D3);
		// 		z = screenHeight;
		// 		break ;
		// 	}
		// }

		//rays for top view
		draw_line(data, angle, shortest, 0x00FF0000);
		i++;
	}
}

int	plot_frame(t_settings *data)
{
	for (int x = 0; x < screenWidth; x++)
	{
		for (int y = 0; y < screenHeight ; y++)
		{
			int type = worldMap[y / 26][x / 26];
			if (x % 26 == 0 || y % 26 == 0)
				my_mlx_pixel_put(&data->img, x, y, 0x00808080);
			else if (type != 0 && x)
				my_mlx_pixel_put(&data->img, x, y, 0x00FFFFFF);
			else
				my_mlx_pixel_put(&data->img, x, y, 0x00000000);
		}
	}
	draw_player(data);
	// create_top_view(data);

	// draw_sky(data);
	// draw_ground(data);
	draw_rays(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (1);
}

int	key_press(int key_code, t_settings *data)
{
	// printf("key presse = %d\n", key_code);
	if (key_code == ROTATE_L)
	{
		data->angle += 0.1;
		if (data->angle > 2 * PI)
			data->angle -= 2 * PI;
		data->deltaX = sin(data->angle) * 5;
		data->deltaY = cos(data->angle) * 5;
	}
	if (key_code == ROTATE_R)
	{
		data->angle -= 0.1;
		if (data->angle < 0)
			data->angle += 2 * PI;
		data->deltaX = sin(data->angle) * 5;
		data->deltaY = cos(data->angle) * 5;
	}
	if (key_code == UP)
	{
		data->posY += data->deltaY;
		data->posX += data->deltaX;
	}
    if (key_code == DOWN)
	{
		data->posY -= data->deltaY;
		data->posX -= data->deltaX;
	}
	// if (key_code == LEFT)
	// {
	// 	data->posY += data->deltaY;
	// 	data->posX -= data->deltaX;
	// }
    // if (key_code == RIGHT)
	// {
	// 	data->posY -= data->deltaY;
	// 	data->posX -= data->deltaX;
	// }
	plot_frame(data);
	return (key_code);
}

int	main(void)
{
	t_settings *data;

	data = init_window();
	init_player(data);
	data->map = worldMap;
	plot_frame(data);
	mlx_key_hook(data->win, key_press, data);
	mlx_loop(data->mlx);
}