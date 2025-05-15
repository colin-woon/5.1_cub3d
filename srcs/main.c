/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 06:57:25 by rteoh             #+#    #+#             */
/*   Updated: 2025/05/15 17:59:53 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void run_raycasting(t_ray *ray, t_player *player, t_mlx *mlx, t_game *game);
int	game_loop(t_game *game);
int get_pixel(t_img *texture, int x, int y);

void	run_mlx(t_game *game);

int main(int ac, char *av[])
{
	t_game	game;

	int		debug_map[24][24] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	// int		debug_map[DEBUG_MAP_HEIGHT][DEBUG_MAP_WIDTH] =
	// {
	// 	{1,1,1,1,1},
	// 	{1,0,1,0,1},
	// 	{1,0,0,0,1},
	// 	{1,0,0,0,1},
	// 	{1,1,1,1,1},
	// };
	memcpy(game.map, debug_map, sizeof(debug_map));

	// if (ac != 2)
	// {
	// 	msg("Bad Input\nExample: ./cub3D .cub\n");
	// 	return (0);
	// }
	// parse(av[1], &game);
	start_mlx(&game);
	init_player(&game.player);
	game.ray = malloc(sizeof(t_ray));
	run_raycasting(game.ray, game.player, game.mlx_data, &game);
	run_mlx(&game);
	return (0);
}

void	run_mlx(t_game *game)
{
	mlx_hook(game->mlx_data->window, KeyPress, 1, movement_keys, game);
	mlx_loop_hook(game->mlx_data->ptr, game_loop, game);
	mlx_loop(game->mlx_data->ptr);
}

int	game_loop(t_game *game)
{
	run_raycasting(game->ray, game->player, game->mlx_data, game);
	return (0);
}

void run_raycasting(t_ray *ray, t_player *player, t_mlx *mlx, t_game *game)
{
	int x = 0;
	static bool is_already_init_texture = false;
	static t_img texture;
	// printf("\n--- Player Initial Values ---\n");
    // printf("Position: (x: %.2f, y: %.2f)\n", player->pos_x, player->pos_y);
    // printf("Direction: (x: %.2f, y: %.2f)\n", player->dir_x, player->dir_y);
    // printf("Camera Plane: (x: %.2f, y: %.2f)\n", player->plane_x, player->plane_y);
    // printf("---------------------------\n\n");

	init_floor_and_ceiling(mlx, 0);

	while (x < WIDTH)
	{
		// printf("DEBUG: test\n");
		// EXPLANATION:	max value after 2 * x/WIDTH is 2, and min value is 0,
		// using those values, subtract 1, can effectively represent:
		//		-1 (left side of screen)
		//		0 (center of screen)
		//		1 (right side of screen)
		// camera_x represents a like a percentage of where it is on the plane (-1 < 0 < 1) (Left Centre Right)
		ray->camera_x = 2 * x / (double)WIDTH - 1;
		ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
		ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;

		// Needed because when moving or rotating, the player position changes, and it usually is a floating point
		int map_x = (int)player->pos_x;
		int map_y = (int)player->pos_y;


		//length of ray from one x to next x
		if (ray->dir_x == 0)
			ray->delta_dist_x = 1e30;
		else
			ray->delta_dist_x = fabs(1 / ray->dir_x);

		//length of ray from one y-side to next y-side
		if (ray->dir_y == 0)
			ray->delta_dist_y = 1e30;
		else
			ray->delta_dist_y = fabs(1 / ray->dir_y);

		ray->is_wall_hit = 0;

		// used for side_dist_x/y, will multiply the delta to get the actual length,
		// side_dist is like a ratio, could start from anywhere in the middle between x1/y1 to another x2/y2
		// If it has to go in the negative or positive x-direction,
		// and the negative or positive y-direction will depend on the direction of the ray,
		// and this fact will be stored in stepX and stepY.
		// Those variables are always either -1 or +1.
		// posx and y might look the same here, but because of the movement hooks, theyre actually different,
		// will be calculated to floating point numbers

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

		// DDA
		// Decides whether to move x or y
		// https://youtu.be/NbSee-XM7WA?si=km_sroyTrmMaxw0_&t=668
		while (!ray->is_wall_hit)
		{
			// Hits a vertical wall first
			if (ray->side_dist_x < ray->side_dist_y)
			{
				ray->side_dist_x += ray->delta_dist_x;
				map_x += ray->step_x;
				ray->wall_hit_side = VERTICAL;
			}
			else
			// Hits a horizontal wall first
			{
				ray->side_dist_y += ray->delta_dist_y;
				map_y += ray->step_y;
				ray->wall_hit_side = HORIZONTAL;
			}

			if (game->map[map_x][map_y] > 0)
				ray->is_wall_hit = 1;
		}


		if (ray->wall_hit_side == VERTICAL)
			ray->prependicular_wall_distance = (ray->side_dist_x - ray->delta_dist_x);
		else
			ray->prependicular_wall_distance = (ray->side_dist_y - ray->delta_dist_y);

		ray->line_height = (int)(WALL_HEIGHT_SCALE * HEIGHT / ray->prependicular_wall_distance);

		ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
		if (ray->draw_start < 0)
			ray->draw_start = 0;
			ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
		if (ray->draw_end >= HEIGHT)
			ray->draw_end = HEIGHT - 1;

		if (!is_already_init_texture)
		{
			texture.ptr = mlx_xpm_file_to_image(game->mlx_data->ptr, "texture/water.xpm", &texture.height, &texture.width);
			if (!texture.ptr)
			{
				printf("error loading texture\n");
				exit(EXIT_FAILURE);
			}
			texture.address = mlx_get_data_addr(texture.ptr,
				&texture.bits_per_pixel,
				&texture.line_length,
				&texture.endian);
			is_already_init_texture = true;
		}

		double wall_x;
		if (ray->wall_hit_side == VERTICAL)
			wall_x = player->pos_y + ray->prependicular_wall_distance * ray->dir_y;
		else
			wall_x = player->pos_x + ray->prependicular_wall_distance * ray->dir_x;

		wall_x -= floor(wall_x);

		int tex_x = (int)(wall_x * texture.width);
		if ((ray->wall_hit_side == VERTICAL && ray->dir_x > 0) || (ray->wall_hit_side == HORIZONTAL && ray->dir_y < 0))
			tex_x = texture.width - tex_x - 1;

		double step = (double)texture.height / ray->line_height;
		double tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;

		for (int y = ray->draw_start; y <= ray->draw_end; y++) {
			int tex_y = (int)tex_pos & (texture.height - 1);
			tex_pos += step;
			int color = get_pixel(&texture, tex_x, tex_y);
			if (ray->wall_hit_side == HORIZONTAL)
				color = ((color >> 1) & 0x7F7F7F);
			my_mlx_pixel_put(mlx->img, x, y, color);
		}
		// draw_vertical_line(mlx, x, ray->draw_start, ray->draw_end, create_trgb(0, 220, 0, 0));
		x++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->img->ptr, 0, 0);
}

int get_pixel(t_img *texture, int x, int y)
{
    char *dst;
    dst = texture->address + (y * texture->line_length + x * (texture->bits_per_pixel / 8));
    return *(int*)dst;
}
