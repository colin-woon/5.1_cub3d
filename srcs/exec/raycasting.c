/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:29:32 by cwoon             #+#    #+#             */
/*   Updated: 2025/06/02 17:24:28 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	run_raycasting(t_ray *ray, t_player *player, t_mlx *mlx, t_game *game);
void	init_ray_dir_n_map_pos(t_game *game, int x, int *map_x, int *map_y);
void	draw_wall_texture(t_img *texture, double wall_x, t_game *game, int *x);
void	calculate_wall_projection(t_ray *ray, t_player *player);
void	calculate_pitch_offset(t_player *player, t_ray *ray);

void	run_raycasting(t_ray *ray, t_player *player, t_mlx *mlx, t_game *game)
{
	int	x_col;
	int	y_row;
	int	map_x_dda;
	int	map_y_dda;

	x_col = 0;
	while (x_col < SCREEN_WIDTH)
	{
		init_ray_dir_n_map_pos(game, x_col, &map_x_dda, &map_y_dda);
		calculate_point_gap(ray);
		calculate_step_n_init_side_dist(ray, player, map_x_dda, map_y_dda);
		run_dda(ray, game, &map_x_dda, &map_y_dda);
		calculate_wall_projection(ray, player);
		draw_ceiling(&y_row, ray, game, &x_col);
		draw_wall_texture(&game->assets->textures[get_wall_dir(ray)], \
get_fractional_texture_position_x(ray, player), game, &x_col);
		draw_floor(&y_row, ray, game, &x_col);
		x_col++;
	}
	draw_minimap(mlx, game, player);
	mlx_put_image_to_window\
(mlx->ptr, mlx->window, game->mlx_data->img->ptr, 0, 0);
}

// Calculate wall projection height and screen draw limits (incorporates pitch)
// perpendicular distance needed to avoid fisheye effect
// https://chat.qwen.ai/s/4eaf1fda-5ae9-4f03-b0c1-c08374235e65?fev=0.0.95
// derived from this formula, its mathematical proof,
// although not obviously related, using substitution
// This function sets ray->draw_start and ray->draw_end
// --- 2. Calculate Projected Line Height ---
// Prevent division by zero or very small distances,
// which cause excessively large line_height.
void	calculate_wall_projection(t_ray *ray, t_player *player)
{
	if (ray->wall_hit_side == VERTICAL)
		ray->perpendicular_wall_distance \
= (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perpendicular_wall_distance \
= (ray->side_dist_y - ray->delta_dist_y);
	if (ray->perpendicular_wall_distance < 0.01)
		ray->perpendicular_wall_distance = 0.01;
	ray->line_height = \
(int)(WALL_HEIGHT_SCALE * SCREEN_HEIGHT / ray->perpendicular_wall_distance);
	calculate_pitch_offset(player, ray);
}

// --- 3. Calculate Draw Start and End Points with Pitch ---
// Get the vertical look offset from the player's state.
// (player->pitch is assumed to be in screen pixels offset from the center)
	// pitch_offset = (int)player->pitch;
// Calculate the top screen pixel of the wall slice.
// The wall is centered around (SCREEN_HEIGHT / 2 + pitch_offset).
	// ray->draw_start
	// = -ray->line_height / 2 + SCREEN_HEIGHT / 2 + pitch_offset;
// Safeguard: Ensure draw_start is not greater than draw_end.
// This can happen if line_height is calculated as <= 0.
	// if (ray->draw_start > ray->draw_end)
// If the wall is effectively behind the player or too far,
// or line_height is zero, just draw a single pixel line at horizon or collapse
// For simplicity, let's set them to the same point (effectively no wall drawn)
// You might want to handle this differently, e.g. by not drawing.
	// center_y = SCREEN_HEIGHT / 2 + pitch_offset;
void	calculate_pitch_offset(t_player *player, t_ray *ray)
{
	int	pitch_offset;
	int	center_y;

	pitch_offset = (int)player->pitch;
	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2 + pitch_offset;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2 + pitch_offset;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
	if (ray->draw_start > ray->draw_end)
	{
		center_y = SCREEN_HEIGHT / 2 + pitch_offset;
		if (center_y < 0)
			center_y = 0;
		if (center_y >= SCREEN_HEIGHT)
			center_y = SCREEN_HEIGHT -1;
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

	tex.x = (int)(wall_x * texture->width);
	prep_texture_vars(&tex, texture, game->ray, game->player);
	put_texture_pixels(&tex, texture, game, x);
}
