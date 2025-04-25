/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <ryan42cmp@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 13:41:06 by rteoh             #+#    #+#             */
/*   Updated: 2025/04/25 13:32:28 by rteoh            ###   ########.fr       */
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
# include "error.h"

typedef struct s_game
{
	void *mlx;
	void *mlx_win;
} t_game;

typedef struct s_texture
{
	char	*s_tex_file;
	char	*e_tex_file;
	char	*w_tex_file;
	char	*n_tex_file;
	
	void	*n_tex_img;
	void	*w_tex_img;	
	void	*e_tex_img;	
	void	*s_tex_img;	
	
	int		*floor_rgb;
	int		*ceiling_rgb;
}	t_texture;

char	*get_next_row(int fd);
bool	ft_strend(char *s, char *suffix);
int		open_file(char *path_to_file);
void	parse_map(char *path_to_cub, t_game *game);

#endif
