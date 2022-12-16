/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 00:45:01 by ivork         #+#    #+#                 */
/*   Updated: 2022/12/16 15:02:43 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	rgb_to_argb(t_rgb color)
{
	int	a;

	a = 255;
	return (color.r << 24 | color.g << 16 | color.b << 8 | a);
}

void	color_background(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < SCREENHEIGHT)
	{
		y = 0;
		while (y < SCREENHEIGHT / 2)
		{
			mlx_put_pixel(data->img, x, y, rgb_to_argb(data->ceiling));
			y++;
		}
		x++;
	}
	x = 0;
	while (x < SCREENHEIGHT)
	{
		y = SCREENHEIGHT - 1;
		while (y > SCREENHEIGHT / 2)
		{
			mlx_put_pixel(data->img, x, y, rgb_to_argb(data->floor));
			y--;
		}
		x++;
	}
}

static void	ray_direction(t_player *player, t_ray *ray)
{
	if (ray->dir_x != 0)
		ray->delta_x = fabs(1 / ray->dir_x);
	if (ray->dir_y != 0)
		ray->delta_y = fabs(1 / ray->dir_y);
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->next_x = (player->pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->next_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->next_y = (player->pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->next_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_y;
	}
}

static void	dda(char **map, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->next_x < ray->next_y)
		{
			ray->next_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->next_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (map[ray->map_y][ray->map_x] != '0')
			hit = 1;
	}
}

void	shoot_rays(t_data *data)
{
	t_player	*player;
	t_ray		*ray;
	int			x;

	player = data->player;
	ray = data->ray;
	x = 0;
	while (x < SCREENWIDTH)
	{
		player->camera_x = 2 * x / (double)SCREENWIDTH - 1;
		ray->dir_x = player->dir_x + player->plane_x * player->camera_x;
		ray->dir_y = player->dir_y + player->plane_y * player->camera_x;
		ray->map_x = (int)player->pos_x;
		ray->map_y = (int)player->pos_y;
		ray->delta_x = 1e30;
		ray->delta_y = 1e30;
		ray_direction(player, ray);
		dda(data->map, ray);
		if (ray->side == 0)
			ray->distance = (ray->next_x - ray->delta_x);
		else
			ray->distance = (ray->next_y - ray->delta_y);
		build_wall(data, x);
		x++;
	}
}
