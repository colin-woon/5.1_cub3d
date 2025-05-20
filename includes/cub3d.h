/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:35:45 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/20 16:46:51 by rteoh            ###   ########.fr       */
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
}	t_img;


typedef struct s_texture
{
	void	*no_img_ptr; //no_img_ptr
	void	*we_img_ptr;
	void	*ea_img_ptr;
	void	*so_img_ptr;

	t_img	*no_img_info;
	t_img	*we_img_info;
	t_img	*ea_img_info;
	t_img	*so_img_info;

	int		*floor_rgb;
	int		*ceiling_rgb;
}	t_texture;

typedef struct	s_mlx {
	void	*ptr;
	void	*window;
	t_img	*img;
}	t_mlx;

typedef struct s_game
{
	t_mlx		*mlx_data;
	t_texture	*textures;
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
