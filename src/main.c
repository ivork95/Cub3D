#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define mapWidth 24
#define mapHeight 24
#define texWidth 64
#define texHeight 64
#define screenWidth 624
#define screenHeight 624
#define UP 13
#define DOWN 1
#define LEFT 0
#define RIGHT 2
#define PI 3.141592653
#define FOV 70
#define RAD 0.0174532925
#define ROTATE_L 123
#define ROTATE_R 124

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

typedef struct	s_win {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_win;

typedef struct	s_settings {
	double posX;
	double posY;
	double dirX;
	double dirY;
	double deltaX;
	double deltaY;
	double angle;
	double planeX;
	double planeY;
	void			*mlx;
	void			*win;
	t_win			img;
}				t_settings;


void	my_mlx_pixel_put(t_win *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

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
	// horizontal
	for(int i = 0; i < screenWidth; i += 1)
	{
		angle = data->angle + ((float)FOV / 2 - ((float)i / screenWidth * FOV)) * RAD;
		if (angle > 2 * PI)
			angle -= 2 * PI;
		if (angle < 0)
			angle += 2 * PI;
		for (int z = 0; z < mapHeight; z += 1)
		{
			if (angle == 1.5 * PI || angle == 0.5 * PI)
				continue ; 
			if (0.5 * PI < angle && angle < 1.5 * PI)
			{
				nextY = (((((int)data->posY / (screenHeight / mapHeight)) - z) - 0.0001)) * (screenHeight / mapHeight);
				rad = angle - PI;
				nextX = data->posX - tan(rad) * abs((int)data->posY - nextY);
			}
			else
			{
				nextY = ((int)data->posY / (screenHeight / mapHeight) + z + 1) * (screenHeight / mapHeight);
				rad = angle;
				nextX = data->posX + tan(rad) * abs((int)data->posY - nextY);
			}
			deltaX = abs((int)data->posX - nextX); 
			deltaY = abs((int)data->posY - nextY);
			ray_length_y = sqrt(deltaX * deltaX + deltaY * deltaY);
			if (nextX > 0 && nextX < 624 && nextY > 0 && nextY < 624)
			{
				if (worldMap[nextY / 26][nextX / 26] != 0)
					break ;
			}
			ray_length_y = 1000000000;
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
		int line_heigth = (26 * 624) / shortest;
		if (line_heigth > 624)
			line_heigth = 624;
		for (int z = 0; z < screenHeight; z++)
		{
			if (screenHeight - z <  (screenHeight + line_heigth) / 2)
			{
				for (int ir = 0; ir < line_heigth; ir++)
					my_mlx_pixel_put(&data->img, i, screenHeight - z - ir, 0x00F0F0D3);
				z = screenHeight;
				break ;
			}
		}
		// draw_line(data, angle, shortest, 0x00FF0000);
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

int	plot_frame(t_settings *data)
{
	// for (int x = 0; x < screenWidth; x++)
	// {
	// 	for (int y = 0; y < screenHeight ; y++)
	// 	{
	// 		int type = worldMap[y / 26][x / 26];
	// 		if (type != 0 && x)
	// 			my_mlx_pixel_put(&data->img, x, y, 0x00FFFFFF);
	// 		else

	// 			my_mlx_pixel_put(&data->img, x, y, 0x00000000);
	// 		if (x % 26 == 0 || y % 26 == 0)
	// 			my_mlx_pixel_put(&data->img, x, y, 0x00808080);
	// 	}
	// }
	// draw_player(data);
	// draw_line(data, data->angle, 800, 0x00FF0000);
	draw_sky(data);
	draw_ground(data);
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
	void	*mlx;
	void	*mlx_win;
	t_win	img;
	t_settings *data;

	data = malloc(sizeof(t_settings));
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, screenWidth, screenHeight, "Hello world!");
	data->img.img = mlx_new_image(data->mlx, screenWidth, screenHeight);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length,
								&data->img.endian);
	data->posX = 320;
	data->posY = 360;
	data->dirX = -1;
	data->dirY = 0;
	data->deltaX = 0;
	data->deltaY = -5;
	data->angle = PI;
	data->planeX = 0;
	data->planeY = 0.66;
	plot_frame(data);

	// for (int x = 0; x < screenWidth; x++)
	// {
	// 	for (int y = 0; y < screenHeight ; y++)
	// 	{
	// 		int type = worldMap[y / 20][x / 26];
	// 		if (y / 20 == data.posY && x / 26 == data.posX)
	// 			my_mlx_pixel_put(&data.img, x, y, 0x00FF00FF);
	// 		else if (type != 0)
	// 			my_mlx_pixel_put(&data.img, x, y, 0x00FF0000);

	// 	}
	// }
	// mlx_put_image_to_window(data.mlx, data.win, data.img.img, 0, 0);
	mlx_key_hook(data->win, key_press, data);
	// mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(data->mlx);
}