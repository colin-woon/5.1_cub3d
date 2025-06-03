/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:15:34 by cwoon             #+#    #+#             */
/*   Updated: 2025/06/02 22:23:39 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	run_dda(t_ray *ray, t_game *game, int *map_x, int *map_y);
void	calculate_step_n_init_side_dist\
(t_ray *ray, t_player *player, int map_x, int map_y);
void	calculate_point_gap(t_ray *ray);

// run_dda
// Decides whether to move x or y
// https://youtu.be/NbSee-XM7WA?si=km_sroyTrmMaxw0_&t=668
// Hits a vertical wall first	(ray->side_dist_x < ray->side_dist_y)
// Hits a horizontal wall first	(ray->side_dist_y += ray->delta_dist_y);
// printf("height is %d\n", game->map->height);
// printf("x is %d, y is %d\n", *map_x, *map_y);
void	run_dda(t_ray *ray, t_game *game, int *map_x, int *map_y)
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
		if (game->map->grid[*map_y][*map_x] > 0)
			is_wall_hit = 1;
	}
}


// 1. side_dist is like a ratio,
// will multiply the delta to get the actual length,
// could start from anywhere in the middle between x1/y1 to another x2/y2
// 2. Depending on the ray direction, we calculate which side dist is required
// 3. Steps are always either -1 or +1.
// 4. posx and y are floating numbers,
// itll always be different due to movement and rotation
void	calculate_step_n_init_side_dist\
(t_ray *ray, t_player *player, int map_x, int map_y)
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


// length of ray from one x to next x
// length of ray from one y-side to next y-side
// 1e30 = 1*10^30 - represents "infinite distance"
// needed for dda where if the ray is in a perfect straight line,
// the dda algo will choose to step in its corresponding axis
// , prevents division with 0;
// eg: if perfectly straight on x axis, will always step to y-axis vice versa
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
