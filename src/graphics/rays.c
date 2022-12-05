/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rays.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 00:45:01 by ivork         #+#    #+#                 */
/*   Updated: 2022/12/04 20:56:53 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>
#include <stdio.h>

double get_ray_length_y(t_data *data, double angle)
{
	int	j;
	double ray_length;
	double rad;
	double nextY;
	double nextX;
	double deltaY;
	double deltaX;
	t_player *settings;

	j = 0;
	settings = data->settings;
	// printf("#########################\n");
	// printf("ratioX = %f\n", ((float)screenWidth / data->mapwidth));
	// printf("ratioY = %f\n", ((float)screenHeight / data->mapHeigth));
	while (j < data->mapHeigth)
	{
		ray_length = 100000000;
		if (angle == 1.5 * PI || angle == 0.5 * PI)
			break ;
		if (0.5 * PI < angle && angle < 1.5 * PI)
		{
			nextY = ((((int)(settings->posY / ((float)screenHeight / data->mapHeigth))) - j)) * ((float)screenHeight / data->mapHeigth);
			rad = angle - PI;
			nextX = settings->posX - tan(rad) * fabs(settings->posY - nextY);
			nextY = ((nextY / ((float)screenHeight / data->mapHeigth)) - 0.0001) * ((float)screenHeight / data->mapHeigth);
		}
		else
		{
			nextY = ((int)(settings->posY / ((float)screenHeight / data->mapHeigth) + 1 + j)) * ((float)screenHeight / data->mapHeigth);
			rad = angle;
			nextX = settings->posX + tan(rad) * fabs(settings->posY - nextY);
		}
		if (nextX < 0 || nextX > screenWidth|| nextY < 0 || nextY > screenHeight)
			break ;
		// printf("nY = %f\n", nextY);
		// printf("nX = %f\n", nextX);
		// int indexX = (nextY / ((float)screenHeight / (data->mapHeigth)));
		// int indexY = (nextX / ((float)screenWidth / (data->mapwidth)));
		// printf("index-Y = %d\n", indexX);
		// printf("index-X = %d\n", indexY);
		// printf("actual = %c\n", data->map[(int)(nextY / ((float)screenHeight / (data->mapHeigth)))][(int)(nextX / ((float)screenWidth / (data->mapwidth)))]);
		// printf("expected = %c\n", data->map[18][13]);
		// printf("---------------------\n");
		deltaX = fabs(settings->posX - nextX); 
		deltaY = fabs(settings->posY - nextY);
		ray_length = sqrt(deltaX * deltaX + deltaY * deltaY);
        settings->hitX = nextX;
		// if (data->map[indexY][indexX] != '0')
		if (data->map[(int)(nextY / ((float)screenHeight / (data->mapHeigth)) + 0.000001)][(int)(nextX / ((float)screenWidth / (data->mapwidth)))] != '0')
			break ;
		ray_length = 1000000000;
		j++;
	}
	return (ray_length);
}

double get_ray_length_x(t_data *data, double angle)
{
	int	z;
	double ray_length;
	double rad;
	double nextY;
	double nextX;
	double deltaY;
	double deltaX;
	t_player *settings;

	z = 0;
	settings = data->settings;
	// printf("#########################\n");
	// printf("ratioX = %f\n", ((float)screenWidth / data->mapwidth));
	// printf("ratioY = %f\n", ((float)screenHeight / data->mapHeigth));
	while (z < data->mapwidth)
	{
		ray_length = 10000000;
		if (angle == 2 * PI || angle == 0)
			break ;
		if (angle > PI)
		{
			nextX = ((((int)(settings->posX / ((float)screenWidth / data->mapwidth) - z)))) * ((float)screenWidth / data->mapwidth);
			rad = 2 * PI - angle;
			nextY = settings->posY + fabs(settings->posX - nextX) / tan(rad);
			nextX = ((nextX / ((float)screenWidth / data->mapwidth)) - 0.0001) * ((float)screenWidth / data->mapwidth);
		}
		else
		{
			nextX = ((int)(settings->posX / ((float)screenWidth / data->mapwidth) + z + 1)) * ((float)screenWidth / data->mapwidth);
			rad = angle;
			nextY = settings->posY + fabs(settings->posX - nextX) / tan(rad);
		}
		if (nextX < 0 || nextX > screenWidth || nextY < 0 || nextY > screenHeight)
			break ;
		deltaX = fabs(settings->posX - nextX); 
		deltaY = fabs(settings->posY - nextY);
		ray_length = sqrt(deltaX * deltaX + deltaY * deltaY);
        settings->hitY = nextY;
		// printf("nY = %f\n", nextY);
		// printf("nX = %f\n", nextX);
		// int indexX = (nextY / ((float)screenHeight / (data->mapHeigth)));
		// int indexY = (nextX / ((float)screenWidth / (data->mapwidth)) + 0.001);
		// printf("index-Y = %d\n", indexX);
		// printf("index-X = %d\n", indexY);
		// printf("actual = %c\n", data->map[(int)(nextY / ((float)screenHeight / (data->mapHeigth)))][(int)(nextX / ((float)screenWidth / (data->mapwidth)))]);
		// printf("---------------------\n");
		if (nextX > 0 && nextX < screenWidth && nextY > 0 && nextY < screenHeight)
		{
			if (data->map[(int)(nextY / ((float)screenHeight / (data->mapHeigth)))][(int)(nextX / ((float)screenWidth / (data->mapwidth)) + 0.000001)] != '0')
				break ;
		}
		ray_length = 10000000;
		z++;
	}
	return (ray_length);
}

double calc_angle(int i)
{
	double angle;
	double plane_size;
	double step;
	
	plane_size = tan(FOV / 2 * RAD);
	step = 2 * plane_size / screenWidth;
	angle = atan((plane_size - step * i) / 1);
	return (angle);
}

void shoot_rays(t_data *data)
{
	double	ray_length_y;
	double	ray_length_x;
	double	shortest;
	double	angle;
	int		i;
	i = 0;
	// while (i < 1)
	while (i < screenWidth)
	{
		angle = data->settings->angle + calc_angle(i);
		// angle = data->settings->angle + ((float)FOV / 2 - ((float)i / screenWidth * FOV)) * RAD;
		// angle = data->settings->angle;
		if (angle > 2.0 * PI)
			angle -= 2.0 * PI;
		if (angle < 0)
			angle += 2.0 * PI;
		ray_length_y =  get_ray_length_y(data, angle);
		ray_length_x = get_ray_length_x(data, angle);
		if (ray_length_x < ray_length_y)
		{
			shortest = ray_length_x;
			data->settings->hitX = -1;
		}
		else
		{
			shortest = ray_length_y;
			data->settings->hitY = -1;
		}
		shortest = shortest * cos(fabs(angle - data->settings->angle));
		data->settings->distance = shortest;
		render_screen(data, i, angle);
		i++;
		// draw_line(data, angle, shortest, 0xFFFFFFFF);
	}
}