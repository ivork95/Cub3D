/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rays.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 00:45:01 by ivork         #+#    #+#                 */
/*   Updated: 2022/11/16 15:29:16 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <math.h>

int worldMap1[mapHeight][mapWidth]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,1,1,1,1,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

double get_ray_length_y(t_settings *data, double angle)
{
	int	j;
	double ray_length;
	double rad;
	double nextY;
	double nextX;
	double deltaY;
	double deltaX;

	j = 0;
	while (j < mapHeight)
	{
		ray_length = 100000000;
		if (angle == 1.5 * PI || angle == 0.5 * PI)
			break ;
		if (0.5 * PI < angle && angle < 1.5 * PI)
		{
			nextY = (((((int)data->posY / (screenHeight / mapHeight))) - 0.0001) - j) * (screenHeight / mapHeight);
			rad = angle - PI;
			nextX = data->posX - tan(rad) * fabs(data->posY - nextY);
		}
		else
		{
			nextY = ((int)data->posY / (screenHeight / mapHeight) + 1 + j) * (screenHeight / mapHeight);
			rad = angle;
			nextX = data->posX + tan(rad) * fabs(data->posY - nextY);
		}
		if (nextX < 0 || nextX > 624 || nextY < 0 || nextY > 624)
			break ;
		deltaX = fabs(data->posX - nextX); 
		deltaY = fabs(data->posY - nextY);
		ray_length = sqrt(deltaX * deltaX + deltaY * deltaY);
        data->hitX = nextX;
		if (worldMap1[(int)nextY / 26][(int)nextX / 26] != 0)
			break ;
		ray_length = 1000000000;
		j++;
	}
	return (ray_length);
}

double get_ray_length_x(t_settings *data, double angle)
{
	int	z;
	double ray_length;
	double rad;
	double nextY;
	double nextX;
	double deltaY;
	double deltaX;

	z = 0;
	while (z < mapWidth)
	{
		ray_length = 10000000;
		if (angle == 2 * PI || angle == 0)
			break ;
		if (angle > PI)
		{
			nextX = (((((int)data->posX / (screenHeight / mapHeight)) - z) - 0.0001)) * (screenHeight / mapHeight);
			rad = 2 * PI - angle;
			nextY = data->posY + fabs(data->posX - nextX) / tan(rad);
		}
		else
		{
			nextX = ((int)data->posX / (screenHeight / mapHeight) + z + 1) * (screenHeight / mapHeight);
			rad = angle;
			nextY = data->posY + fabs(data->posX - nextX) / tan(rad);
		}
		if (nextX < 0 || nextX > 624 || nextY < 0 || nextY > 624)
			break ;
		deltaX = fabs(data->posX - nextX); 
		deltaY = fabs(data->posY - nextY);
		ray_length = sqrt(deltaX * deltaX + deltaY * deltaY);
        data->hitY = nextY;
		if (nextX > 0 && nextX < 624 && nextY > 0 && nextY < 624)
		{
			if (worldMap1[(int)nextY / 26][(int)nextX / 26] != 0)
				break ;
		}
		ray_length = 10000000;
		z++;
	}
	return (ray_length);
}

void shoot_rays(t_settings *data)
{
	double	ray_length_y;
	double	ray_length_x;
	double	shortest;
	double	angle;
	int		color;
	int		i;

	i = 0;
	while (i < screenWidth)
	{
		angle = data->angle + ((float)FOV / 2 - ((float)i / screenWidth * FOV)) * RAD;
		if (angle > 2 * PI)
			angle -= 2 * PI;
		if (angle < 0)
			angle += 2 * PI;
		ray_length_y =  get_ray_length_y(data, angle);
		ray_length_x = get_ray_length_x(data, angle);
		if (ray_length_x < ray_length_y)
		{
			shortest = ray_length_x;
			color = 0x0000FF00;
            data->hitX = -1;
		}
		else
		{
			shortest = ray_length_y;
			color = 0x00006400;
            data->hitY = -1;
		}
		double ca=data->angle - angle;
		if (ca < 0)
			ca += 2 * PI;
		else if ( ca > 2 * PI)
			ca -= 2 * PI;
		shortest=shortest*cos(ca);
        data->distance = shortest;
        render_screen(data, i, color, angle);

		//rays for top view
		// draw_line(data, angle, shortest, color);
		i++;
	}
}
