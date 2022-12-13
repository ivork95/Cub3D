/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_hook.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/12 00:55:31 by ivork         #+#    #+#                 */
/*   Updated: 2022/12/13 02:13:24 by ivork         ########   odam.nl         */
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
		old_dir_x = player->dirX;
		player->dirX = player->dirX * cos(0.1) - player->dirY * sin(0.1);
		player->dirY = old_dir_x * sin(0.1) + player->dirY * cos(0.1);
		old_plane_x = player->planeX;
		player->planeX = player->planeX * cos(0.1) - player->planeY * sin(0.1);
		player->planeY = old_plane_x * sin(0.1) + player->planeY * cos(0.1);
	}
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		old_dir_x = player->dirX;
		player->dirX = player->dirX * cos(-0.1) - player->dirY * sin(-0.1);
		player->dirY = old_dir_x * sin(-0.1) + player->dirY * cos(-0.1);
		old_plane_x = player->planeX;
		player->planeX = player->planeX * cos(-0.1)
			- player->planeY * sin(-0.1);
		player->planeY = old_plane_x * sin(-0.1) + player->planeY * cos(-0.1);
	}
}

static void	move_up_down(t_player *player, mlx_t *mlx, char **map)
{
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		if (map[(int)player->posY][(int)(player->posX + player->dirX * 0.1)]
			== '0')
			player->posX += player->dirX * 0.1;
		if (map[(int)(player->posY + player->dirY * 0.1)][(int)player->posX]
			== '0')
			player->posY += player->dirY * 0.1;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		if (map[(int)player->posY][(int)(player->posX - player->dirX * 0.1)]
			== '0')
			player->posX -= player->dirX * 0.1;
		if (map[(int)(player->posY - player->dirY * 0.1)][(int)player->posX]
			== '0')
			player->posY -= player->dirY * 0.1;
	}
}

void	move_left_right(t_player *player, mlx_t *mlx, char **map)
{
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		if (map[(int)player->posY][(int)(player->posX - player->dirX * 0.1)]
			== '0')
			player->posX -= player->dirX * 0.1;
		if (map[(int)(player->posY + player->dirY * 0.1)][(int)player->posX]
			== '0')
			player->posY += player->dirY * 0.1;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		if (map[(int)player->posY][(int)(player->posX + player->dirX * 0.1)]
			== '0')
			player->posX += player->dirX * 0.1;
		if (map[(int)(player->posY - player->dirY * 0.1)][(int)player->posX]
			== '0')
			player->posY -= player->dirY * 0.1;
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
