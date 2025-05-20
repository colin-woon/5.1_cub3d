/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:35:45 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/20 19:43:03 by rteoh            ###   ########.fr       */
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

# define WIDTH 1200
# define HEIGHT 800

typedef	enum {
	NORTH,
	SOUTH,
	EAST,
	WEST
}	e_wall_direction;


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
	int		img_width;
	int		img_height;
}	t_img;

typedef struct	s_textures
{
	t_img		*imgs[4];
	int			*floor_rgb;
	int			*ceiling_rgb;
}	t_textures;

typedef struct	s_mlx {
	void	*ptr;
	void	*window;
	t_img	*img;
}	t_mlx;

typedef struct s_game
{
	t_mlx		*mlx_data;
	t_textures	*textures;
	t_map		*map;
} t_game;

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
int debug_event(int keycode, t_mlx *mlx);

// mlx.c
int	close_window(int keycode, t_mlx *mlx);
int	key_hook(int keysym, t_mlx *mlx);
void	start_mlx(t_game *game);

// mlx_colour_utils.c
int	create_trgb(int transparency, int red, int green, int blue);
int	get_transparency(int trgb);
int	get_red(int trgb);
int	get_green(int trgb);
int	get_blue(int trgb);

#endif
