/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 12:07:43 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/12/13 14:24:38 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/* Public libraries */
# include <stdbool.h>

/* MLX42 */
# include "../MLX42/include/MLX42/MLX42.h"

/* parser */
typedef struct s_stl_data
{
	const char	*s;
	long		acc;
	long		cutoff;
	int			c;
	int			neg;
	int			any;
	int			cutlim;
}	t_stl_data;

typedef struct s_map_element
{
	char					*map_element;
	int						type;
	int						sub_type;
	struct s_map_element	*next;
}	t_map_element;

typedef struct s_stack
{
	int				cr;
	int				cc;
	struct s_stack	*next;
}	t_stack;

typedef struct s_has_c
{
	bool	has_no;
	bool	has_so;
	bool	has_we;
	bool	has_ea;
}	t_has_c;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_cub
{
	int		rows;
	int		cols;
	char	**map;
	int		start_pos[2];
	char	orientation;
	char	**no_path;
	char	**so_path;
	char	**we_path;
	char	**ea_path;
	t_rgb	floor;
	t_rgb	ceiling;
}	t_cub;

/*graphics*/

typedef struct s_player{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	char	orientation;
	double  move_speed;
	double  rot_speed;
}				t_player;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	delta_x;
	double	delta_y;
	double	next_x;
	double	next_y;
	double	step_x;
	double	step_y;
	double	distance;
	int		map_x;
	int		map_y;
	int		side;
}				t_ray;

typedef struct s_textures{
	mlx_texture_t	*texture;
	mlx_texture_t	*texture_north;
	mlx_texture_t	*texture_south;
	mlx_texture_t	*texture_west;
	mlx_texture_t	*texture_east;
	double			x;
	double			y;
	double			step_y;
	double			y_offset;
}					t_textures;

typedef struct s_data {
	t_player	*player;
	t_textures	*textures;
	t_ray		*ray;
	mlx_t		*mlx;
	void		*win;
	mlx_image_t	*img;
	mlx_image_t	*map_img;
	char		**map;
	int			map_heigth;
	int			map_width;
	t_rgb		floor;
	t_rgb		ceiling;
}				t_data;

#endif
