/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:53:35 by cwoon             #+#    #+#             */
/*   Updated: 2025/06/02 22:14:35 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		mouse_hook(int x, int y, t_game *game);
void	rotate_player(t_player *player, double angle);
void	rotate_horizontally\
(t_game *game, int *x, t_mouse_vars *var, bool *mouse_moved);
void	rotate_vertically\
(t_game *game, int *y, t_mouse_vars *var, bool *mouse_moved);
void	init_mouse_vars(t_mouse_vars *var, int *x, int *y);

// // printf("x: %d y: %d\n", x, y);
// FOR WINDOWS (need to use relative position
// as there is no way to reset mouse pointer to center)
// int	mouse_hook(int x, int y, t_game *game)
// {
// 	double	delta_x;
// 	double	rotation_angle;

// 	(void)y;
// 	if (!game->mouse_initialized)
// 	{
// 		game->last_mouse_x = x;
// 		game->mouse_initialized = 1;
// 		return (0);
// 	}
// 	delta_x = (double)(x - game->last_mouse_x);
// 	rotation_angle = -delta_x * MOUSE_SENSITIVITY;
// 	if (fabs(delta_x) > 1.0)
// 	{
// 		rotation_angle = -delta_x * MOUSE_SENSITIVITY;
// 		rotate_player(game->player, rotation_angle);
// 		game->is_render = true;
// 	}
// 	game->last_mouse_x = x;
// 	return (0);
// }

int	mouse_hook(int x, int y, t_game *game)
{
	t_mouse_vars	var;
	bool			mouse_moved;

	// printf("x: %d y: %d\n", x, y);
	mouse_moved = false;
	init_mouse_vars(&var, &x, &y);
	rotate_horizontally(game, &x, &var, &mouse_moved);
	rotate_vertically(game, &y, &var, &mouse_moved);
	if (mouse_moved)
	{
		game->is_render = true;
		mlx_mouse_move(game->mlx_data->ptr, game->mlx_data->window, \
var.screen_center_x, var.screen_center_y);
	}
	return (0);
}

// --- Horizontal Rotation (Yaw) ---
// Check if x actually changed to avoid tiny rotations if only y moved
// Negative for natural mouse look
// This is your existing yaw rotation
void	rotate_horizontally\
(t_game *game, int *x, t_mouse_vars *var, bool *mouse_moved)
{
	if (*x != (*var).screen_center_x)
	{
		(*var).rotation_angle_yaw = -(*var).delta_x * MOUSE_SENSITIVITY_X;
		rotate_player(game->player, (*var).rotation_angle_yaw);
		*mouse_moved = true;
	}
}

// --- Vertical Look (Pitch) ---
// Check if y actually changed
// Moving mouse down (y > screen_center_y, delta_y > 0)
// should make player look down (decrease pitch offset).
// Moving mouse up (y < screen_center_y, delta_y < 0)
// should make player look up (increase pitch offset).
// The sign of MOUSE_SENSITIVITY_Y can invert this if needed.
// Let's make positive pitch mean looking up.
// Clamp pitch to prevent looking too far (and potential visual glitches)
void	rotate_vertically\
(t_game *game, int *y, t_mouse_vars *var, bool *mouse_moved)
{
	if (*y != (*var).screen_center_y)
	{
		game->player->pitch -= (*var).delta_y * MOUSE_SENSITIVITY_Y;
		*mouse_moved = true;
		if (game->player->pitch > MAX_PITCH_PIXELS)
			game->player->pitch = MAX_PITCH_PIXELS;
		else if (game->player->pitch < -MAX_PITCH_PIXELS)
			game->player->pitch = -MAX_PITCH_PIXELS;
	}
}

void	init_mouse_vars(t_mouse_vars *var, int *x, int *y)
{
	(*var).screen_center_x = SCREEN_WIDTH / 2;
	(*var).screen_center_y = SCREEN_HEIGHT / 2;
	(*var).delta_x = (double)(*x - (*var).screen_center_x);
	(*var).delta_y = (double)(*y - (*var).screen_center_y);
	(*var).rotation_angle_yaw = 0.0;
}

void	rotate_player(t_player *player, double angle)
{
	double	old_dir_y;
	double	old_plane_y;

	old_dir_y = player->dir_y;
	player->dir_y = player->dir_y * cos(angle) - player->dir_x * sin(angle);
	player->dir_x = old_dir_y * sin(angle) + player->dir_x * cos(angle);
	old_plane_y = player->plane_y;
	player->plane_y \
= player->plane_y * cos(angle) - player->plane_x * sin(angle);
	player->plane_x = old_plane_y * sin(angle) + player->plane_x * cos(angle);
}
