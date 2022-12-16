/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ivork <ivork@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/13 02:14:25 by ivork         #+#    #+#                 */
/*   Updated: 2022/12/16 14:57:47 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* MLX42 */
# include "../MLX42/include/MLX42/MLX42.h"

/* Private libraries */
# include "structs.h"

/* Public libraries */
# include <math.h>
# include <stdlib.h>

# define SCREENWIDTH 1080
# define SCREENHEIGHT 1080
# define PI 3.141592653
# define FOV 70
# define RAD 0.0174532925

/* main.c */
int		create_image(t_data *data);

/* init_cub.c */
t_data	*init_data(t_cub *cub);

/* render.c */
void	color_background(t_data *data);
void	shoot_rays(t_data *data);

/* key_hook.c */
void	key_press(void *param);

/* textures.c */
void	build_wall(t_data *data, int x);

#endif
