/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:29:32 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/29 00:44:55 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	run_raycasting(t_ray *ray, t_player *player, t_mlx *mlx, t_game *game);
int		get_texture_pixel(t_img *texture, int x, int y);
void	draw_wall_texture(t_img *texture, double wall_x, t_ray *ray, t_mlx *mlx, int *x);
double	get_fractional_texture_position_x(t_ray *ray, t_player *player);
void	calculate_line_height(t_ray *ray);
e_wall_direction	get_wall_direction(t_ray *ray);
void	run_DDA(t_ray *ray, t_game *game, int *map_x, int *map_y);
void	calculate_step_n_init_side_dist(t_ray *ray, t_player *player, int map_x, int map_y);
void	calculate_point_gap(t_ray *ray);
void	init_ray_dir_n_map_pos(t_game *game, int x, int *map_x, int *map_y);

void run_raycasting(t_ray *ray, t_player *player, t_mlx *mlx, t_game *game)
{
	int	x;
	int	map_x;
	int	map_y;

	draw_floor_n_ceiling(mlx, get_floor_colour(game), get_ceiling_colour(game));

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		init_ray_dir_n_map_pos(game, x, &map_x, &map_y);
		calculate_point_gap(ray);
		calculate_step_n_init_side_dist(ray, player, map_x, map_y);
		run_DDA(ray, game, &map_x, &map_y);
		calculate_line_height(ray);
		draw_wall_texture(&game->assets->textures[get_wall_direction(ray)], get_fractional_texture_position_x(ray, player), ray, mlx, &x);
		x++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->img->ptr, 0, 0);
}

int get_texture_pixel(t_img *texture, int x, int y)
{
	char *dst;
	dst = texture->address + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
	return *(int*)dst;
}

e_wall_direction	get_wall_direction(t_ray *ray)
{
	if (ray->wall_hit_side == VERTICAL) {
		if (ray->dir_x > 0) return SOUTH;  // Ray moving right hits EAST wall
		else return NORTH;                  // Ray moving left hits WEST wall
	} else { // HORIZONTAL
		if (ray->dir_y > 0) return EAST; // Ray moving down hits SOUTH wall
		else return WEST;                // Ray moving up hits NORTH wall
	}
}

// shading effect:
// if (ray->wall_hit_side == HORIZONTAL)
// 	color = ((color >> 1) & 0x7F7F7F);
void	draw_wall_texture(t_img *texture, double wall_x, t_ray *ray, t_mlx *mlx, int *x)
{
	int		tex_x;
	double	step;
	double	tex_pos;
	int		y;

	tex_x = (int)(wall_x * texture->width);
	if ((ray->wall_hit_side == VERTICAL && ray->dir_x > 0) \
		|| (ray->wall_hit_side == HORIZONTAL && ray->dir_y < 0))
	tex_x = texture->width - tex_x - 1;
	step = (double)texture->height / ray->line_height;
	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		int tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		int color = get_texture_pixel(texture, tex_x, tex_y);
		if (ray->wall_hit_side == HORIZONTAL)
			color = ((color >> 1) & 0x7F7F7F);
		my_mlx_pixel_put(mlx->img, *x, y, color);
		y++;
	}
}

// prepares_texture_scaling
// player_postition + the wall distance * ray_direction will determine exactly where the ray stopped
// then subtract the int value of the wall to get the ratio/fractional position of texel
double	get_fractional_texture_position_x(t_ray *ray, t_player *player)
{
	double wall_x;

	if (ray->wall_hit_side == VERTICAL)
		wall_x = player->pos_y + ray->prependicular_wall_distance * ray->dir_y;
	else
		wall_x = player->pos_x + ray->prependicular_wall_distance * ray->dir_x;

	wall_x -= floor(wall_x);
	return (wall_x);
}

// calculate line height, prependicular distance needed to avoid fisheye effect
// https://chat.qwen.ai/s/4eaf1fda-5ae9-4f03-b0c1-c08374235e65?fev=0.0.95
// derived from this formula, its mathematical proof, although not obviously related, using substitution
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

// run_DDA
// Decides whether to move x or y
// https://youtu.be/NbSee-XM7WA?si=km_sroyTrmMaxw0_&t=668
// Hits a vertical wall first	(ray->side_dist_x < ray->side_dist_y)
// Hits a horizontal wall first	(ray->side_dist_y += ray->delta_dist_y);
void	run_DDA(t_ray *ray, t_game *game, int *map_x, int *map_y)
{
	int	is_wall_hit;

	is_wall_hit = 0;
	while (!is_wall_hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			*map_x += ray->step_x;
			ray->wall_hit_side = VERTICAL;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			*map_y += ray->step_y;
			ray->wall_hit_side = HORIZONTAL;
		}
		// printf("height is %d\n", game->map->height);
		// printf("x is %d, y is %d\n", *map_x, *map_y);
		if (game->map->grid[*map_x][*map_y] > 0)
			is_wall_hit = 1;
	}
}

// used for side_dist_x/y, will multiply the delta to get the actual length,
// side_dist is like a ratio, could start from anywhere in the middle between x1/y1 to another x2/y2
// If it has to go in the negative or positive x-direction,
// and the negative or positive y-direction will depend on the direction of the ray,
// and this fact will be stored in stepX and stepY.
// Those variables are always either -1 or +1.
// posx and y might look the same here, but because of the movement hooks, theyre actually different,
// will be calculated to floating point numbers
void	calculate_step_n_init_side_dist(t_ray *ray, t_player *player, int map_x, int map_y)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (map_x + 1.0 - player->pos_x) * ray->delta_dist_x;
	}

	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (map_y + 1.0 - player->pos_y) * ray->delta_dist_y;
	}
}

//length of ray from one x to next x
//length of ray from one y-side to next y-side
void	calculate_point_gap(t_ray *ray)
{
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);

	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
}

// Needed because when moving or rotating, the player position changes, and it usually is a floating point
// EXPLANATION:	max value after 2 * x/SCREEN_WIDTH is 2, and min value is 0,
// using those values, subtract 1, can effectively represent:
//		-1 (left side of screen)
//		0 (center of screen)
//		1 (right side of screen)
// camera_x represents a like a percentage of where it is on the plane (-1 < 0 < 1) (Left Centre Right)
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
