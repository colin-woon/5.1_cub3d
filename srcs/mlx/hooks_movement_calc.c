/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_movement_calc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 00:56:30 by cwoon             #+#    #+#             */
/*   Updated: 2025/06/17 16:30:37 by cwoon            ###   ########.fr       */
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
	t_movement_vars	var;

	var.move_x = 0;
	var.move_y = 0;
	if (keysym == XK_w)
	{
		var.move_x = player->dir_x * MOVE_SPEED;
		var.move_y = player->dir_y * MOVE_SPEED;
	}
	else if (keysym == XK_s)
	{
		var.move_x = -player->dir_x * MOVE_SPEED;
		var.move_y = -player->dir_y * MOVE_SPEED;
	}
	var.potential_x = player->pos_x + var.move_x;
	var.potential_y = player->pos_y + var.move_y;
	validate_movement(player, map, &var);
	game->is_render = true;
}

void	move_left_or_right\
(int keysym, t_player *player, t_game *game, t_map *map)
{
	t_movement_vars	vars;

	vars.move_x = 0;
	vars.move_y = 0;
	if (keysym == XK_d)
	{
		vars.move_x = player->plane_x * MOVE_SPEED;
		vars.move_y = player->plane_y * MOVE_SPEED;
	}
	else if (keysym == XK_a)
	{
		vars.move_x = -player->plane_x * MOVE_SPEED;
		vars.move_y = -player->plane_y * MOVE_SPEED;
	}
	vars.potential_x = player->pos_x + vars.move_x;
	vars.potential_y = player->pos_y + vars.move_y;
	validate_movement(player, map, &vars);
	game->is_render = true;
}
