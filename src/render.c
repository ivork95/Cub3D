/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 01:11:02 by ivork         #+#    #+#                 */
/*   Updated: 2022/11/23 14:30:57 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void	my_mlx_pixel_put(t_win *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_sky(t_settings *data)
{
	for(int x = 0; x < screenHeight; x += 1)
	{
		for (int y = 0; y < screenWidth / 2; y++)
				mlx_put_pixel(data->img, x, y, 0x0000FFFF);
	}
}

void draw_ground(t_settings *data)
{
	for(int x = 0; x < screenHeight; x += 1)
	{
		for (int y = 0; y < screenWidth / 2; y++)
				mlx_put_pixel(data->img, x, screenWidth - y, 0x00A0522D);
	}
}

int	get_color(mlx_texture_t* texture, int x, int y)
{
	unsigned long color;
	int red;
	int green;
	int blue;

	// blue = texture->pixels[x * texture->width * 4 + (y * 4) + 1];
	// green = texture->pixels[x * texture->width * 4 + (y * 4) + 2];
	// red = texture->pixels[x * texture->width * 4 + (y * 4) + 3];

	blue = texture->pixels[y * texture->width * 4 + (x * 4) + 1];
	green = texture->pixels[y * texture->width * 4 + (x * 4) + 2];
	red = texture->pixels[y * texture->width * 4 + (x * 4) + 3];
	color = (256 * 256 * 256 * 256) + (blue * 256 * 256) + (green * 256) + red;
	return (color);
}

void build_wall(t_settings *data, double ray_length, int x, int color, double angle)
{
	double line_heigth;
	double	ty;
	double	tx;
	double	texture_step_y;
	double	ty_off;
	int		i;
	int		j;
	long	color2;

	color = 0xFFFFFFFF;
	line_heigth = (screenHeight / mapHeight * screenHeight) / ray_length;
	texture_step_y = data->texture->height/(float)line_heigth;
	ty_off = 0;
    if (data->hitX == -1)
    {
        // tx = (double)((int)data->hitY % (screenHeight / mapHeight)) / (screenHeight / mapHeight) * (data->texture->width / 4.0);
        tx = (double)(fmod(data->hitY, ((double)screenHeight / (double)mapHeight))) / (screenHeight / mapHeight) * (data->texture->width);
		if (angle > PI && angle < 2 * PI)
			tx = (data->texture->width) - tx;
    }
    else
	{
        // tx = (float)((int)data->hitX % (screenHeight / mapHeight)) / (screenHeight / mapHeight) * (data->texture->width / 4.0);
        tx = (float)(fmod(data->hitX, (screenHeight / mapHeight))) / (screenHeight / mapHeight) * (data->texture->width);
		if (angle < 0.5 * PI || angle > 1.5 * PI)
			tx = data->texture->width - tx;
		
	}
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
				color2 = get_color(data->texture, tx, ty);
				mlx_put_pixel(data->img, x,  i + j, color2);
				ty += texture_step_y;
				j++;
			}
			i = screenHeight;
			break ;
		}
		i++;
	}
}

void render_screen(t_settings *data, int x, int color, double angle)
{
    if (x == 0)
    {
        create_top_view(data);
        draw_sky(data);
        draw_ground(data);
    }
    build_wall(data, data->distance, x, color, angle);
}