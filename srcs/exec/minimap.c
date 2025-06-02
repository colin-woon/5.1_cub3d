/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:47:21 by cwoon             #+#    #+#             */
/*   Updated: 2025/06/02 21:32:59 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player_line(t_player *player, t_mlx *mlx, \
int player_minimap_x, int player_minimap_y);
void	draw_player_box(t_player *player, t_mlx *mlx);
void	draw_map_tiles(t_map *map, t_mlx *mlx);
void	draw_minimap(t_mlx *mlx, t_game *game, t_player *player);

void	draw_minimap(t_mlx *mlx, t_game *game, t_player *player)
{
	draw_map_tiles(game->map, mlx);
	draw_player_box(player, mlx);
}

// Determine tile color based on map data
// Assuming anything not a WALL is a floor/empty space
// Draw the scaled tile as a rectangle
// Ensure this doesn't draw outside the screen or minimap boundaries if desired
// For now, it will draw if the top-left of the tile is on screen
void	draw_map_tiles(t_map *map, t_mlx *mlx)
{
	int				map_x_grid;
	int				map_y_grid;
	t_minimap_vars	var;

	map_y_grid = 0;
	while (map_y_grid < map->height)
	{
		map_x_grid = 0;
		while (map_x_grid < map->width)
		{
			get_map_tiles_var(&var, map, map_x_grid, map_y_grid);
			draw_minimap_rect(mlx->img, &var, var.color);
			map_x_grid++;
		}
		map_y_grid++;
	}
}

void	draw_player_box(t_player *player, t_mlx *mlx)
{
	int				player_minimap_x;
	int				player_minimap_y;
	t_minimap_vars	var;

	player_minimap_y = MINIMAP_OFFSET_Y + (int)(player->pos_y * MINIMAP_SCALE);
	player_minimap_x = MINIMAP_OFFSET_X + (int)(player->pos_x * MINIMAP_SCALE);
	get_player_box_vars(&var, player_minimap_x, player_minimap_y);
	draw_minimap_rect(mlx->img, &var, var.color);
	draw_player_line(player, mlx, player_minimap_x, player_minimap_y);
}

// Simple line drawing (draw a few pixels along the vector)
// For a more precise line, you'd use an algorithm like Bresenham's.
// This is a simplified version for a short line.
void	draw_player_line(t_player *player, t_mlx *mlx, \
int player_minimap_x, int player_minimap_y)
{
	double	dx;
	double	dy;
	int		i;
	int		px;
	int		py;

	dx = player->dir_x;
	dy = player->dir_y;
	i = 0;
	while (i < MINIMAP_RAY_LENGTH)
	{
		px = player_minimap_x + (int)(dx * i);
		py = player_minimap_y + (int)(dy * i);
		my_mlx_pixel_put(mlx->img, px, py, MINIMAP_VIEW_CONE_COLOR);
		i++;
	}
}
