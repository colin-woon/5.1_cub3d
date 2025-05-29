/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:29:32 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/29 14:48:07 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	run_raycasting(t_ray *ray, t_player *player, t_mlx *mlx, t_game *game);
void	calculate_line_height(t_ray *ray);
void	init_ray_dir_n_map_pos(t_game *game, int x, int *map_x, int *map_y);
void	draw_wall_texture(t_img *texture, double wall_x, t_game *game, int *x);

void	run_raycasting(t_ray *ray, t_player *player, t_mlx *mlx, t_game *game)
{
	int	x;
	int	map_x;
	int	map_y;

	draw_floor_ceiling(mlx, get_floor_colour(game), get_ceiling_colour(game));
	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray_dir_n_map_pos(game, x, &map_x, &map_y);
		calculate_point_gap(ray);
		calculate_step_n_init_side_dist(ray, player, map_x, map_y);
		run_dda(ray, game, &map_x, &map_y);
		calculate_line_height(ray);
		draw_wall_texture(&game->assets->textures[get_wall_direction(ray)], \
get_fractional_texture_position_x(ray, player), game, &x);
		x++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->img->ptr, 0, 0);
}

// calculate line height, prependicular distance needed to avoid fisheye effect
// https://chat.qwen.ai/s/4eaf1fda-5ae9-4f03-b0c1-c08374235e65?fev=0.0.95
// derived from this formula, its mathematical proof,
// although not obviously related, using substitution
void	calculate_line_height(t_ray *ray)
{
	if (ray->wall_hit_side == VERTICAL)
		ray->prependicular_wall_distance \
= (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->prependicular_wall_distance \
= (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height \
= (int)(WALL_HEIGHT_SCALE * SCREEN_HEIGHT / ray->prependicular_wall_distance);
	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
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

	prep_texture_vars(&tex, wall_x, texture, game->ray);
	put_texture_pixels(&tex, texture, game, x);
}
