/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:35:45 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/15 17:51:42 by cwoon            ###   ########.fr       */
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

# define WIDTH 1200
# define HEIGHT 800
# define MOVE_SPEED 0.15
# define ROTATION_SPEED 0.08
# define WALL_HEIGHT_SCALE 1

// DEBUG: TEMPORARY HARDCODED
#define DEBUG_MAP_WIDTH 24
#define DEBUG_MAP_HEIGHT 24
# define DEBUG_PLAYER_POS_X 3
# define DEBUG_PLAYER_POS_Y 3

enum wall_hit_side {
	VERTICAL,
	HORIZONTAL
};
typedef struct s_texture
{
	void	*no_img_ptr; //no_img_ptr
	void	*we_img_ptr;
	void	*ea_img_ptr;
	void	*so_img_ptr;

	int		*floor_rgb;
	int		*ceiling_rgb;
}	t_texture;


typedef	struct s_map
{
	int	map_height;
	int	map_width;

	char	**map_layout;


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
	int		is_wall_hit;
	int		wall_hit_side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_game
{
	t_mlx		*mlx_data;
	t_texture	*textures;
	t_player	*player;
	t_ray		*ray;
	// int		**map;
	int			map[DEBUG_MAP_HEIGHT][DEBUG_MAP_WIDTH];
}	t_game;

t_map	*parse_map(int fd, char *line, t_game *game);

char	*get_next_row(int fd);
bool	ft_strend(char *s, char *suffix);
int		open_file(char *path_to_file);
void	parse(char *path_to_cub, t_game *game);
void	parse_texture(char *line, t_game *game);


void	error_msg(char *err);
void	msg(char *err);

// debug.c
int debug_event(int keycode, t_mlx *mlx);

// mlx_movement_hooks.c
int	movement_keys(int keysym, t_game *game);

// mlx.c
int	close_window(int keycode, t_game *game);
void	start_mlx(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void init_mlx_img(t_mlx *mlx);
void draw_vertical_line(t_mlx *mlx, int x, int from, int to, int color);
void init_floor_and_ceiling(t_mlx *mlx, int color);

// init.c
void init_player(t_player **player);

// utils_cleanup.c
void	cleanup(t_game *game);

void run_raycasting(t_ray *ray, t_player *player, t_mlx *mlx, t_game *game);


// mlx_colour_utils.c
int	create_trgb(int transparency, int red, int green, int blue);
int	get_transparency(int trgb);
int	get_red(int trgb);
int	get_green(int trgb);
int	get_blue(int trgb);
#endif
