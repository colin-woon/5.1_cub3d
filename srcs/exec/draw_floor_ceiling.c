/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceiling.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:32:24 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/27 20:34:01 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor(int *y_row, t_ray *ray, t_game *game, int *x_col);
void	draw_ceiling(int *y_row, t_ray *ray, t_game *game, int *x_col);
int		get_ceiling_colour(t_game *game);
int		get_floor_colour(t_game *game);

void	draw_ceiling(int *y_row, t_ray *ray, t_game *game, int *x_col)
{
	*y_row = 0;
	while (*y_row < ray->draw_start)
	{
		my_mlx_pixel_put(game->mlx_data->img, *x_col, *y_row, get_ceiling_colour(game));
		(*y_row)++;
	}
}

// Ensure *y_row starts validly; if ray->draw_end was SCREEN_HEIGHT - 1,
// *y_row would be SCREEN_HEIGHT, and the loop condition *y_row < SCREEN_HEIGHT would be false.
// This is correct, as no floor would be drawn in that case.
void	draw_floor(int *y_row, t_ray *ray, t_game *game, int *x_col)
{
	*y_row = ray->draw_end + 1;
	while (*y_row < SCREEN_HEIGHT)
	{
		my_mlx_pixel_put(game->mlx_data->img, *x_col, *y_row, get_floor_colour(game));
		(*y_row)++;
	}
}

int	get_floor_colour(t_game *game)
{
	return (create_trgb(0, \
game->assets->floor_rgb[0], \
game->assets->floor_rgb[1], \
game->assets->floor_rgb[2]));
}

int	get_ceiling_colour(t_game *game)
{
	return (create_trgb(0, \
game->assets->ceiling_rgb[0], \
game->assets->ceiling_rgb[1], \
game->assets->ceiling_rgb[2]));
}
