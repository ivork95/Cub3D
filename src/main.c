// #include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../includes/cub3d.h"
#include "../MLX42/include/MLX42/MLX42.h"

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
  {1,0,0,0,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
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

int	plot_frame(t_settings *data)
{
	shoot_rays(data);
	// mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	return (1);
}

void	init_player_settings(t_settings *data)
{
	data->posX = 320;
	data->posY = 300;
	data->dirX = -1;
	data->dirY = 0;
	data->deltaX = 0;
	data->deltaY = 0;
	data->angle = 0.5 * PI;
	data->hitX = -1;
	data->hitY = -1;
}

t_settings *init_window(void)
{
	t_settings *data;

	data = malloc(sizeof(t_settings));
	data->mlx = mlx_init((const uint32_t)screenWidth, (const uint32_t)screenHeight, "Cub3d", false);
	if (!data->mlx)
		exit(EXIT_FAILURE);
	data->img = mlx_new_image(data->mlx, screenWidth, screenHeight);
	return (data);
}

t_settings	*init_data(void)
{
	t_settings	*data;

	data = init_window();
	init_player_settings(data);
	data->texture = mlx_load_png("./Checkerboard_pattern.png");
	if (!data->texture)
	{
		printf("failed to load texture\n");
		exit(1);
	}
	// data->map = malloc(sizeof(int) * mapHeight * mapWidth);
	// data->map = worldMap;
	return (data);
}

int	main(void)
{
	t_settings *data;

	data = init_data();
	plot_frame(data);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	// mlx_loop(data->mlx);


	// mlx_t	*mlx;
	// mlx_image_t	*img;

	// mlx = mlx_init(screenWidth, screenHeight, "Cub3d", true);
	// if (!mlx)
	// 	exit(EXIT_FAILURE);
	// img = mlx_new_image(mlx, 128, 128);
	// memset(img->pixels, 255, img->width * img->height * sizeof(int));
	// mlx_image_to_window(mlx, img, 0, 0);
	// // mlx_loop_hook(mlx, &key_press, mlx);
	// mlx_loop(mlx);
	// mlx_terminate(mlx);
}