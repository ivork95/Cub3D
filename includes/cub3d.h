#ifndef CUBED_H
# define CUBED_H
# include "../mlx/mlx.h"

#define mapWidth 24
#define mapHeight 24
#define texWidth 64
#define texHeight 64
#define screenWidth 624
#define screenHeight 624
#define UP 13
#define DOWN 1
#define LEFT 0
#define RIGHT 2
#define PI 3.141592653
#define FOV 70
#define RAD 0.0174532925
#define ROTATE_L 123
#define ROTATE_R 124

typedef struct	s_win {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_win;

typedef struct	s_settings {
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	deltaX;
	double	deltaY;
	double	angle;
	double	planeX;
	double	planeY;
	void	*mlx;
	void	*win;
	t_win	img;
	int		**map;
}				t_settings;


t_settings	*init_window(void);
void		create_top_view(t_settings *data);
void		init_player(t_settings *data);
void		my_mlx_pixel_put(t_win *data, int x, int y, int color);
void		draw_sky(t_settings *data);
void		draw_ground(t_settings *data);
void		draw_player(t_settings *data);

#endif