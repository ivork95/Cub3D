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
#define UP 119
#define DOWN 115
#define LEFT 97
#define RIGHT 100
#define PI 3.141592653
#define FOV 70
#define RAD 0.0174532925

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
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
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
	printf("x value = %d, y value = %d\n", x1, y1);
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
	printf("x value = %d, y value = %d\n", x1, y1);
}

void draw_rays(t_settings *data)
{
	int x1;
	int y1;
	int ray_y;
	int ray_x;
	int dx;
	int dy;
	double angle;
	float y_offset;
	float x_offset;

	// for(int i = 0; i < FOV; i += 1)
	// {
	// 	angle = data->angle + (FOV / 2 - i) * RAD;
	// 	draw_line(data, angle, 600, 0x00AAFF00);
	// }
	int nextY;
	int x_off;
	int y_off;
	// horizontal
	if (data->angle > PI)
	{
		float Tan=tan(data->angle * PI / 180);
		//next y value; 300 <- 312
		ray_y = (int)data->posY / 26 * 26;
		ray_x = (data->posY - ray_y) * Tan + data->posX;
		x_off = 64; y_off = -x_off * Tan;
		printf("nextY = %d\n", ray_y);
		printf("nextX = %d\n", ray_x);
		printf("posX = %f\n", data->posX);
		int dof;
		int mx;
		int my;
		int mp;
		for(int i = 0; i < 360; i += 1)
    	{
			for (int r = 0; r < 3; r++)
			{
				x1 = r * cos(i * PI / 180);
				y1 = r * sin(i * PI / 180);
				my_mlx_pixel_put(&data->img, ray_x + x1, ray_y + y1, 0x00FF0000);
			}
		}
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
            my_mlx_pixel_put(&data->img, data->posX + x1, data->posY + y1, 0x00658354);
      	}
	}
}

int	plot_frame(t_settings *data)
{
	for (int x = 0; x < screenWidth; x++)
	{
		for (int y = 0; y < screenHeight ; y++)
		{
			int type = worldMap[y / 26][x / 26];
			if (type != 0 && x)
				my_mlx_pixel_put(&data->img, x, y, 0x00FFFFFF);
			else

				my_mlx_pixel_put(&data->img, x, y, 0x00000000);
			if (x % 26 == 0 || y % 26 == 0)
				my_mlx_pixel_put(&data->img, x, y, 0x00808080);
		}
	}
	draw_player(data);
	draw_rays(data);
	draw_line(data, data->angle, 30, 0x00FF0000);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	return (1);
}

int	key_press(int key_code, t_settings *data)
{
	if (key_code == LEFT)
	{
		data->angle += 0.1;
		if (data->angle > 2 * PI)
			data->angle -= 2 * PI;
		data->deltaX = sin(data->angle) * 5;
		data->deltaY = cos(data->angle) * 5;
	}
	if (key_code == RIGHT)
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
	plot_frame(data);
	// printf("deltaX = %f, deltaY = %f\nAngle = %f\n", data->deltaX, data->deltaY, data->angle);
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
	data->posX = 300;
	data->posY = 300;
	data->dirX = -1;
	data->dirY = 0;
	data->deltaX = 0;
	data->deltaY = -5;
	data->angle = 1.5 * PI;
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