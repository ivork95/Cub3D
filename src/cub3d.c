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