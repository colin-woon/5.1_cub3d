/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_movement_calc_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:22:03 by cwoon             #+#    #+#             */
/*   Updated: 2025/06/17 16:31:15 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	validate_movement(t_player *player, t_map *map, t_movement_vars *var);

// We use a small buffer in the direction of movement to prevent clipping.
void	validate_movement(t_player *player, t_map *map, t_movement_vars *var)
{
	int	check_x;
	int	check_y;

	if (var->move_x > 0)
		check_x = (int)(player->pos_x + var->move_x + COLLISION_BUFFER);
	else
		check_x = (int)(player->pos_x + var->move_x - COLLISION_BUFFER);
	if (map->grid[(int)player->pos_y][check_x] == NO_WALL)
		player->pos_x = var->potential_x;
	if (var->move_y > 0)
		check_y = (int)(player->pos_y + var->move_y + COLLISION_BUFFER);
	else
		check_y = (int)(player->pos_y + var->move_y - COLLISION_BUFFER);
	if (map->grid[check_y][(int)player->pos_x] == NO_WALL)
		player->pos_y = var->potential_y;
}
