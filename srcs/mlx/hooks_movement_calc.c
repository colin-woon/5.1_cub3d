/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_movement_calc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 00:56:30 by cwoon             #+#    #+#             */
/*   Updated: 2025/06/17 15:44:17 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_left_or_right\
(int keysym, t_player *player, t_game *game, t_map *map);
void	move_forward_or_backward\
(int keysym, t_player *player, t_game *game, t_map *map);
void	look_left_or_right(int keysym, t_player *player, t_game *game);
void	look_left(t_player *player, t_game *game);
void	look_right(t_player *player, t_game *game);

void	look_left_or_right(int keysym, t_player *player, t_game *game)
{
	if (keysym == XK_Left)
		look_left(player, game);
	else if (keysym == XK_Right)
		look_right(player, game);
}

void	look_left(t_player *player, t_game *game)
{
	double	old_dir_y;
	double	old_plane_y;

	old_dir_y = player->dir_y;
	player->dir_y = \
player->dir_y * cos(ROTATION_SPEED) - player->dir_x * sin(ROTATION_SPEED);
	player->dir_x \
= old_dir_y * sin(ROTATION_SPEED) + player->dir_x * cos(ROTATION_SPEED);
	old_plane_y = player->plane_y;
	player->plane_y \
= player->plane_y * cos(ROTATION_SPEED) \
- player->plane_x * sin(ROTATION_SPEED);
	player->plane_x \
= old_plane_y * sin(ROTATION_SPEED) \
+ player->plane_x * cos(ROTATION_SPEED);
	game->is_render = true;
}

void	look_right(t_player *player, t_game *game)
{
	double	old_dir_y;
	double	old_plane_y;

	old_dir_y = player->dir_y;
	player->dir_y \
= player->dir_y * cos(-ROTATION_SPEED) \
- player->dir_x * sin(-ROTATION_SPEED);
	player->dir_x \
= old_dir_y * sin(-ROTATION_SPEED) + player->dir_x * cos(-ROTATION_SPEED);
	old_plane_y = player->plane_y;
	player->plane_y \
= player->plane_y * cos(-ROTATION_SPEED) \
- player->plane_x * sin(-ROTATION_SPEED);
	player->plane_x \
= old_plane_y * sin(-ROTATION_SPEED) \
+ player->plane_x * cos(-ROTATION_SPEED);
	game->is_render = true;
}

void	move_forward_or_backward\
(int keysym, t_player *player, t_game *game, t_map *map)
{
	double	new_pos_x;
	double	new_pos_y;
	int		buffer_x;
	int		buffer_y;

	if (keysym == XK_w)
	{
		new_pos_x = player->pos_x + player->dir_x * MOVE_SPEED;
		new_pos_y = player->pos_y + player->dir_y * MOVE_SPEED;
		// Add a buffer in the direction of movement
		buffer_x = (int)(player->pos_x + player->dir_x * COLLISION_BUFFER);
		buffer_y = (int)(player->pos_y + player->dir_y * COLLISION_BUFFER);

		// Check the future position plus the buffer
		if (map->grid[(int)player->pos_y][buffer_x] == NO_WALL)
			player->pos_x = new_pos_x;
		if (map->grid[buffer_y][(int)player->pos_x] == NO_WALL)
			player->pos_y = new_pos_y;
		game->is_render = true;
	}
	else if (keysym == XK_s)
	{
		new_pos_x = player->pos_x - player->dir_x * MOVE_SPEED;
		new_pos_y = player->pos_y - player->dir_y * MOVE_SPEED;
		// Add a buffer in the direction of movement
		buffer_x = (int)(player->pos_x - player->dir_x * COLLISION_BUFFER);
		buffer_y = (int)(player->pos_y - player->dir_y * COLLISION_BUFFER);

		// Check the future position plus the buffer
		if (map->grid[(int)player->pos_y][buffer_x] == NO_WALL)
			player->pos_x = new_pos_x;
		if (map->grid[buffer_y][(int)player->pos_x] == NO_WALL)
			player->pos_y = new_pos_y;
		game->is_render = true;
	}
}

void	move_left_or_right\
(int keysym, t_player *player, t_game *game, t_map *map)
{
	double	new_pos_x;
	double	new_pos_y;
	int		buffer_x;
	int		buffer_y;

	if (keysym == XK_d) // Strafe Right
	{
		new_pos_x = player->pos_x + player->plane_x * MOVE_SPEED;
		new_pos_y = player->pos_y + player->plane_y * MOVE_SPEED;
		buffer_x = (int)(player->pos_x + player->plane_x * COLLISION_BUFFER);
		buffer_y = (int)(player->pos_y + player->plane_y * COLLISION_BUFFER);

		if (map->grid[(int)player->pos_y][buffer_x] == NO_WALL)
			player->pos_x = new_pos_x;
		if (map->grid[buffer_y][(int)player->pos_x] == NO_WALL)
			player->pos_y = new_pos_y;
		game->is_render = true;
	}
	else if (keysym == XK_a) // Strafe Left
	{
		new_pos_x = player->pos_x - player->plane_x * MOVE_SPEED;
		new_pos_y = player->pos_y - player->plane_y * MOVE_SPEED;
		buffer_x = (int)(player->pos_x - player->plane_x * COLLISION_BUFFER);
		buffer_y = (int)(player->pos_y - player->plane_y * COLLISION_BUFFER);

		if (map->grid[(int)player->pos_y][buffer_x] == NO_WALL)
			player->pos_x = new_pos_x;
		if (map->grid[buffer_y][(int)player->pos_x] == NO_WALL)
			player->pos_y = new_pos_y;
		game->is_render = true;
	}
}
