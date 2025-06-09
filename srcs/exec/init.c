/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:48:53 by cwoon             #+#    #+#             */
/*   Updated: 2025/06/09 21:22:29 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_player **player, t_map *map, t_game *game);
void	init_render_direction(t_player **player, t_wall_dir player_dir);

// 	(*player)->pos_x = DEBUG_PLAYER_POS_X;
// 	(*player)->pos_y = DEBUG_PLAYER_POS_Y;
void	init_player(t_player **player, t_map *map, t_game *game)
{
	*player = ft_calloc(1, sizeof(t_player));
	if (!player)
		error_msg_exit("Calloc Error: init player\n", game);
	(*player)->pos_x = map->player_y;
	(*player)->pos_y = map->player_x;
	init_render_direction(player, map->player_dir);
}

// int	debug_direction = DEBUG_RENDER_DIRECTION;
void	init_render_direction(t_player **player, t_wall_dir player_dir)
{
	if (player_dir == NORTH)
	{
		(*player)->dir_y = -1;
		(*player)->plane_x = FOV;
	}
	else if (player_dir == SOUTH)
	{
		(*player)->dir_y = 1;
		(*player)->plane_x = -FOV;
	}
	else if (player_dir == WEST)
	{
		(*player)->dir_x = -1;
		(*player)->plane_y = -FOV;
	}
	else if (player_dir == EAST)
	{
		(*player)->dir_x = 1;
		(*player)->plane_y = FOV;
	}
}
