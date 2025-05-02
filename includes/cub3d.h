/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:35:45 by cwoon             #+#    #+#             */
/*   Updated: 2025/04/30 21:58:35 by rteoh            ###   ########.fr       */
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


typedef struct s_game
{
	void 		*mlx;
	void 		*mlx_win;
	t_texture	*textures;
	t_map		*map;
} t_game;

char		*get_next_row(int fd);
bool		ft_strend(char *s, char *suffix);
int			open_file(char *path_to_file);
void		parse(char *path_to_cub, t_game *game);
void		parse_texture(char *line, t_game *game);


void	error_msg(char *err);
void	msg(char *err);
#endif
