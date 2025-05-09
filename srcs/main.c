/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 06:57:25 by rteoh             #+#    #+#             */
/*   Updated: 2025/05/06 16:58:55 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void run_raycasting(t_ray *ray, t_player *player, t_mlx *mlx, t_game *game);
int	game_loop(t_game *game);

void	run_mlx(t_game *game);

int main(int ac, char *av[])
{
	t_game	game;

	// int		debug_map[24][24] =
	// {
	// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	// 	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	// 	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	// };
	int		debug_map[DEBUG_MAP_HEIGHT][DEBUG_MAP_WIDTH] =
	{
		{1,1,1,1,1},
		{1,0,1,0,1},
		{1,0,0,0,1},
		{1,0,0,0,1},
		{1,1,1,1,1},
	};
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
	// printf("\n--- Player Initial Values ---\n");
    // printf("Position: (x: %.2f, y: %.2f)\n", player->pos_x, player->pos_y);
    // printf("Direction: (x: %.2f, y: %.2f)\n", player->dir_x, player->dir_y);
    // printf("Camera Plane: (x: %.2f, y: %.2f)\n", player->plane_x, player->plane_y);
    // printf("---------------------------\n\n");

	init_floor_and_ceiling(mlx, 0);

	while (x < WIDTH)
	{
		// printf("DEBUG: test\n");
		ray->camera_x = 2 * x / (double)WIDTH - 1;
		ray->dir_x = player->dir_x + player->plane_x * ray->camera_x;
		ray->dir_y = player->dir_y + player->plane_y * ray->camera_x;

		int map_x = (int)player->pos_x;
		int map_y = (int)player->pos_y;

		if (ray->dir_x == 0)
			ray->delta_dist_x = 1e30;
		else
			ray->delta_dist_x = fabs(1 / ray->dir_x);
		if (ray->dir_y == 0)
			ray->delta_dist_y = 1e30;
		else
			ray->delta_dist_y = fabs(1 / ray->dir_y);

		ray->is_wall_hit = 0;

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
		while (!ray->is_wall_hit)
		{
			if (ray->side_dist_x < ray->side_dist_y)
			{
				ray->side_dist_x += ray->delta_dist_x;
				map_x += ray->step_x;
				ray->wall_hit_side = 0;
			}
			else
			{
				ray->side_dist_y += ray->delta_dist_y;
				map_y += ray->step_y;
				ray->wall_hit_side = 1;
			}

			if (game->map[map_x][map_y] > 0)
				ray->is_wall_hit = 1;
		}

		if (ray->wall_hit_side == 0)
			ray->prep_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
		else
			ray->prep_wall_dist = (ray->side_dist_y - ray->delta_dist_y);

		ray->line_height = (int)(HEIGHT / ray->prep_wall_dist);

		ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
		if (ray->draw_start < 0)
			ray->draw_start = 0;
			ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
		if (ray->draw_end >= HEIGHT)
			ray->draw_end = HEIGHT - 1;

		draw_vertical_line(mlx, x, ray->draw_start, ray->draw_end, create_trgb(0, 220, 0, 0));
		x++;
	}
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->img->ptr, 0, 0);
}
