/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:48:53 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/21 19:51:35 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player(t_player **player);
void init_render_direction(t_player **player);

void init_player(t_player **player)
{
	*player = malloc(sizeof(t_player));
	ft_memset(*player, 0, sizeof(t_player));
	(*player)->pos_x = DEBUG_PLAYER_POS_X;
	(*player)->pos_y = DEBUG_PLAYER_POS_Y;
	init_render_direction(player);
}

void init_render_direction(t_player **player)
{
	int	debug_direction = DEBUG_RENDER_DIRECTION;

	if (debug_direction == NORTH)
	{
		(*player)->dir_x = -1;
		(*player)->plane_y = FOV;
	}
	else if (debug_direction == SOUTH)
	{
		(*player)->dir_x = 1;
		(*player)->plane_y = -FOV;
	}
	else if (debug_direction == WEST)
	{
		(*player)->dir_y = -1;
		(*player)->plane_x = -FOV;
	}
	else if (debug_direction == EAST)
	{
		(*player)->dir_y = 1;
		(*player)->plane_x = FOV;
	}
}
