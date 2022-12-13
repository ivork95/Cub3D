/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 00:45:01 by ivork         #+#    #+#                 */
/*   Updated: 2022/12/13 02:29:36 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>

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
	if (ray->dirX != 0)
		ray->deltaX = fabs(1 / ray->dirX);
	if (ray->dirY != 0)
		ray->deltaY = fabs(1 / ray->dirY);
	if (ray->dirX < 0)
	{
		ray->stepX = -1;
		ray->nextX = (player->posX - ray->mapX) * ray->deltaX;
	}
	else
	{
		ray->stepX = 1;
		ray->nextX = (ray->mapX + 1.0 - player->posX) * ray->deltaX;
	}
	if (ray->dirY < 0)
	{
		ray->stepY = -1;
		ray->nextY = (player->posY - ray->mapY) * ray->deltaY;
	}
	else
	{
		ray->stepY = 1;
		ray->nextY = (ray->mapY + 1.0 - player->posY) * ray->deltaY;
	}
}

static void	dda(char **map, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->nextX < ray->nextY)
		{
			ray->nextX += ray->deltaX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->nextY += ray->deltaY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (map[ray->mapY][ray->mapX] != '0')
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
		player->cameraX = 2 * x / (double)SCREENWIDTH - 1;
		ray->dirX = player->dirX + player->planeX * player->cameraX;
		ray->dirY = player->dirY + player->planeY * player->cameraX;
		ray->mapX = (int)player->posX;
		ray->mapY = (int)player->posY;
		ray->deltaX = 1e30;
		ray->deltaY = 1e30;
		ray_direction(player, ray);
		dda(data->map, ray);
		if (ray->side == 0)
			ray->distance = (ray->nextX - ray->deltaX);
		else
			ray->distance = (ray->nextY - ray->deltaY);
		build_wall(data, x);
		x++;
	}
}
