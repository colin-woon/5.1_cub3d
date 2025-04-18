/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:35:45 by cwoon             #+#    #+#             */
/*   Updated: 2025/04/14 19:01:49 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include "libft.h"
# include <X11/X.h>
# include <X11/keysym.h>

# define WIDTH 1200
# define HEIGHT 800

typedef struct s_img {
	void	*ptr;
	char	*address;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct	s_mlx {
	void	*ptr;
	void	*window;
	t_img	*img;
}	t_mlx;


// debug.c
int debug_event(int keycode, t_mlx *mlx);

// mlx.c
int	close_window(int keycode, t_mlx *mlx);
int	key_hook(int keysym, t_mlx *mlx);
void	start_mlx();

// mlx_colour_utils.c
int	create_trgb(int transparency, int red, int green, int blue);
int	get_transparency(int trgb);
int	get_red(int trgb);
int	get_green(int trgb);
int	get_blue(int trgb);


#endif
