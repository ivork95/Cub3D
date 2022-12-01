#ifndef CUBED_H
# define CUBED_H
// # include "../mlx/mlx.h"
#include "../MLX42/include/MLX42/MLX42.h"
#include "structs.h"





t_data	*init_window(void);
void		create_top_view(t_data *data);
void		init_player_settings(t_data *data, t_cub *cub);
void		draw_sky(t_data *data);
void		draw_ground(t_data *data);
void		draw_player(t_data *data);
void		draw_line(t_data *data, double angle, double line_lenght, long color);
void		render_screen(t_data *data, int x, double angle);
void		shoot_rays(t_data *data);
void		key_press(void *param);
void 		my_keyhook(mlx_key_data_t keydata, void* param);
int			create_image(t_data *data);
double		get_ray_length_y(t_data *data, double angle);
double		get_ray_length_x(t_data *data, double angle);

#endif