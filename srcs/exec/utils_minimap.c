/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_minimap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:47:19 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/30 17:58:20 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_rect(t_img *img, t_minimap_vars *var, int color);
void	get_map_tiles_var(t_minimap_vars *var, t_map *map, \
int map_x_grid, int map_y_grid);
void	get_player_box_vars(t_minimap_vars *var, int player_x, int player_y);

void	get_map_tiles_var(t_minimap_vars *var, t_map *map, \
int map_x_grid, int map_y_grid)
{
	var->rect_x = MINIMAP_OFFSET_X + map_x_grid * MINIMAP_SCALE;
	var->rect_y = MINIMAP_OFFSET_Y + map_y_grid * MINIMAP_SCALE;
	if (map->grid[map_y_grid][map_x_grid] == WALL)
		var->color = MINIMAP_WALL_COLOR;
	else
		var->color = MINIMAP_FLOOR_COLOR;
	var->height = MINIMAP_SCALE;
	var->width = MINIMAP_SCALE;
}

void	get_player_box_vars(t_minimap_vars *var, int player_x, int player_y)
{
	var->rect_x = player_x - MINIMAP_PLAYER_SIZE / 2;
	var->rect_y = player_y - MINIMAP_PLAYER_SIZE / 2;
	var->width = MINIMAP_PLAYER_SIZE;
	var->height = MINIMAP_PLAYER_SIZE;
	var->color = MINIMAP_PLAYER_COLOR;
}

void	draw_minimap_rect(t_img *img, t_minimap_vars *var, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < var->height)
	{
		j = 0;
		while (j < var->width)
		{
			my_mlx_pixel_put(img, var->rect_x + j, var->rect_y + i, color);
			j++;
		}
		i++;
	}
}
