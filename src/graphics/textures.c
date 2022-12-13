/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 00:18:31 by ivork         #+#    #+#                 */
/*   Updated: 2022/12/13 02:41:33 by ivork         ########   odam.nl         */
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

static double	map_line_tex(t_data *data, t_textures *tex, t_ray *ray, int lh)
{
	lh = SCREENHEIGHT / ray->distance;
	if (ray->side == 0)
	{
		tex->tx = data->player->posY + ray->distance * ray->dirY;
		tex->tx = (tex->tx - floor((tex->tx))) * tex->texture->width;
		if (ray->dirX > 0)
			tex->tx = (tex->texture->width) - tex->tx;
	}
	else
	{
		tex->tx = data->player->posX + ray->distance * ray->dirX;
		tex->tx = (tex->tx - floor((tex->tx))) * tex->texture->width;
		if (ray->dirY < 0)
			tex->tx = tex->texture->width - tex->tx;
	}
	tex->texture_step_y = tex->texture->height / (float)lh;
	tex->ty_offset = 0;
	if (lh > SCREENHEIGHT)
	{
		tex->ty_offset = (lh - SCREENHEIGHT) / 2.0;
		lh = SCREENHEIGHT;
	}
	tex->ty = (tex->ty_offset * tex->texture_step_y);
	return (lh);
}

void	build_wall(t_data *data, int x)
{
	t_textures	*textures;
	double		line_heigth;
	int			i;
	int			j;

	textures = data->textures;
	set_textures_side(textures, data->ray);
	line_heigth = map_line_tex(data, textures, data->ray, 0);
	i = 0;
	while (i < SCREENHEIGHT)
	{
		if (SCREENHEIGHT - i <= (SCREENHEIGHT + line_heigth) / 2)
		{
			j = 0;
			while (j < line_heigth)
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
