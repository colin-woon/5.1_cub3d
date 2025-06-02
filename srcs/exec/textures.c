/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:12:57 by cwoon             #+#    #+#             */
/*   Updated: 2025/06/02 17:03:46 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					get_texture_pixel(t_img *texture, int x, int y);
double				get_fractional_texture_position_x\
(t_ray *ray, t_player *player);
t_wall_dir	get_wall_dir(t_ray *ray);
void				put_texture_pixels\
(t_texture_vars *tex, t_img *texture, t_game *game, int *x);
// void				prep_texture_vars\
// (t_texture_vars *tex, double wall_x, t_img *texture, t_ray *ray);
void prep_texture_vars(t_texture_vars *tex, double wall_x, t_img *texture, t_ray *ray, t_player *player);


int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*dst;

	dst = texture->address \
+ (y * texture->line_length + x * (texture->bits_per_pixel / 8));
	return (*(int *)dst);
}

// Ray moving right hits EAST wall
// Ray moving left hits WEST wall
// HORIZONTAL
// Ray moving down hits SOUTH wall
// Ray moving up hits NORTH wall
t_wall_dir	get_wall_dir(t_ray *ray)
{
	if (ray->wall_hit_side == VERTICAL)
	{
		if (ray->dir_x > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
	else
	{
		if (ray->dir_y > 0)
			return (EAST);
		else
			return (WEST);
	}
}

// MODIFIED Function Signature and Implementation:
void prep_texture_vars(t_texture_vars *tex, double wall_x, t_img *texture, t_ray *ray, t_player *player)
{
	// X coordinate in texture (horizontal)
	tex->x = (int)(wall_x * texture->width);
	// Flip texture X if necessary (standard practice to avoid mirrored textures)
	if ((ray->wall_hit_side == VERTICAL && ray->dir_x > 0) ||
		(ray->wall_hit_side == HORIZONTAL && ray->dir_y < 0)) // Conditions might depend on your coordinate system and wall definitions
		tex->x = texture->width - tex->x - 1;

	// Calculate step size for texture Y coordinate per screen pixel Y
	// ray->line_height is the full projected height of the wall column on screen (calculated in calculate_wall_projection)
	if (ray->line_height == 0) // Avoid division by zero if line_height is somehow 0
		tex->step = 0;
	else
		tex->step = (double)texture->height / ray->line_height;

	// Calculate starting texture Y position for the first screen pixel (ray->draw_start)
	// This formula ensures the texture "sticks" to the wall correctly, accounting for pitch.
	// It maps the screen Y coordinates to texture Y coordinates relative to the (pitched) horizon.
	double screen_horizon_pitched = SCREEN_HEIGHT / 2.0 + player->pitch;

	// tex->pos will be the texture Y coordinate corresponding to the screen Y ray->draw_start
	tex->pos = (texture->height / 2.0) + (ray->draw_start - screen_horizon_pitched) * tex->step;
}

// shading effect:
// if (ray->wall_hit_side == HORIZONTAL)
// 	color = ((color >> 1) & 0x7F7F7F);
void	put_texture_pixels\
(t_texture_vars *tex, t_img *texture, t_game *game, int *x)
{
	int	y;

	y = game->ray->draw_start;
	while (y <= game->ray->draw_end)
	{
		tex->y = (int)tex->pos & (texture->height - 1);
		tex->pos += tex->step;
		tex->color = get_texture_pixel(texture, tex->x, tex->y);
		if (game->ray->wall_hit_side == HORIZONTAL)
			tex->color = ((tex->color >> 1) & 0x7F7F7F);
		my_mlx_pixel_put(game->mlx_data->img, *x, y, tex->color);
		y++;
	}
}

// prepares_texture_scaling
// player_postition + the wall distance * ray_direction
// will determine exactly where the ray stopped
// then subtract the int value of the wall
// to get the ratio/fractional position of texel
double	get_fractional_texture_position_x(t_ray *ray, t_player *player)
{
	double	wall_x;

	if (ray->wall_hit_side == VERTICAL)
		wall_x = player->pos_y + ray->perpendicular_wall_distance * ray->dir_y;
	else
		wall_x = player->pos_x + ray->perpendicular_wall_distance * ray->dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}


