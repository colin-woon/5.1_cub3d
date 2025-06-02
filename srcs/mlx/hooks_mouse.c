/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 17:53:35 by cwoon             #+#    #+#             */
/*   Updated: 2025/06/02 15:02:08 by cwoon            ###   ########.fr       */
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

int mouse_hook(int x, int y, t_game *game) {
    int screen_center_x;
    int screen_center_y;
    double delta_x;
    double delta_y;
    double rotation_angle_yaw;
    bool mouse_moved = false;

    screen_center_x = SCREEN_WIDTH / 2;
    screen_center_y = SCREEN_HEIGHT / 2;

    // --- Horizontal Rotation (Yaw) ---
    delta_x = (double)(x - screen_center_x);
    if (x != screen_center_x) { // Check if x actually changed to avoid tiny rotations if only y moved
        rotation_angle_yaw = -delta_x * MOUSE_SENSITIVITY_X; // Negative for natural mouse look
        rotate_player(game->player, rotation_angle_yaw); // This is your existing yaw rotation
        mouse_moved = true;
    }

    // --- Vertical Look (Pitch) ---
    delta_y = (double)(y - screen_center_y);
    if (y != screen_center_y) { // Check if y actually changed
        // Moving mouse down (y > screen_center_y, delta_y > 0) should make player look down (decrease pitch offset).
        // Moving mouse up (y < screen_center_y, delta_y < 0) should make player look up (increase pitch offset).
        // The sign of MOUSE_SENSITIVITY_Y can invert this if needed.
        // Let's make positive pitch mean looking up.
        game->player->pitch -= delta_y * MOUSE_SENSITIVITY_Y;
        mouse_moved = true;

        // Clamp pitch to prevent looking too far (and potential visual glitches)
        if (game->player->pitch > MAX_PITCH_PIXELS) {
            game->player->pitch = MAX_PITCH_PIXELS;
        } else if (game->player->pitch < -MAX_PITCH_PIXELS) {
            game->player->pitch = -MAX_PITCH_PIXELS;
        }
    }

    if (mouse_moved) {
        game->is_render = true; // Signal that a re-render is needed
        // Reset mouse to the center of the window
        mlx_mouse_move(game->mlx_data->ptr, game->mlx_data->window, screen_center_x, screen_center_y);
    }

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
