/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:35:45 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/27 20:13:02 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include "libft.h"
# include <fcntl.h> //for the open
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>

# define SCREEN_WIDTH 1200
# define SCREEN_HEIGHT 800
# define MOVE_SPEED 0.15
# define ROTATION_SPEED 0.08
# define FOV 0.66
# define WALL_HEIGHT_SCALE 1

typedef enum {
    NORTH,
    SOUTH,
    EAST,
    WEST
} e_wall_direction;

// DEBUG: TEMPORARY HARDCODED
#define DEBUG_RENDER_DIRECTION NORTH
#define DEBUG_MAP_WIDTH 24
#define DEBUG_MAP_HEIGHT 24
#define DEBUG_PLAYER_POS_X 3
#define DEBUG_PLAYER_POS_Y 3

typedef enum {
	VERTICAL,
	HORIZONTAL
} e_wall_hit_side;

typedef	struct s_map
{
	char				**layout;
	int					**grid;
	int					height;
	int					width;
	int					player_x;
	int					player_y;
	e_wall_direction	player_dir;
}	t_map;

typedef struct s_img {
	void	*ptr;
	char	*address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct	s_assets
{
	t_img		*textures[4];
	int			*floor_rgb;
	int			*ceiling_rgb;
}	t_assets;

typedef struct	s_mlx {
	void	*ptr;
	void	*window;
	t_img	*img;
}	t_mlx;

typedef struct	s_player {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct	s_raycasting {
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	prependicular_wall_distance;
	int		step_x;
	int		step_y;
	int		wall_hit_side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_game
{
	t_mlx		*mlx_data;
	t_assets	*assets;
	t_map		*map;// here, you can comment my parsing out if not using
	t_player	*player;
	t_ray		*ray;
	int			debug_map[DEBUG_MAP_HEIGHT][DEBUG_MAP_WIDTH];
	bool		is_render;
}	t_game;

bool	parse_map(int fd, char *line, t_game *game);

char	*get_next_row(int fd);
bool	ft_strend(char *s, char *suffix);
int		open_file(char *path_to_file);
bool	parse(char *path_to_cub, t_game *game);
bool	parse_texture(char *line, t_game *game);

bool	error_msg(char *err);
void	msg(char *err);
void	error_msg_exit(char *err);

// debug.c
void	DEBUG_init_map(t_game *game);
void	DEBUG_print_map_assets(t_game *game);
int debug_event(int keycode, t_mlx *mlx);

// mlx_movement_hooks.c
int	movement_keys(int keysym, t_game *game);

// mlx.c
int	close_window(int keycode, t_game *game);
void	start_mlx(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void init_mlx_img(t_mlx *mlx);
void draw_vertical_line(t_mlx *mlx, int x, int from, int to, int color);
void init_floor_and_ceiling(t_mlx *mlx, int floor_colour, int ceiling_colour);

// init.c
void init_player(t_player **player, t_map *map);

// utils_cleanup.c
void	cleanup(t_game *game);

// raycasting.c
void	run_raycasting(t_ray *ray, t_player *player, t_mlx *mlx, t_game *game);
int		get_texture_pixel(t_img *texture, int x, int y);
void	draw_wall_texture(t_img *texture, double wall_x, t_ray *ray, t_mlx *mlx, int *x);
double	get_fractional_texture_position_x(t_ray *ray, t_player *player);
void	calculate_line_height(t_ray *ray);
void	run_DDA(t_ray *ray, t_game *game, int *map_x, int *map_y);
void	calculate_step_n_init_side_dist(t_ray *ray, t_player *player, int map_x, int map_y);
void	calculate_point_gap(t_ray *ray);
void	init_ray_dir_n_map_pos(t_game *game, int x, int *map_x, int *map_y);
e_wall_direction	get_wall_direction(t_ray *ray);
int	get_ceiling_colour(t_game *game);
int	get_floor_colour(t_game *game);

// mlx_colour_utils.c
int	create_trgb(int transparency, int red, int green, int blue);
int	get_transparency(int trgb);
int	get_red(int trgb);
int	get_green(int trgb);
int	get_blue(int trgb);

#endif
