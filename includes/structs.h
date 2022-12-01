/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   structs.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kgajadie <kgajadie@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/26 12:07:43 by kgajadie      #+#    #+#                 */
/*   Updated: 2022/12/01 16:19:35 by ivork         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

/* Public libraries */
# include <stdbool.h>

/* MLX42 */
#include "../MLX42/include/MLX42/MLX42.h"

#define screenWidth 624
#define screenHeight 624
#define PI 3.141592653
#define FOV 70
#define RAD 0.0174532925

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
	char	**no_path;
	char	**so_path;
	char	**we_path;
	char	**ea_path;
	t_rgb	floor;
	t_rgb	ceiling;
}	t_cub;

/*graphics*/

typedef struct	s_player{
	double	posX;
	double	posY;
	double	deltaX;
	double	deltaY;
	double	angle;
	double	hitX;
	double	hitY;
	double  distance;
}				t_player;

typedef struct		s_textures{
	mlx_texture_t*	texture;
	mlx_texture_t*	texture_N;
	mlx_texture_t*	texture_S;
	mlx_texture_t*	texture_W;
	mlx_texture_t*	texture_E;
}					t_textures;


typedef struct	s_data {
	t_player	*settings;
	t_textures	*textures;
	mlx_t		*mlx;
	void		*win;
	mlx_image_t	*img;
	mlx_image_t	*map_img;
	char		**map;
	int			mapHeigth;
	int			mapwidth;
}				t_data;


#endif
