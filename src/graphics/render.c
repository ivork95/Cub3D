/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 01:11:02 by ivork         #+#    #+#                 */
/*   Updated: 2022/12/01 17:02:03 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>



void draw_sky(t_data *data)
{
	for(int x = 0; x < screenHeight; x += 1)
	{
		for (int y = 0; y < screenWidth / 2; y++)
				mlx_put_pixel(data->img, x, y, 0x0000FFFF);
	}
}

void draw_ground(t_data *data)
{
	for(int x = 0; x < screenHeight; x += 1)
	{
		for (int y = 0; y < screenWidth / 2; y++)
				mlx_put_pixel(data->img, x, screenWidth - y, 0x00A0522D);
	}
}

static int	get_rgba(mlx_texture_t* texture, int x, int y)
{
	int	r;
	int	g;
	int	b;
	int	a;

	r = texture->pixels[y * texture->width * 4 + (x * 4)];
	g = texture->pixels[y * texture->width * 4 + (x * 4) + 1];
	b = texture->pixels[y * texture->width * 4 + (x * 4) + 2];
	a = texture->pixels[y * texture->width * 4 + (x * 4) + 3];
    return (r << 24 | g << 16 | b << 8 | a);
}

static void	draw_wall(t_data *data, double ray_length, int x, double angle)
{
	double	line_heigth;
	double	ty;
	double	tx;
	double	texture_step_y;
	double	ty_off;
	int		i;
	int		j;

	line_heigth = (screenHeight / data->mapHeigth * screenHeight) / ray_length;
	if (data->settings->hitX == -1 && angle > PI && angle < 2 * PI)
		data->textures->texture = data->textures->texture_W;
	else if (data->settings->hitX == -1)
		data->textures->texture = data->textures->texture_E;
	else if (data->settings->hitY == -1 && (angle < 0.5 * PI || angle > 1.5 * PI))
		data->textures->texture = data->textures->texture_S;
	else
		data->textures->texture = data->textures->texture_N;
    if (data->settings->hitX == -1)
    {
        tx = (double)(fmod(data->settings->hitY, ((double)screenHeight / (double)data->mapHeigth))) / (screenHeight / data->mapHeigth) * (data->textures->texture->width);
		if (angle > PI && angle < 2 * PI)
			tx = (data->textures->texture->width) - tx;
    }
    else
	{
        tx = (float)(fmod(data->settings->hitX, (screenHeight / data->mapHeigth))) / (screenHeight / data->mapHeigth) * (data->textures->texture->width);
		if (angle < 0.5 * PI || angle > 1.5 * PI)
			tx = data->textures->texture->width - tx;
	}
	texture_step_y = data->textures->texture->height/(float)line_heigth;
	ty_off = 0;
	if (line_heigth > screenHeight)
	{
		ty_off = (line_heigth - screenHeight) / 2.0;
		line_heigth = screenHeight;
	}
	ty = (ty_off * texture_step_y);
	i = 0;
	while (i < screenHeight)
	{
		if (screenHeight - i <=  (screenHeight + line_heigth) / 2)
		{
			j = 0;
			while (j <= line_heigth)
			{
				mlx_put_pixel(data->img, x,  i + j, get_rgba(data->textures->texture, tx, ty));
				ty += texture_step_y;
				j++;
			}
			i = screenHeight;
			break ;
		}
		i++;
	}
}

void render_screen(t_data *data, int x, double angle)
{
    if (x == 0)
    {
		create_top_view(data);
		angle = 0;
        // draw_sky(data);
        // draw_ground(data);
    }
    // draw_wall(data, data->settings->distance, x, angle);
}