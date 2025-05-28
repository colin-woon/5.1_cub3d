/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:48:53 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/27 20:45:12 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player(t_player **player, t_map *map);
void init_render_direction(t_player **player, t_wall_direction player_dir);

void init_player(t_player **player, t_map *map)
{

	*player = ft_calloc(1, sizeof(t_player));
	if (!player)
		error_msg_exit("Calloc Error: init player\n");
	(*player)->pos_x = map->player_x;
	(*player)->pos_y = map->player_y;
// 	(*player)->pos_x = DEBUG_PLAYER_POS_X;
// 	(*player)->pos_y = DEBUG_PLAYER_POS_Y;
	init_render_direction(player, map->player_dir);
}


void init_render_direction(t_player **player, t_wall_direction player_dir)
{
	int	debug_direction = DEBUG_RENDER_DIRECTION;

	if (player_dir == NORTH)
	{
		(*player)->dir_x = -1;
		(*player)->plane_y = FOV;
	}
	else if (player_dir == SOUTH)
	{
		(*player)->dir_x = 1;
		(*player)->plane_y = -FOV;
	}
	else if (player_dir == WEST)
	{
		(*player)->dir_y = -1;
		(*player)->plane_x = -FOV;
	}
	else if (player_dir == EAST)
	{
		(*player)->dir_y = 1;
		(*player)->plane_x = FOV;
	}
}
