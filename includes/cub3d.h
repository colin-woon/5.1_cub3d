/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <ryan42cmp@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:41:06 by rteoh             #+#    #+#             */
/*   Updated: 2025/04/28 15:58:04 by rteoh            ###   ########.fr       */
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

typedef struct s_texture
{	
	void	*n_tex_img; //no_img_ptr
	void	*w_tex_img;
	void	*e_tex_img;
	void	*s_tex_img;

	int		*floor_rgb;
	int		*ceiling_rgb;
}	t_texture;

typedef struct s_game
{
	void 		*mlx;
	void 		*mlx_win;
	t_texture	*textures;
	char		**map;
} t_game;

char		*get_next_row(int fd);
bool		ft_strend(char *s, char *suffix);
int			open_file(char *path_to_file);
void		parse(char *path_to_cub, t_game *game);
t_texture	*parse_texture(int fd, t_game *game);


void	error_msg(char *err);
void	msg(char *err);
#endif
