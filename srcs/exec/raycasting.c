/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:29:32 by cwoon             #+#    #+#             */
/*   Updated: 2025/06/02 15:58:16 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	run_raycasting(t_ray *ray, t_player *player, t_mlx *mlx, t_game *game);
void	calculate_line_height(t_ray *ray);
void	init_ray_dir_n_map_pos(t_game *game, int x, int *map_x, int *map_y);
void	draw_wall_texture(t_img *texture, double wall_x, t_game *game, int *x);
void	draw_minimap(t_mlx *mlx, t_game *game, t_player *player);

void calculate_wall_projection(t_ray *ray, t_player *player);

void    run_raycasting(t_ray *ray, t_player *player, t_mlx *mlx, t_game *game)
{
    int x_col; // Current screen column being rendered
    int y_row; // Current screen row being drawn to
    int map_x_dda; // Map X coordinate for DDA
    int map_y_dda; // Map Y coordinate for DDA

    // Get floor and ceiling colors once to avoid repeated calls in the loop
    int ceiling_colour = get_ceiling_colour(game);
    int floor_colour = get_floor_colour(game);

    // The old call to draw_floor_ceiling() is removed from here.
    // We will draw floor and ceiling on a per-column basis now.

    x_col = 0;
    while (x_col < SCREEN_WIDTH)
    {
        // Initialize ray for the current screen column
        // Assuming init_ray_dir_n_map_pos might use game->player for player's direction/plane
        // and game->ray for setting initial ray->dir_x, ray->dir_y etc.
        init_ray_dir_n_map_pos(game, x_col, &map_x_dda, &map_y_dda);

        // Calculate distances and steps for DDA
        calculate_point_gap(ray); // Modifies ray based on its dir_x, dir_y
        calculate_step_n_init_side_dist(ray, player, map_x_dda, map_y_dda); // Modifies ray based on player pos and map_x/y_dda

        // Perform DDA to find wall hit
        run_dda(ray, game, &map_x_dda, &map_y_dda); // Modifies ray (perp_wall_dist, side, etc.)

        // Calculate wall projection height and screen draw limits (incorporates pitch)
        // This function sets ray->draw_start and ray->draw_end
        calculate_wall_projection(ray, player);

        // 1. Draw Ceiling for the current column x_col
        // Pixels from y_row = 0 up to (but not including) ray->draw_start
        y_row = 0;
        while (y_row < ray->draw_start)
        {
            // Ensure you're using the correct image buffer, likely from game->mlx_data->img
            // if my_mlx_pixel_put is a standalone function.
            // If mlx contains the t_img directly, then mlx->img is fine.
            // Based on your put_texture_pixels, it seems to be game->mlx_data->img
            my_mlx_pixel_put(game->mlx_data->img, x_col, y_row, ceiling_colour);
            y_row++;
        }

        // 2. Draw Wall Texture for the current column x_col
        // This function should draw pixels from y_row = ray->draw_start to ray->draw_end
        // It uses game->ray internally to get draw_start and draw_end.
        draw_wall_texture(&game->assets->textures[get_wall_dir(ray)],
                          get_fractional_texture_position_x(ray, player),
                          game,  // game struct is passed, which contains game->ray
                          &x_col); // The current screen column

        // 3. Draw Floor for the current column x_col
        // Pixels from y_row = ray->draw_end + 1 down to SCREEN_HEIGHT - 1
        y_row = ray->draw_end + 1;
        // Ensure y_row starts validly; if ray->draw_end was SCREEN_HEIGHT - 1,
        // y_row would be SCREEN_HEIGHT, and the loop condition y_row < SCREEN_HEIGHT would be false.
        // This is correct, as no floor would be drawn in that case.
        while (y_row < SCREEN_HEIGHT)
        {
            my_mlx_pixel_put(game->mlx_data->img, x_col, y_row, floor_colour);
            y_row++;
        }

        x_col++; // Move to the next screen column
    }

    // After the 3D scene (ceiling, walls, floor) is drawn to the image buffer:
    // Draw the 2D minimap on top
    draw_minimap(mlx, game, player); // Assuming mlx is the correct t_mlx for minimap drawing context

    // Finally, put the completed image (3D scene + minimap) to the window
    mlx_put_image_to_window(mlx->ptr, mlx->window, game->mlx_data->img->ptr, 0, 0);
    // Note: If mlx->img is the same as game->mlx_data->img, then use mlx->img->ptr.
    // I've used game->mlx_data->img->ptr assuming that's where the scene is rendered.
}

// calculate line height, prependicular distance needed to avoid fisheye effect
// https://chat.qwen.ai/s/4eaf1fda-5ae9-4f03-b0c1-c08374235e65?fev=0.0.95
// derived from this formula, its mathematical proof,
// although not obviously related, using substitution
// void	calculate_line_height(t_ray *ray)
// {
// 	if (ray->wall_hit_side == VERTICAL)
// 		ray->prependicular_wall_distance \
// = (ray->side_dist_x - ray->delta_dist_x);
// 	else
// 		ray->prependicular_wall_distance \
// = (ray->side_dist_y - ray->delta_dist_y);
// 	ray->line_height \
// = (int)(WALL_HEIGHT_SCALE * SCREEN_HEIGHT / ray->prependicular_wall_distance);
// 	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
// 	if (ray->draw_start < 0)
// 		ray->draw_start = 0;
// 	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
// 	if (ray->draw_end >= SCREEN_HEIGHT)
// 		ray->draw_end = SCREEN_HEIGHT - 1;
// }

void calculate_wall_projection(t_ray *ray, t_player *player)
{
    // --- 1. Calculate Perpendicular Wall Distance ---
    // This logic is taken directly from your commented-out `calculate_line_height`.
    // It assumes that your DDA loop (run_dda) correctly calculates and stores:
    // - ray->wall_hit_side (VERTICAL or HORIZONTAL)
    // - ray->side_dist_x, ray->side_dist_y
    // - ray->delta_dist_x, ray->delta_dist_y
    // In many DDA implementations (like Lode Vandevenne's tutorial),
    // (side_dist - delta_dist) correctly gives the perpendicular wall distance.
    if (ray->wall_hit_side == VERTICAL) // Assuming VERTICAL means hit a N/S wall
    {
        ray->prependicular_wall_distance = (ray->side_dist_x - ray->delta_dist_x);
    }
    else // Assuming HORIZONTAL means hit an E/W wall
    {
        ray->prependicular_wall_distance = (ray->side_dist_y - ray->delta_dist_y);
    }

    // --- 2. Calculate Projected Line Height ---
    // Prevent division by zero or very small distances, which cause excessively large line_height.
    if (ray->prependicular_wall_distance < 0.01) // Using a small epsilon
    {
        ray->prependicular_wall_distance = 0.01;
    }

    // Calculate the height of the wall slice on screen.
    // This uses your WALL_HEIGHT_SCALE.
    ray->line_height = (int)(WALL_HEIGHT_SCALE * SCREEN_HEIGHT / ray->prependicular_wall_distance);

    // --- 3. Calculate Draw Start and End Points with Pitch ---
    int pitch_offset;

    // Get the vertical look offset from the player's state.
    // (player->pitch is assumed to be in screen pixels offset from the center)
    pitch_offset = (int)player->pitch;

    // Calculate the top screen pixel of the wall slice.
    // The wall is centered around (SCREEN_HEIGHT / 2 + pitch_offset).
    ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2 + pitch_offset;
    if (ray->draw_start < 0)
    {
        ray->draw_start = 0; // Clamp to the top of the screen.
    }

    // Calculate the bottom screen pixel of the wall slice.
    ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2 + pitch_offset;
    if (ray->draw_end >= SCREEN_HEIGHT)
    {
        ray->draw_end = SCREEN_HEIGHT - 1; // Clamp to the bottom of the screen.
    }

    // Safeguard: Ensure draw_start is not greater than draw_end.
    // This can happen if line_height is calculated as <= 0.
    if (ray->draw_start > ray->draw_end)
    {
        // If the wall is effectively behind the player or too far,
        // or line_height is zero, just draw a single pixel line at horizon or collapse.
        // For simplicity, let's set them to the same point (effectively no wall drawn).
        // You might want to handle this differently, e.g. by not drawing.
        int center_y = SCREEN_HEIGHT / 2 + pitch_offset;
        if (center_y < 0) center_y = 0;
        if (center_y >= SCREEN_HEIGHT) center_y = SCREEN_HEIGHT -1;
        ray->draw_start = center_y;
        ray->draw_end = center_y;
    }
}

// Needed because when moving or rotating,
// the player position changes, and it usually is a floating point
// EXPLANATION:	max value after 2 * x/SCREEN_WIDTH is 2, and min value is 0,
// using those values, subtract 1, can effectively represent:
//		-1 (left side of screen)
//		0 (center of screen)
//		1 (right side of screen)
// camera_x represents a like a percentage of
// where it is on the plane (-1 < 0 < 1) (Left Centre Right)
void	init_ray_dir_n_map_pos(t_game *game, int x, int *map_x, int *map_y)
{
	game->ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
	game->ray->dir_x \
= game->player->dir_x + game->player->plane_x * game->ray->camera_x;
	game->ray->dir_y \
= game->player->dir_y + game->player->plane_y * game->ray->camera_x;
	*map_x = (int)game->player->pos_x;
	*map_y = (int)game->player->pos_y;
}

void	draw_wall_texture(t_img *texture, double wall_x, t_game *game, int *x)
{
	t_texture_vars	tex;

	prep_texture_vars(&tex, wall_x, texture, game->ray, game->player);
	put_texture_pixels(&tex, texture, game, x);
}

void	draw_minimap(t_mlx *mlx, t_game *game, t_player *player)
{
	draw_map_tiles(game->map, mlx);
	draw_player_box(player, mlx);
}
