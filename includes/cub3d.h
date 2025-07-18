/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:35:45 by cwoon             #+
#include "cub3d.h"#    #+#             */
/*   Updated: 2025/05/30 18:11:00 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>

# define SCREEN_WIDTH 2000
# define SCREEN_HEIGHT 2000
# define MOVE_SPEED 0.15
# define COLLISION_BUFFER 0.25
# define ROTATION_SPEED 0.08
# define FOV 0.66
# define WALL_HEIGHT_SCALE 1.5

# define MOUSE_SENSITIVITY_X 0.0002
# define MOUSE_SENSITIVITY_Y 0.2
// Needed so the player wont look infinitely up or down
# define MAX_PITCH_PIXELS SCREEN_HEIGHT

// --- Minimap Constants ---
// Pixels from the left edge of the screen
// Pixels from the top edge of the screen
// Screen pixels per map grid unit (e.g., 8px per tile)
# define MINIMAP_OFFSET_X 20
# define MINIMAP_OFFSET_Y 20
# define MINIMAP_SCALE 8

// Colors for the minimap (ARGB format, assuming 0xAARRGGBB or 0x00RRGGBB)
// If your mlx_pixel_put uses a different color format, adjust these.
# define MINIMAP_WALL_COLOR   0x00808080 // Gray
# define MINIMAP_FLOOR_COLOR  0x00404040 // Dark Gray
# define MINIMAP_PLAYER_COLOR 0x00FF0000 // Red
# define MINIMAP_PLAYER_SIZE  10        // Player dot
# define MINIMAP_VIEW_CONE_COLOR 0x00FFFF00 // Yellow view direction
# define MINIMAP_RAY_LENGTH   20       // player view ray length

typedef enum e_wall_direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_wall_dir;

typedef enum e_wall_hit_side
{
	VERTICAL,
	HORIZONTAL
}	t_wall_hit_side;

typedef enum e_is_wall
{
	NO_WALL,
	WALL,
}	t_is_wall;

typedef struct s_map
{
	char		**layout;
	int			**grid;
	int			height;
	int			width;
	int			player_x;
	int			player_y;
	t_wall_dir	player_dir;
}	t_map;

typedef struct s_img
{
	void	*ptr;
	char	*address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_assets
{
	t_img	textures[4];
	int		*floor_rgb;
	int		*ceiling_rgb;
}	t_assets;

typedef struct s_mlx
{
	void	*ptr;
	void	*window;
	t_img	*img;
}	t_mlx;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	pitch;
}	t_player;

typedef struct s_raycasting
{
	double	camera_x;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perpendicular_wall_distance;
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
	t_map		*map;
	t_player	*player;
	t_ray		*ray;
	bool		is_render;
}	t_game;
	// int			last_mouse_x;
	// int			mouse_initialized;

typedef struct s_texture_vars
{
	int		x;
	int		y;
	double	pos;
	double	step;
	int		color;
}	t_texture_vars;

typedef struct s_minimap_vars
{
	int	rect_x;
	int	rect_y;
	int	width;
	int	height;
	int	color;
}	t_minimap_vars;

typedef struct s_mouse_vars
{
	int		screen_center_x;
	int		screen_center_y;
	double	delta_x;
	double	delta_y;
	double	rotation_angle_yaw;
}	t_mouse_vars;

typedef struct s_movement_vars
{
	double	move_x;
	double	move_y;
	double	potential_x;
	double	potential_y;
}	t_movement_vars;

// parse/utils.c
void		get_map_grid(t_map *map);
char		*get_next_row(int fd);
bool		ft_strend(char *s, char *suffix);
int			open_file(char *path_to_file);
void		get_map_grid(t_map *map);

// check_valid_map_utils.c
char		*fill_str_sp\
(char *row, int row_width, int max_width, t_game *game);
int			ft_strlen_pro(char *line);
void		save_player(t_map *map, int y, int x, char dir);

// parse_map_utils.c
bool		check_above_wall(char **rows, int i, int j);
bool		check_wall_behind(char *row, int i);
bool		ft_iszero(char c);
bool		ft_isplayer(char c);
bool		ft_iswall(int c);

// check_valid_map.c
void		make_map_square(t_map *map, t_game *game);
bool		check_valid_map(t_map *map, t_game *game);
bool		get_map_width(t_map *map);
bool		check_player(t_map *map);

// check_valid_map2.c
bool		check_horizontal_walls(t_map *map);
bool		check_vertical_walls(t_map	*map);
bool		check_vertical_blocks(char **blocks);
void		free_blocks(char **blocks);

// parse.c
bool		parse(char *path_to_cub, t_game *game);

// parse_texture.c
bool		check_texture_complete(t_assets *assets);
t_assets	*init_assets(t_game *game);
bool		parse_texture(char *line, t_game *game);

// parse_texture_utils.c
bool		init_rgb(char *rgb_c, int **rgb_ptr, t_game *game);
void		fill_img_info(void *img_ptr, t_img *img);
char		*get_file_path(char *line);
void		make_img(char *str, t_game *game, t_img *texture);

//parse_texture_utils2.c
bool		check_rgb(int	*rgb);

// parse_map.c
void		store_map(char *line, t_map *map, int map_height, t_game *game);
char		*conv_tab(char *line, t_game *game);
bool		parse_map(int fd, char *line, t_game *game);

// error.c
bool		error_msg(char *err);
void		msg(char *err);
void		error_msg_exit(char *err, t_game *game);

// mlx.c
int			close_window(t_game *game);
void		start_mlx(t_game *game);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);
void		init_mlx_img(t_mlx *mlx);

// hooks_movement.c
int			movement_keys(int keysym, t_game *game);
bool		is_valid_keys(int keysym);
void		recalculate_variables\
(t_game *game, t_map *map, t_player *player, int keysym);

// hooks_movement_calc.c
void		move_left_or_right\
(int keysym, t_player *player, t_game *game, t_map *map);
void		move_forward_or_backward\
(int keysym, t_player *player, t_game *game, t_map *map);
void		look_left_or_right(int keysym, t_player *player, t_game *game);
void		look_left(t_player *player, t_game *game);
void		look_right(t_player *player, t_game *game);
void		validate_movement\
(t_player *player, t_map *map, t_movement_vars *var);

// hooks_mouse.c
int			mouse_hook(int x, int y, t_game *game);
void		rotate_player(t_player *player, double angle);
void		rotate_horizontally\
(t_game *game, int *x, t_mouse_vars *var, bool *mouse_moved);
void		rotate_vertically\
(t_game *game, int *y, t_mouse_vars *var, bool *mouse_moved);
void		init_mouse_vars(t_mouse_vars *var, int *x, int *y);

// init.c
void		init_player(t_player **player, t_map *map, t_game *game);

// free.c
void		cleanup(t_game *game);

// raycasting.c
void		run_raycasting\
(t_ray *ray, t_player *player, t_mlx *mlx, t_game *game);
void		init_ray_dir_n_map_pos\
(t_game *game, int x, int *map_x, int *map_y);
void		draw_wall_texture\
(t_img *texture, double wall_x, t_game *game, int *x);
void		calculate_wall_projection(t_ray *ray, t_player *player);
void		calculate_pitch_offset(t_player *player, t_ray *ray);

// draw_floor_ceiling.c
void		draw_floor(int *y_row, t_ray *ray, t_game *game, int *x_col);
void		draw_ceiling(int *y_row, t_ray *ray, t_game *game, int *x_col);
int			get_ceiling_colour(t_game *game);
int			get_floor_colour(t_game *game);

// dda.c
void		run_dda(t_ray *ray, t_game *game, int *map_x, int *map_y);
void		calculate_step_n_init_side_dist\
(t_ray *ray, t_player *player, int map_x, int map_y);
void		calculate_point_gap(t_ray *ray);

// textures.c
int			get_texture_pixel(t_img *texture, int x, int y);
double		get_fractional_texture_position_x\
(t_ray *ray, t_player *player);
t_wall_dir	get_wall_dir(t_ray *ray);
void		put_texture_pixels\
(t_texture_vars *tex, t_img *texture, t_game *game, int *x);
void		prep_texture_vars\
(t_texture_vars *tex, t_img *texture, t_ray *ray, t_player *player);

// minimap.c
void		draw_player_line(t_player *player, t_mlx *mlx, \
int player_minimap_x, int player_minimap_y);
void		draw_player_box(t_player *player, t_mlx *mlx);
void		draw_map_tiles(t_map *map, t_mlx *mlx);
void		draw_minimap(t_mlx *mlx, t_game *game, t_player *player);

// utils_minimap.c
void		draw_minimap_rect(t_img *img, t_minimap_vars *var, int color);
void		get_map_tiles_var(t_minimap_vars *var, t_map *map, \
int map_x_grid, int map_y_grid);
void		get_player_box_vars\
(t_minimap_vars *var, int player_x, int player_y);

// mlx/utils_colour.c
int			create_trgb(int transparency, int red, int green, int blue);
int			get_transparency(int trgb);
int			get_red(int trgb);
int			get_green(int trgb);
int			get_blue(int trgb);

#endif
