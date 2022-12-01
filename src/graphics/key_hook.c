/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_hook.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 00:55:31 by ivork         #+#    #+#                 */
/*   Updated: 2022/12/01 12:31:47 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <math.h>


int	collide(t_data *data, int key_code)
{
	double	x;
	double	y;
	double	angle;

	if (key_code == MLX_KEY_S)
		angle = data->settings->angle + PI;
	if (key_code == MLX_KEY_W)
		angle = data->settings->angle;
	if (key_code == MLX_KEY_A)
		angle = data->settings->angle + 0.5 * PI;
	if (key_code == MLX_KEY_D)
		angle = data->settings->angle - 0.5 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	if (angle < 0)
		angle += 2 * PI;
	x = get_ray_length_x(data, angle);
	y = get_ray_length_y(data, angle);
	if (x < 5 || y < 5)
		return (1);
	return (0);
}

void	key_press(void *param)
{
	t_data	*data;
	mlx_t		*mlx;
	double		dt;

	data = param;
	mlx = data->mlx;
	dt = mlx->delta_time * 30;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		data->settings->angle += 0.05;
		if (data->settings->angle < 0)
			data->settings->angle += 2 * PI;
		if (data->settings->angle > 2 * PI)
			data->settings->angle -= 2 * PI;
		data->settings->deltaX = sin(data->settings->angle) * 5;
		data->settings->deltaY = cos(data->settings->angle) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		data->settings->angle -= 0.05;
		if (data->settings->angle < 0)
			data->settings->angle += 2 * PI;
		if (data->settings->angle > 2 * PI)
			data->settings->angle -= 2 * PI;
		data->settings->deltaX = sin(data->settings->angle) * 5;
		data->settings->deltaY = cos(data->settings->angle) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_W) &&  !collide(data, MLX_KEY_W))
	{
		data->settings->posY += data->settings->deltaY * dt;
		data->settings->posX += data->settings->deltaX * dt;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S)  &&  !collide(data, MLX_KEY_S))
	{
		data->settings->posY -= data->settings->deltaY * dt;
		data->settings->posX -= data->settings->deltaX * dt;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A) &&  !collide(data, MLX_KEY_A))
	{
		data->settings->posY += cos(data->settings->angle + 0.5 * PI) * 5 * dt;
		data->settings->posX += sin(data->settings->angle + 0.5 * PI) * 5 * dt;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D)  &&  !collide(data, MLX_KEY_D))
	{
		data->settings->posY += cos(data->settings->angle - 0.5 * PI) * 5 * dt;
		data->settings->posX += sin(data->settings->angle - 0.5 * PI) * 5 * dt;
	}
	create_image(data);
}
