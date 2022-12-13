/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_hook.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 00:55:31 by ivork         #+#    #+#                 */
/*   Updated: 2022/12/13 02:54:07 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../libft/libft.h"
#include <math.h>

static void	rotate_player(t_player *player, mlx_t *mlx)
{
	double	old_dir_x;
	double	old_plane_x;

	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	{
		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(0.1) - player->dir_y * sin(0.1);
		player->dir_y = old_dir_x * sin(0.1) + player->dir_y * cos(0.1);
		old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(0.1) - player->plane_y * sin(0.1);
		player->plane_y = old_plane_x * sin(0.1) + player->plane_y * cos(0.1);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(-0.1) - player->dir_y * sin(-0.1);
		player->dir_y = old_dir_x * sin(-0.1) + player->dir_y * cos(-0.1);
		old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(-0.1)
			- player->plane_y * sin(-0.1);
		player->plane_y = old_plane_x * sin(-0.1) + player->plane_y * cos(-0.1);
	}
}

static void	move_up_down(t_player *player, mlx_t *mlx, char **map)
{
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		if (map[(int)player->pos_y][(int)(player->pos_x + player->dir_x * 0.1)]
			== '0')
			player->pos_x += player->dir_x * 0.1;
		if (map[(int)(player->pos_y + player->dir_y * 0.1)][(int)player->pos_x]
			== '0')
			player->pos_y += player->dir_y * 0.1;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		if (map[(int)player->pos_y][(int)(player->pos_x - player->dir_x * 0.1)]
			== '0')
			player->pos_x -= player->dir_x * 0.1;
		if (map[(int)(player->pos_y - player->dir_y * 0.1)][(int)player->pos_x]
			== '0')
			player->pos_y -= player->dir_y * 0.1;
	}
}

void	move_left_right(t_player *player, mlx_t *mlx, char **map)
{
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		if (map[(int)player->pos_y][(int)(player->pos_x - player->dir_x * 0.1)]
			== '0')
			player->pos_x -= player->dir_x * 0.1;
		if (map[(int)(player->pos_y + player->dir_y * 0.1)][(int)player->pos_x]
			== '0')
			player->pos_y += player->dir_y * 0.1;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		if (map[(int)player->pos_y][(int)(player->pos_x + player->dir_x * 0.1)]
			== '0')
			player->pos_x += player->dir_x * 0.1;
		if (map[(int)(player->pos_y - player->dir_y * 0.1)][(int)player->pos_x]
			== '0')
			player->pos_y -= player->dir_y * 0.1;
	}
}

void	key_press(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(EXIT_SUCCESS);
	rotate_player(data->player, data->mlx);
	move_up_down(data->player, data->mlx, data->map);
	move_left_right(data->player, data->mlx, data->map);
	create_image(data);
}
