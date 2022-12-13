/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_cub.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 00:12:46 by ivork         #+#    #+#                 */
/*   Updated: 2022/12/13 14:29:19 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdio.h>
#include <stdlib.h>

static void	set_start_pos(t_data *data)
{
	data->player->plane_y = 0;
	data->player->plane_x = 0;
	data->player->dir_x = 0;
	data->player->dir_y = 0;
	if (data->player->orientation == 'N')
	{
		data->player->dir_y = -1;
		data->player->plane_x = -0.5;
	}
	else if (data->player->orientation == 'S')
	{
		data->player->dir_y = 1;
		data->player->plane_x = 0.5;
	}
	else if (data->player->orientation == 'E')
	{
		data->player->dir_x = -1;
		data->player->plane_y = 0.5;
	}
	else
	{
		data->player->dir_x = 1;
		data->player->plane_y = -0.5;
	}
}

static void	init_player_settings(t_data *data, t_cub *cub)
{
	data->player = malloc(sizeof(t_player));
	if (!data->player)
	{
		printf("maloc failure");
		exit(1);
	}
	data->player->pos_x = cub->start_pos[1];
	data->player->pos_y = cub->start_pos[0];
	data->player->orientation = cub->orientation;
	data->player->move_speed = 0.1;
	data->player->rot_speed = 0.05;
	set_start_pos(data);
}

static t_data	*init_window(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
	{
		printf("malloc failure\n");
		exit(1);
	}
	data->mlx = mlx_init((const uint32_t)SCREENWIDTH,
			(const uint32_t)SCREENHEIGHT, "Cub3d", false);
	if (!data->mlx)
		exit(EXIT_FAILURE);
	return (data);
}

static void	init_textures(t_data *data, t_cub *cub)
{
	data->textures = malloc(sizeof(t_textures));
	if (!data->textures)
	{
		printf("malloc failure\n");
		exit(1);
	}
	data->textures->texture_north = mlx_load_png(cub->no_path[1]);
	data->textures->texture_south = mlx_load_png(cub->so_path[1]);
	data->textures->texture_west = mlx_load_png(cub->we_path[1]);
	data->textures->texture_east = mlx_load_png(cub->ea_path[1]);
	if (!data->textures->texture_north || !data->textures->texture_east
		|| !data->textures->texture_west || !data->textures->texture_south)
	{
		printf("failed to load texture\n");
		exit(1);
	}
}

t_data	*init_data(t_cub *cub)
{
	t_data	*data;

	data = init_window();
	data->map = cub->map;
	data->map_heigth = cub->rows;
	data->map_width = cub->cols;
	data->floor = cub->floor;
	data->ceiling = cub->ceiling;
	init_player_settings(data, cub);
	init_textures(data, cub);
	data->ray = malloc(sizeof(t_ray));
	if (!data->ray)
	{
		printf("maloc failure");
		exit(1);
	}
	return (data);
}
