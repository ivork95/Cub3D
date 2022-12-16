/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_hook.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 00:55:31 by ivork         #+#    #+#                 */
/*   Updated: 2022/12/16 14:25:51 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/libft.h"
#include <math.h>

static void	rotate_right(t_player *player, mlx_t *mlx)
{
	double	old_dir_x;
	double	old_plane_x;

	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(-player->rot_speed)
			- player->dir_y * sin(-player->rot_speed);
		player->dir_y = old_dir_x * sin(-player->rot_speed)
			+ player->dir_y * cos(-player->rot_speed);
		old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(-player->rot_speed)
			- player->plane_y * sin(-player->rot_speed);
		player->plane_y = old_plane_x * sin(-player->rot_speed)
			+ player->plane_y * cos(-player->rot_speed);
	}
}

static void	rotate_left(t_player *player, mlx_t *mlx)
{
	double	old_dir_x;
	double	old_plane_x;

	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(player->rot_speed)
			- player->dir_y * sin(player->rot_speed);
		player->dir_y = old_dir_x * sin(player->rot_speed)
			+ player->dir_y * cos(player->rot_speed);
		old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(player->rot_speed)
			- player->plane_y * sin(player->rot_speed);
		player->plane_y = old_plane_x * sin(player->rot_speed)
			+ player->plane_y * cos(player->rot_speed);
	}
}

static void	move_up_down(t_player *player, mlx_t *mlx, char **map)
{
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		if (map[(int)player->pos_y]
			[(int)(player->pos_x + player->dir_x * player->move_speed)] == '0')
			player->pos_x += player->dir_x * player->move_speed;
		if (map[(int)(player->pos_y + player->dir_y * player->move_speed)]
			[(int)player->pos_x] == '0')
			player->pos_y += player->dir_y * player->move_speed;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		if (map[(int)player->pos_y]
			[(int)(player->pos_x - player->dir_x * player->move_speed)] == '0')
			player->pos_x -= player->dir_x * player->move_speed;
		if (map[(int)(player->pos_y - player->dir_y * player->move_speed)]
			[(int)player->pos_x] == '0')
			player->pos_y -= player->dir_y * player->move_speed;
	}
}

void	move_left_right(t_player *player, mlx_t *mlx, char **map)
{
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		if (map[(int)player->pos_y]
			[(int)(player->pos_x + player->plane_x * player->move_speed)]
			== '0')
			player->pos_x += player->plane_x * player->move_speed;
		if (map[(int)(player->pos_y + player->plane_y * player->move_speed)]
			[(int)player->pos_x] == '0')
			player->pos_y += player->plane_y * player->move_speed;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		if (map[(int)player->pos_y]
			[(int)(player->pos_x - player->plane_x * player->move_speed)]
			== '0')
			player->pos_x -= player->plane_x * player->move_speed;
		if (map[(int)(player->pos_y - player->plane_y * player->move_speed)]
			[(int)player->pos_x] == '0')
			player->pos_y -= player->plane_y * player->move_speed;
	}
}

void	key_press(void *param)
{
	t_data	*data;

	data = param;
	data->player->move_speed = 5 * data->mlx->delta_time;
	data->player->rot_speed = 1.5 * data->mlx->delta_time;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(EXIT_SUCCESS);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT_SHIFT))
		data->player->move_speed = data->player->move_speed * 2;
	rotate_left(data->player, data->mlx);
	rotate_right(data->player, data->mlx);
	move_up_down(data->player, data->mlx, data->map);
	move_left_right(data->player, data->mlx, data->map);
	create_image(data);
}
