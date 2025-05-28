/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:12:57 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/29 01:39:26 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					get_texture_pixel(t_img *texture, int x, int y);
void				draw_wall_texture\
(t_img *texture, double wall_x, t_ray *ray, t_mlx *mlx, int *x);
double				get_fractional_texture_position_x\
(t_ray *ray, t_player *player);
t_wall_direction	get_wall_direction(t_ray *ray);

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

// shading effect:
// if (ray->wall_hit_side == HORIZONTAL)
// 	color = ((color >> 1) & 0x7F7F7F);
void	draw_wall_texture\
(t_img *texture, double wall_x, t_ray *ray, t_mlx *mlx, int *x)
{
	int		tex_x;
	int		tex_y;
	int		color;
	double	step;
	double	tex_pos;
	int		y;

	tex_x = (int)(wall_x * texture->width);
	if ((ray->wall_hit_side == VERTICAL && ray->dir_x > 0) \
|| (ray->wall_hit_side == HORIZONTAL && ray->dir_y < 0))
		tex_x = texture->width - tex_x - 1;
	step = (double)texture->height / ray->line_height;
	tex_pos \
= (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		color = get_texture_pixel(texture, tex_x, tex_y);
		if (ray->wall_hit_side == HORIZONTAL)
			color = ((color >> 1) & 0x7F7F7F);
		my_mlx_pixel_put(mlx->img, *x, y, color);
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
