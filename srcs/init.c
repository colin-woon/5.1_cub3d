/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:48:53 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/27 15:00:15 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player(t_player **player, t_map *map);

void init_player(t_player **player, t_map *map)
{
	*player = ft_calloc(1, sizeof(t_player));
	if (!player)
		error_msg_exit("Calloc Error: init player\n");
	(*player)->pos_x = map->player_x;
	(*player)->pos_y = map->player_y;
	(*player)->dir_x = -1;
	(*player)->dir_y = 0;
	(*player)->plane_x = 0;
	(*player)->plane_y = 0.66;


	// DEBUG
	// printf("\n--- Player Initial Values ---\n");
    // printf("Position: (x: %.2f, y: %.2f)\n", (*player)->pos_x, (*player)->pos_y);
    // printf("Direction: (x: %.2f, y: %.2f)\n", (*player)->dir_x, (*player)->dir_y);
    // printf("Camera Plane: (x: %.2f, y: %.2f)\n", (*player)->plane_x, (*player)->plane_y);
    // printf("---------------------------\n\n");
}
