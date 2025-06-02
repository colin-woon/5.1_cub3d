/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:53:35 by cwoon             #+#    #+#             */
/*   Updated: 2025/06/02 14:52:22 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		mouse_hook(int x, int y, t_game *game);
void	rotate_player(t_player *player, double angle);

// // printf("x: %d y: %d\n", x, y);
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

// Define WINDOW_WIDTH or get it from your game structure
// Avoid running if x or y are out of reasonable bounds (optional)
// Or if the mouse is already centered (prevents infinite loops/jitter)
// Calculate the horizontal difference from the center
// Calculate the rotation angle based on the difference and sensitivity
// Apply the rotation
// Mark for re-render
// Reset the mouse position to the center of the window
// You need to know your window width and height
int mouse_hook(int x, int y, t_game *game)
{
	int		screen_center_x;
	double	delta_x;
	double	rotation_angle;

	(void)y; // To silence unused parameter warning
	screen_center_x = SCREEN_WIDTH / 2;
	if (x == screen_center_x)
		return (0);
	delta_x = (double)(x - screen_center_x);
	rotation_angle = -delta_x * MOUSE_SENSITIVITY;
	rotate_player(game->player, rotation_angle);
	game->is_render = true;
	mlx_mouse_move(game->mlx_data->ptr, game->mlx_data->window,\
SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	return (0);
}

void	rotate_player(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	old_plane_x = player->plane_x;
	player->plane_x \
= player->plane_x * cos(angle) - player->plane_y * sin(angle);
	player->plane_y = old_plane_x * sin(angle) + player->plane_y * cos(angle);
}
