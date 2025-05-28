/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_movement_calc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 00:56:30 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/29 01:07:35 by cwoon            ###   ########.fr       */
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
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = \
player->dir_x * cos(ROTATION_SPEED) - player->dir_y * sin(ROTATION_SPEED);
	player->dir_y \
= old_dir_x * sin(ROTATION_SPEED) + player->dir_y * cos(ROTATION_SPEED);
	old_plane_x = player->plane_x;
	player->plane_x \
= player->plane_x * cos(ROTATION_SPEED) \
- player->plane_y * sin(ROTATION_SPEED);
	player->plane_y \
= old_plane_x * sin(ROTATION_SPEED) \
+ player->plane_y * cos(ROTATION_SPEED);
	game->is_render = true;
}

void	look_right(t_player *player, t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x \
= player->dir_x * cos(-ROTATION_SPEED) \
- player->dir_y * sin(-ROTATION_SPEED);
	player->dir_y \
= old_dir_x * sin(-ROTATION_SPEED) + player->dir_y * cos(-ROTATION_SPEED);
	old_plane_x = player->plane_x;
	player->plane_x \
= player->plane_x * cos(-ROTATION_SPEED) \
- player->plane_y * sin(-ROTATION_SPEED);
	player->plane_y \
= old_plane_x * sin(-ROTATION_SPEED) \
+ player->plane_y * cos(-ROTATION_SPEED);
	game->is_render = true;
}

void	move_forward_or_backward\
(int keysym, t_player *player, t_game *game, t_map *map)
{
	if (keysym == XK_w)
	{
		if (map->grid[(int)(player->pos_x + player->dir_x * MOVE_SPEED)]\
[(int)player->pos_y] == NO_WALL)
			player->pos_x += player->dir_x * MOVE_SPEED;
		if (map->grid[(int)player->pos_x]\
[(int)(player->pos_y + player->dir_y * MOVE_SPEED)] == NO_WALL)
			player->pos_y += player->dir_y * MOVE_SPEED;
		game->is_render = true;
	}
	else if (keysym == XK_s)
	{
		if (map->grid[(int)(player->pos_x - player->dir_x * MOVE_SPEED)]\
[(int)player->pos_y] == NO_WALL)
			player->pos_x -= player->dir_x * MOVE_SPEED;
		if (map->grid[(int)(player->pos_x)]\
[(int)(player->pos_y - player->dir_y * MOVE_SPEED)] == NO_WALL)
			player->pos_y -= player->dir_y * MOVE_SPEED;
		game->is_render = true;
	}
}

void	move_left_or_right\
(int keysym, t_player *player, t_game *game, t_map *map)
{
	if (keysym == XK_a)
	{
		if (map->grid[(int)(player->pos_x - player->plane_x * MOVE_SPEED)]\
[(int)player->pos_y] == NO_WALL)
			player->pos_x -= player->plane_x * MOVE_SPEED;
		if (map->grid[(int)player->pos_x]\
[(int)(player->pos_y - player->plane_y * MOVE_SPEED)] == NO_WALL)
			player->pos_y -= player->plane_y * MOVE_SPEED;
		game->is_render = true;
	}
	else if (keysym == XK_d)
	{
		if (map->grid[(int)(player->pos_x + player->plane_x * MOVE_SPEED)]\
[(int)player->pos_y] == NO_WALL)
			player->pos_x += player->plane_x * MOVE_SPEED;
		if (map->grid[(int)player->pos_x]\
[(int)(player->pos_y + player->plane_y * MOVE_SPEED)] == NO_WALL)
			player->pos_y += player->plane_y * MOVE_SPEED;
		game->is_render = true;
	}
}
