/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_n_ceiling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:32:24 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/27 20:34:01 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_n_ceiling(t_mlx *mlx, int floor_colour, int ceiling_colour);
int		get_ceiling_colour(t_game *game);
int		get_floor_colour(t_game *game);

void	draw_floor_n_ceiling(t_mlx *mlx, int floor_colour, int ceiling_colour)
{
	int x;
	int y;

	x = 0;
	while (x < SCREEN_HEIGHT/2)
	{
		y = 0;
		while (y < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(mlx->img, y, x, ceiling_colour);
			y++;
		}
		x++;
	}
	while (x < SCREEN_HEIGHT)
	{
		y = 0;
		while (y < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(mlx->img, y, x, floor_colour);
			y++;
		}
		x++;
	}
}

int	get_floor_colour(t_game *game)
{
	return(create_trgb(0, \
		game->assets->floor_rgb[0], \
		game->assets->floor_rgb[1], \
		game->assets->floor_rgb[2]));
}

int	get_ceiling_colour(t_game *game)
{
	return(create_trgb(0, \
		game->assets->ceiling_rgb[0], \
		game->assets->ceiling_rgb[1], \
		game->assets->ceiling_rgb[2]));
}
