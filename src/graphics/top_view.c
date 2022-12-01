/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   top_view.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/11 19:16:16 by ivork         #+#    #+#                 */
/*   Updated: 2022/12/01 17:37:44 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>


void draw_line(t_data *data, double angle, double line_lenght, long color)
{
	int x1;
	int y1;

	for(int i = 0; i < line_lenght; i += 1)
    {
		x1 = i * sin(angle) + data->settings->posX;
		y1 = i * cos(angle) + data->settings->posY;
		if (x1 < screenWidth && x1 > 0  && y1 < screenHeight && y1 > 0)
			mlx_put_pixel(data->img, x1, y1, color);
	}
}

// void draw_player_point(t_data *data)
// {
// 	int x1;
// 	int y1;

// 	for(int i = 0; i < 360; i += 1)
//     {
// 		for (int r = 0; r < 6; r++)
// 		{
//             x1 = r * cos(i * PI / 180);
//             y1 = r * sin(i * PI / 180);
//             mlx_put_pixel(data->img, data->posX + x1, data->posY + y1, 0xFFFFFFFF);
//       	}
// 	}
// 	draw_line(data, data->angle, 50, 0xFFFFFFFF);
// }

void	draw_tiles(t_data *data)
{
	double x;
	double y;
	double Hratio;
	double Wratio;
	
	x = 0;
	Hratio = (float)screenHeight / (data->mapHeigth);
	Wratio = (float)screenHeight / (data->mapHeigth);
	while (x < screenWidth)
	{
		y = 0;
		while (y < screenHeight)
		{
			char type = data->map[(int)(y / ((float)screenHeight / (data->mapHeigth)))][(int)(x / ((float)screenWidth / (data->mapwidth)))];
			if (type != '0')
				mlx_put_pixel(data->img, x, y, 0x00FFFFFF);
			else
				mlx_put_pixel(data->img, x, y, 0x00000000);
			if ((int)x % (int)Hratio == 0 || (int)y % (int)Wratio == 0)
				mlx_put_pixel(data->img, x, y, 0x00808080);
			y++;
		}
		x++;
	}
}

void	create_top_view(t_data *data)
{
	draw_tiles(data);
	// draw_player_point(data);
}

