/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:29:32 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/30 17:39:36 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	run_raycasting(t_ray *ray, t_player *player, t_mlx *mlx, t_game *game);
void	calculate_line_height(t_ray *ray);
void	init_ray_dir_n_map_pos(t_game *game, int x, int *map_x, int *map_y);
void	draw_wall_texture(t_img *texture, double wall_x, t_game *game, int *x);

void draw_minimap_rect(t_img *img, t_minimap_vars *var, int color);
void draw_minimap(t_mlx *mlx, t_game *game, t_player *player);

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
	draw_minimap(mlx, game, player);
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->img->ptr, 0, 0);
}

void	draw_player_line(t_player *player, t_mlx *mlx, int player_minimap_x, int player_minimap_y);
void	draw_player_box(t_player *player, t_mlx *mlx);
void	draw_map_tiles(t_map *map, t_mlx *mlx);

void draw_minimap(t_mlx *mlx, t_game *game, t_player *player)
{
	draw_map_tiles(game->map, mlx);
	draw_player_box(player, mlx);
}

void	get_map_tiles_var(t_minimap_vars *var, t_map *map ,int map_x_grid, int map_y_grid);

// Determine tile color based on map data
// Assuming anything not a WALL is a floor/empty space
// Draw the scaled tile as a rectangle
// Ensure this doesn't draw outside the screen or minimap boundaries if desired
// For now, it will draw if the top-left of the tile is on screen
void	draw_map_tiles(t_map *map, t_mlx *mlx)
{
	int				map_x_grid;
	int				map_y_grid;
	t_minimap_vars	var;

	map_x_grid = 0;
	while (map_x_grid < map->width)
	{
		map_y_grid = 0;
		while (map_y_grid < map->height)
		{
			get_map_tiles_var(&var, map, map_x_grid, map_y_grid);
			draw_minimap_rect(mlx->img, &var, var.color);
			map_y_grid++;
		}
		map_x_grid++;
	}
}

void	get_map_tiles_var(t_minimap_vars *var, t_map *map ,int map_x_grid, int map_y_grid)
{
	var->rect_x = MINIMAP_OFFSET_X + map_x_grid * MINIMAP_SCALE;
	var->rect_y = MINIMAP_OFFSET_Y + map_y_grid * MINIMAP_SCALE;
	if (map->grid[map_y_grid][map_x_grid] == WALL)
		var->color = MINIMAP_WALL_COLOR;
	else
		var->color = MINIMAP_FLOOR_COLOR;
	var->height = MINIMAP_SCALE;
	var->width = MINIMAP_SCALE;
}
void	get_player_box_vars(t_minimap_vars *var, int player_x, int player_y);

void	draw_player_box(t_player *player, t_mlx *mlx)
{
	int player_minimap_x;
	int player_minimap_y;
	t_minimap_vars var;

	player_minimap_y = MINIMAP_OFFSET_Y + (int)(player->pos_x * MINIMAP_SCALE);
	player_minimap_x = MINIMAP_OFFSET_X + (int)(player->pos_y * MINIMAP_SCALE);
	get_player_box_vars(&var, player_minimap_x, player_minimap_y);
	draw_minimap_rect(mlx->img, &var, var.color);
	draw_player_line(player, mlx, player_minimap_x, player_minimap_y);
}

void	get_player_box_vars(t_minimap_vars *var, int player_x, int player_y)
{
	var->rect_x = player_x - MINIMAP_PLAYER_SIZE / 2;
	var->rect_y = player_y - MINIMAP_PLAYER_SIZE / 2;
	var->width = MINIMAP_PLAYER_SIZE;
	var->height = MINIMAP_PLAYER_SIZE;
	var->color = MINIMAP_PLAYER_COLOR;
}

// Simple line drawing (draw a few pixels along the vector)
// For a more precise line, you'd use an algorithm like Bresenham's.
// This is a simplified version for a short line.
void	draw_player_line(t_player *player, t_mlx *mlx, int player_minimap_x, int player_minimap_y)
{
	double dx;
	double dy;
	int i;
	int px;
	int py;

	dx = player->dir_y;
	dy = player->dir_x;
	i = 0;
	while (i < MINIMAP_RAY_LENGTH)
	{
		px = player_minimap_x + (int)(dx * i);
		py = player_minimap_y + (int)(dy * i);
		my_mlx_pixel_put(mlx->img, px, py, MINIMAP_VIEW_CONE_COLOR);
		i++;
	}
}

void draw_minimap_rect(t_img *img, t_minimap_vars *var, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < var->height)
	{
		j = 0;
		while (j < var->width)
		{
			my_mlx_pixel_put(img, var->rect_x + j, var->rect_y + i, color);
			j++;
		}
		i++;
	}
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
