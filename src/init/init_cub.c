/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_cub.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 00:12:46 by ivork         #+#    #+#                 */
/*   Updated: 2022/12/13 02:18:25 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdio.h>
#include <stdlib.h>

static void	set_start_pos(t_data *data, t_cub *cub)
{
	data->player->planeY = 0;
	data->player->planeX = 0;
	data->player->dirX = 0;
	data->player->dirY = 0;
	if (cub->map[cub->start_pos[0]][cub->start_pos[1]] == 'N')
	{
		data->player->dirY = -1;
		data->player->planeX = -0.5;
	}
	else if (cub->map[cub->start_pos[0]][cub->start_pos[1]] == 'S')
	{
		data->player->dirY = 1;
		data->player->planeX = 0.5;
	}
	else if (cub->map[cub->start_pos[0]][cub->start_pos[1]] == 'E')
	{
		data->player->dirX = -1;
		data->player->planeY = 0.5;
	}
	else
	{
		data->player->dirX = 1;
		data->player->planeY = -0.5;
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
	data->player->posX = cub->start_pos[1];
	data->player->posY = cub->start_pos[0];
	set_start_pos(data, cub);
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
	data->textures->texture_N = mlx_load_png(cub->no_path[1]);
	data->textures->texture_S = mlx_load_png(cub->so_path[1]);
	data->textures->texture_W = mlx_load_png(cub->we_path[1]);
	data->textures->texture_E = mlx_load_png(cub->ea_path[1]);
	if (!data->textures->texture_N || !data->textures->texture_E
		|| !data->textures->texture_W || !data->textures->texture_S)
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
	data->mapHeigth = cub->rows;
	data->mapwidth = cub->cols;
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
