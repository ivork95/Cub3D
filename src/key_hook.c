/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_hook.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 00:55:31 by ivork         #+#    #+#                 */
/*   Updated: 2022/11/16 20:37:53 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
// #include "../mlx/mlx.h"
#include <math.h>

// void	key_press(int key_code, t_settings *data)
// {
// 	printf("key presse = %d\n", key_code);
// 	if (key_code == ROTATE_L)
// 	{
// 		data->angle += 0.1;
// 		if (data->angle > 2 * PI)
// 			data->angle -= 2 * PI;
// 		data->deltaX = sin(data->angle) * 5;
// 		data->deltaY = cos(data->angle) * 5;
// 	}
// 	if (key_code == ROTATE_R)
// 	{
// 		data->angle -= 0.1;
// 		if (data->angle < 0)
// 			data->angle += 2 * PI;
// 		data->deltaX = sin(data->angle) * 5;
// 		data->deltaY = cos(data->angle) * 5;
// 	}
// 	if (key_code == UP)
// 	{
// 		data->posY += data->deltaY;
// 		data->posX += data->deltaX;
// 	}
//     if (key_code == DOWN)
// 	{
// 		data->posY -= data->deltaY;
// 		data->posX -= data->deltaX;
// 	}
// 	// if (key_code == LEFT)
// 	// {
// 	// 	data->posY += data->deltaY;
// 	// 	data->posX -= data->deltaX;
// 	// }
//     // if (key_code == RIGHT)
// 	// {
// 	// 	data->posY -= data->deltaY;
// 	// 	data->posX -= data->deltaX;
// 	// }
// 	plot_frame(data);
// }

void	key_press(void *param)
{
	mlx_t	*mlx;
	t_settings *data;

	mlx = ((t_settings*)param)->mlx;
	data = ((t_settings*)param);
	// if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	// 	mlx_close_window(mlx);
	// if (mlx_is_key_down(mlx, MLX_KEY_UP))
	// 	data->img->instances[0].y -= 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	// 	data->img->instances[0].y += 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	// 	data->img->instances[0].x -= 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	// 	data->img->instances[0].x += 5;

	// printf("key presse = %d\n", key_code);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		data->angle += 0.1;
		if (data->angle > 2 * PI)
			data->angle -= 2 * PI;
		data->deltaX = sin(data->angle) * 5;
		data->deltaY = cos(data->angle) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		data->angle -= 0.1;
		if (data->angle < 0)
			data->angle += 2 * PI;
		data->deltaX = sin(data->angle) * 5;
		data->deltaY = cos(data->angle) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
	{
		data->posY += data->deltaY;
		data->posX += data->deltaX;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	{
		data->posY -= data->deltaY;
		data->posX -= data->deltaX;
	}
	// if (key_code == LEFT)
	// {
	// 	data->posY += data->deltaY;
	// 	data->posX -= data->deltaX;
	// }
    // if (key_code == RIGHT)
	// {
	// 	data->posY -= data->deltaY;
	// 	data->posX -= data->deltaX;
	// }
	// plot_frame(data);
}