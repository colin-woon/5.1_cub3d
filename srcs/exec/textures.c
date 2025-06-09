/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:12:57 by cwoon             #+#    #+#             */
/*   Updated: 2025/06/09 14:48:36 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					get_texture_pixel(t_img *texture, int x, int y);
double				get_fractional_texture_position_x\
(t_ray *ray, t_player *player);
t_wall_dir			get_wall_dir(t_ray *ray);
void				put_texture_pixels\
(t_texture_vars *tex, t_img *texture, t_game *game, int *x);
void				prep_texture_vars\
(t_texture_vars *tex, t_img *texture, t_ray *ray, t_player *player);

int	get_texture_pixel(t_img *texture, int x, int y)
{
	char	*dst;

	dst = texture->address \
+ (y * texture->line_length + x * (texture->bits_per_pixel / 8));
	return (*(int *)dst);
}

// This follows the graphical coordinate system in mlx where:
// +y = down(S)  // -y = up(N)
// +x = right(E) // -x = left(W)
t_wall_dir	get_wall_dir(t_ray *ray)
{
	if (ray->wall_hit_side == VERTICAL)
	{
		if (ray->dir_x > 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (ray->dir_y > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

// 1. avoid mirroring (optional cause textures used is asymmetric)
// 	if ((ray->wall_hit_side == VERTICAL && ray->dir_x > 0)
// || (ray->wall_hit_side == HORIZONTAL && ray->dir_y < 0))
// 		tex->x = texture->width - tex->x - 1;
// 2. step is to get the gap of texture pixels for 1 wall pixel
// 3. horizon is to ensure that the texture wont have a "swimming" effect
// 4. tex.pos is the fractional y position in the texture
void	prep_texture_vars\
(t_texture_vars *tex, t_img *texture, t_ray *ray, t_player *player)
{
	double	screen_horizon_pitched;

	if (ray->line_height == 0)
		tex->step = 0;
	else
		tex->step = (double)texture->height / ray->line_height;
	screen_horizon_pitched = SCREEN_HEIGHT / 2.0 + player->pitch;
	tex->pos = (texture->height / 2.0) + \
(ray->draw_start - screen_horizon_pitched) * tex->step;
}

// 1. tex->y = (int)tex->pos & (texture->height - 1);
// the purpose is to warp it around the textures, get the actual y
// can use % here too, but will be slower, but will work for any texture
// & operator works only for textures with dimensions that are power of 2
// texture_height - 1 is like a bitmask eg: 64x64 px 64-1=63
// 63 bitmask is 00111111
// take 65 AND 63 = 10000001 & 00111111,
// resulting only 1, effectively warping around
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
		if (game->ray->wall_hit_side == VERTICAL)
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
