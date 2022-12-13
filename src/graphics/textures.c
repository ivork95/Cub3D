/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 00:18:31 by ivork         #+#    #+#                 */
/*   Updated: 2022/12/13 02:17:36 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>

static int	get_rgba(mlx_texture_t *texture, int x, int y)
{
	int	r;
	int	g;
	int	b;
	int	a;

	y = y % texture->height;
	x = x % texture->width;
	r = texture->pixels[y * texture->width * 4 + (x * 4)];
	g = texture->pixels[y * texture->width * 4 + (x * 4) + 1];
	b = texture->pixels[y * texture->width * 4 + (x * 4) + 2];
	a = texture->pixels[y * texture->width * 4 + (x * 4) + 3];
	return (r << 24 | g << 16 | b << 8 | a);
}

static void	set_textures_side(t_textures *textures, t_ray *ray)
{	
	if (ray->side == 0 && ray->dirX > 0)
		textures->texture = textures->texture_W;
	else if (ray->side == 0)
		textures->texture = textures->texture_E;
	else if (ray->side == 1 && ray->dirY < 0)
		textures->texture = textures->texture_N;
	else
		textures->texture = textures->texture_S;
}

static double	map_line_heigth(t_data *data, t_textures *textures, t_ray *ray)
{
	double	line_heigth;

	line_heigth = SCREENHEIGHT / ray->distance;
	if (ray->side == 0)
	{
		textures->tx = data->player->posY + ray->distance * ray->dirY;
		textures->tx -= floor((textures->tx));
		textures->tx *= textures->texture->width;
		if (ray->dirX > 0)
			textures->tx = (textures->texture->width) - textures->tx;
	}
	else
	{
		textures->tx = data->player->posX + ray->distance * ray->dirX;
		textures->tx -= floor((textures->tx));
		textures->tx *= textures->texture->width;
		if (ray->dirY < 0)
			textures->tx = textures->texture->width - textures->tx;
	}
	textures->texture_step_y = textures->texture->height / (float)line_heigth;
	textures->ty_offset = 0;
	if (line_heigth > SCREENHEIGHT)
	{
		textures->ty_offset = (line_heigth - SCREENHEIGHT) / 2.0;
		line_heigth = SCREENHEIGHT;
	}
	textures->ty = (textures->ty_offset * textures->texture_step_y);
	return (line_heigth);
}

void	build_wall(t_data *data, int x)
{
	t_textures	*textures;
	double		line_heigth;
	int			i;
	int			j;

	textures = data->textures;
	set_textures_side(textures, data->ray);
	line_heigth = map_line_heigth(data, textures, data->ray);
	i = 0;
	while (i < SCREENHEIGHT)
	{
		if (SCREENHEIGHT - i <= (SCREENHEIGHT + line_heigth) / 2)
		{
			j = 0;
			while (j <= line_heigth)
			{
				mlx_put_pixel(data->img, x, i + j,
					get_rgba(textures->texture, textures->tx, textures->ty));
				textures->ty += textures->texture_step_y;
				j++;
			}
			i = SCREENHEIGHT;
		}
		i++;
	}
}
