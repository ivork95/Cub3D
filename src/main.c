// #include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../includes/cub3d.h"
#include "../includes/tokenize.h"
#include "../includes/structs.h"
#include "../includes/utils.h"
#include "../MLX42/include/MLX42/MLX42.h"

int	create_image(t_data *data)
{

	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, screenWidth, screenHeight);
	shoot_rays(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	return (1);
}

void	init_player_settings(t_data *data, t_cub *cub)
{
	data->settings = malloc(sizeof(t_player));
	if (!data->settings)
	{
		printf("maloc failure");
		exit(1);
	}
	data->settings->posX = cub->start_pos[1] * (screenWidth / cub->cols);
	data->settings->posY = cub->start_pos[0] * (screenHeight / cub->rows);
	if (cub->map[cub->start_pos[0]][cub->start_pos[1]] == 'N')
		data->settings->angle = PI;
	if (cub->map[cub->start_pos[0]][cub->start_pos[1]] == 'S')
		data->settings->angle = 2 * PI;
	if (cub->map[cub->start_pos[0]][cub->start_pos[1]] == 'E')
		data->settings->angle = 0.5 * PI;
	if (cub->map[cub->start_pos[0]][cub->start_pos[1]] == 'W')
		data->settings->angle = 1.5 * PI;
	data->settings->deltaX = sin(data->settings->angle) * 5;
	data->settings->deltaY = cos(data->settings->angle) * 5;
	data->settings->hitX = -1;
	data->settings->hitY = -1;
	data->map = cub->map;
	data->mapHeigth = cub->rows;
	data->mapwidth = cub->cols;
}

t_data *init_window(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		printf("malloc failure\n");
		exit(1);
	}
	data->mlx = mlx_init((const uint32_t)screenWidth, (const uint32_t)screenHeight, "Cub3d", false);
	if (!data->mlx)
		exit(EXIT_FAILURE);
	return (data);
}

void	init_textures(t_data *data, t_cub *cub)
{
	data->textures = malloc(sizeof(t_textures));
	if (!data->textures)
	{
		printf("malloc failure\n");
		exit(1);
	}
	data->textures->texture_N = mlx_load_png(cub->no_path[1]);
	data->textures->texture_S = mlx_load_png(cub->so_path[1]);
	data->textures->texture_W = mlx_load_png(cub->we_path[1]);
	data->textures->texture_E = mlx_load_png(cub->ea_path[1]);
	if (!data->textures->texture_N || !data->textures->texture_E || !data->textures->texture_W || !data->textures->texture_S)
	{
		printf("failed to load texture\n");
		exit(1);
	}
}

t_data	*init_data(t_cub *cub)
{
	t_data	*data;

	data = init_window();
	init_player_settings(data, cub);
	init_textures(data, cub);
	data->map = cub->map;
	return (data);
}

int	main(int argc, char *argv[argc + 1])
{
	t_data *data;
	t_cub *cub;

	if (argc != 2)
		put_exit_fail("Error: Invalid amount of arguments\n");
	cub = first(argv[argc - 1]);
	data = init_data(cub);
	mlx_loop_hook(data->mlx, &key_press, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}