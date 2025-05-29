/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:12:57 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/29 14:49:47 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					get_texture_pixel(t_img *texture, int x, int y);
double				get_fractional_texture_position_x\
(t_ray *ray, t_player *player);
t_wall_direction	get_wall_direction(t_ray *ray);
void				put_texture_pixels\
(t_texture_vars *tex, t_img *texture, t_game *game, int *x);
void				prep_texture_vars\
(t_texture_vars *tex, double wall_x, t_img *texture, t_ray *ray);

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
t_wall_direction	get_wall_direction(t_ray *ray)
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

void	prep_texture_vars\
(t_texture_vars *tex, double wall_x, t_img *texture, t_ray *ray)
{
	tex->x = (int)(wall_x * texture->width);
	if ((ray->wall_hit_side == VERTICAL && ray->dir_x > 0) \
|| (ray->wall_hit_side == HORIZONTAL && ray->dir_y < 0))
		tex->x = texture->width - tex->x - 1;
	tex->step = (double)texture->height / ray->line_height;
	tex->pos \
= (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2) * tex->step;
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
		wall_x = player->pos_y + ray->prependicular_wall_distance * ray->dir_y;
	else
		wall_x = player->pos_x + ray->prependicular_wall_distance * ray->dir_x;
	wall_x -= floor(wall_x);
	return (wall_x);
}
