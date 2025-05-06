/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:48:53 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/06 16:18:39 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_player(t_player **player);

void init_player(t_player **player)
{
	*player = malloc(sizeof(t_player));
	(*player)->pos_x = DEBUG_PLAYER_POS_X;
	(*player)->pos_y = DEBUG_PLAYER_POS_Y;
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
