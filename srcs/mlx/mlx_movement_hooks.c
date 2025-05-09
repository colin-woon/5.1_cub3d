/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_movement_hooks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:43:47 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/06 17:00:35 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	movement_keys(int keysym, t_game *game);

int	movement_keys(int keysym, t_game *game)
{
	// printf("DEBUG: sym INT is %d\n", keysym);
	printf("DEBUG: sym HEXA is %x\n", keysym);
	// REFACTOR: exit
	if (keysym == XK_Escape)
	{
		printf("DEBUG: Escape\n");
		close_window(0, game);
	}
	// REFACTOR: look left
	else if (keysym == XK_Left)
	{
		double old_dirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(ROTATION_SPEED) - game->player->dir_y * sin(ROTATION_SPEED);
		game->player->dir_y = old_dirX * sin(ROTATION_SPEED) + game->player->dir_y * cos(ROTATION_SPEED);
		double oldPlaneX = game->player->plane_x;
		game->player->plane_x = game->player->plane_x * cos(ROTATION_SPEED) - game->player->plane_y * sin(ROTATION_SPEED);
		game->player->plane_y = oldPlaneX * sin(ROTATION_SPEED) + game->player->plane_y * cos(ROTATION_SPEED);
		printf("Left\n");
	}
	// REFACTOR: look right
	else if (keysym == XK_Right)
	{
		double oldDirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(-ROTATION_SPEED) - game->player->dir_y * sin(-ROTATION_SPEED);
		game->player->dir_y = oldDirX * sin(-ROTATION_SPEED) + game->player->dir_y * cos(-ROTATION_SPEED);
		double oldPlaneX = game->player->plane_x;
		game->player->plane_x = game->player->plane_x * cos(-ROTATION_SPEED) - game->player->plane_y * sin(-ROTATION_SPEED);
		game->player->plane_y = oldPlaneX * sin(-ROTATION_SPEED) + game->player->plane_y * cos(-ROTATION_SPEED);
		printf("Right\n");
	}
	// REFACTOR: move forward
	else if (keysym == XK_w)
	{
		if(game->map[(int)(game->player->pos_x + game->player->dir_x * MOVE_SPEED)][(int)game->player->pos_y] == false)
			game->player->pos_x += game->player->dir_x * MOVE_SPEED;
		if(game->map[(int)game->player->pos_x][(int)(game->player->pos_y + game->player->dir_y * MOVE_SPEED)] == false)
			game->player->pos_y += game->player->dir_y * MOVE_SPEED;
		printf("w\n");
	}
	// REFACTOR: move left
	else if (keysym == XK_a)
	{
		// Move left (perpendicular to direction, using plane vector)
		if(game->map[(int)(game->player->pos_x - game->player->plane_x * MOVE_SPEED)][(int)game->player->pos_y] == false)
			game->player->pos_x -= game->player->plane_x * MOVE_SPEED;
		if(game->map[(int)game->player->pos_x][(int)(game->player->pos_y - game->player->plane_y * MOVE_SPEED)] == false)
			game->player->pos_y -= game->player->plane_y * MOVE_SPEED;
		printf("a\n");
	}
	// REFACTOR: move backward
	else if (keysym == XK_s)
	{
		if(game->map[(int)(game->player->pos_x - game->player->dir_x * MOVE_SPEED)][(int)game->player->pos_y] == false)
			game->player->pos_x -= game->player->dir_x * MOVE_SPEED;
		if(game->map[(int)(game->player->pos_x)][(int)(game->player->pos_y - game->player->dir_y * MOVE_SPEED)] == false)
			game->player->pos_y -= game->player->dir_y * MOVE_SPEED;
		printf("s\n");
	}
	// REFACTOR: move right
	else if (keysym == XK_d)
	{
		// Move right (perpendicular to direction, using plane vector)
		if(game->map[(int)(game->player->pos_x + game->player->plane_x * MOVE_SPEED)][(int)game->player->pos_y] == false)
			game->player->pos_x += game->player->plane_x * MOVE_SPEED;
		if(game->map[(int)game->player->pos_x][(int)(game->player->pos_y + game->player->plane_y * MOVE_SPEED)] == false)
			game->player->pos_y += game->player->plane_y * MOVE_SPEED;
		printf("d\n");
	}
	return (0);
}
