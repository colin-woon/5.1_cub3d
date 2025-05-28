/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_movement_hooks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:43:47 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/27 20:58:56 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	movement_keys(int keysym, t_game *game);
bool	is_valid_keys(int keysym);
void	recalculate_variables(t_game *game, t_map *map, t_player *player, int keysym);

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
	if (is_valid_keys(keysym))
		recalculate_variables(game, game->map, game->player, keysym);
	return (0);
}

bool	is_valid_keys(int keysym)
{
	if (
		keysym == XK_Left ||
		keysym == XK_Right ||
		keysym == XK_w ||
		keysym == XK_a ||
		keysym == XK_s ||
		keysym == XK_d
	)
		return (true);
	return (false);
}

void	recalculate_variables(t_game *game, t_map *map, t_player *player, int keysym)
{
	if (keysym == XK_Left)
	{
		double	old_dir_x;
		double	old_plane_x;

		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(ROTATION_SPEED) - player->dir_y * sin(ROTATION_SPEED);
		player->dir_y = old_dir_x * sin(ROTATION_SPEED) + player->dir_y * cos(ROTATION_SPEED);
		old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(ROTATION_SPEED) - player->plane_y * sin(ROTATION_SPEED);
		player->plane_y = old_plane_x * sin(ROTATION_SPEED) + player->plane_y * cos(ROTATION_SPEED);
		printf("Left\n");
	}
	// REFACTOR: look right
	else if (keysym == XK_Right)
	{
		double	old_dir_x;
		double	old_plane_x;

		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(-ROTATION_SPEED) - player->dir_y * sin(-ROTATION_SPEED);
		player->dir_y = old_dir_x * sin(-ROTATION_SPEED) + player->dir_y * cos(-ROTATION_SPEED);
		old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(-ROTATION_SPEED) - player->plane_y * sin(-ROTATION_SPEED);
		player->plane_y = old_plane_x * sin(-ROTATION_SPEED) + player->plane_y * cos(-ROTATION_SPEED);
		printf("Right\n");
	}
	// REFACTOR: move forward
	else if (keysym == XK_w)
	{
		if(map->grid[(int)(player->pos_x + player->dir_x * MOVE_SPEED)][(int)player->pos_y] == NO_WALL)
			player->pos_x += player->dir_x * MOVE_SPEED;
		if(map->grid[(int)player->pos_x][(int)(player->pos_y + player->dir_y * MOVE_SPEED)] == NO_WALL)
			player->pos_y += player->dir_y * MOVE_SPEED;
		printf("w\n");
	}
	// REFACTOR: move left
	else if (keysym == XK_a)
	{
		// Move left (perpendicular to direction, using plane vector)
		if(map->grid[(int)(player->pos_x - player->plane_x * MOVE_SPEED)][(int)player->pos_y] == NO_WALL)
			player->pos_x -= player->plane_x * MOVE_SPEED;
		if(map->grid[(int)player->pos_x][(int)(player->pos_y - player->plane_y * MOVE_SPEED)] == NO_WALL)
			player->pos_y -= player->plane_y * MOVE_SPEED;
		printf("a\n");
	}
	// REFACTOR: move backward
	else if (keysym == XK_s)
	{
		if(map->grid[(int)(player->pos_x - player->dir_x * MOVE_SPEED)][(int)player->pos_y] == NO_WALL)
			player->pos_x -= player->dir_x * MOVE_SPEED;
		if(map->grid[(int)(player->pos_x)][(int)(player->pos_y - player->dir_y * MOVE_SPEED)] == NO_WALL)
			player->pos_y -= player->dir_y * MOVE_SPEED;
		printf("s\n");
	}
	// REFACTOR: move right
	else if (keysym == XK_d)
	{
		// Move right (perpendicular to direction, using plane vector)
		if(map->grid[(int)(player->pos_x + player->plane_x * MOVE_SPEED)][(int)player->pos_y] == NO_WALL)
			player->pos_x += player->plane_x * MOVE_SPEED;
		if(map->grid[(int)player->pos_x][(int)(player->pos_y + player->plane_y * MOVE_SPEED)] == NO_WALL)
			player->pos_y += player->plane_y * MOVE_SPEED;
		printf("d\n");
	}
	game->is_render = true;
}
