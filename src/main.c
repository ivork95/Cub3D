/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 00:08:19 by ivork         #+#    #+#                 */
/*   Updated: 2022/12/13 14:08:44 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "../includes/cub3d.h"
#include "../includes/tokenize.h"

int	create_image(t_data *data)
{
	mlx_delete_image(data->mlx, data->img);
	data->img = mlx_new_image(data->mlx, SCREENWIDTH, SCREENHEIGHT);
	color_background(data);
	shoot_rays(data);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	return (1);
}

int	main(int argc, char *argv[argc + 1])
{
	t_data	*data;
	t_cub	*cub;

	if (argc != 2)
		put_exit_fail("Error: Invalid amount of arguments\n");
	cub = read_file(argv[argc - 1]);
	data = init_data(cub);
	mlx_loop_hook(data->mlx, &key_press, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}
