/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 06:57:25 by rteoh             #+#    #+#             */
/*   Updated: 2025/05/29 18:46:27 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		game_loop(t_game *game);
void	run_mlx(t_game *game);
void	get_map_grid(t_map *map);

int main(int ac, char *av[])
{
	t_game	game;

	game.is_render = false;
	// DEBUG_init_map(&game);
	// if (ac != 2)
	// {
	// 	msg("Bad Input\nExample: ./cub3D .cub\n");
	// 	return (0);
	// }
	// game = (t_game){0};
	start_mlx(&game);
	if (parse(av[1], &game) == false)
		exit(EXIT_FAILURE);
	// free_texture(&game);
	init_player(&game.player, game.map);
	game.ray = malloc(sizeof(t_ray));
	// DEBUG_print_map_assets(&game);
	get_map_grid(game.map);
	run_raycasting(game.ray, game.player, game.mlx_data, &game);
	run_mlx(&game);
	return (0);
}

int	mouse_hook(int x, int y, t_game *game);
void rotate_player(t_player *player, double angle);

void	run_mlx(t_game *game)
{
	// mlx_mouse_hide(game->mlx_data->ptr, game->mlx_data->window);
	mlx_hook(game->mlx_data->window, KeyPress, 1, movement_keys, game);
	// mlx_mouse_move(game->mlx_data->ptr, game->mlx_data->window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	mlx_hook(game->mlx_data->window, MotionNotify, 1L << 6, mouse_hook, game);
	mlx_loop_hook(game->mlx_data->ptr, game_loop, game);
	mlx_loop(game->mlx_data->ptr);
}

int	mouse_hook(int x, int y, t_game *game)
{
	printf("x: %d y: %d\n", x, y);
	printf("x: %d y: %d\n", x, y);
	(void)y;
	double	delta_x;
	double	rotation_angle;

    if (!game->mouse_initialized) {
        game->last_mouse_x = x;
        game->mouse_initialized = 1;
        return (0);
    }
	delta_x = (double)(x - game->last_mouse_x);
	rotation_angle = -delta_x * MOUSE_SENSITIVITY;
    if (fabs(delta_x) > 1.0) {
        rotation_angle = -delta_x * MOUSE_SENSITIVITY;
        rotate_player(game->player, rotation_angle);
        game->is_render = true;
    }

    game->last_mouse_x = x;
    return (0);
}

void rotate_player(t_player *player, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(angle) - player->plane_y * sin(angle);
	player->plane_y = old_plane_x * sin(angle) + player->plane_y * cos(angle);
}

int	game_loop(t_game *game)
{
	if (game->is_render)
	{
		run_raycasting(game->ray, game->player, game->mlx_data, game);
		game->is_render = false;
	}
	return (0);
}

void	get_map_grid(t_map *map)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	map->grid = malloc(map->height * sizeof(int*));
	while (i < map->height)
	{
		map->grid[i] = malloc(map->width * sizeof(int));
		i++;
	}

	x = 0;
	while(x < map->height)
	{
		y = 0;
		while (y < map->width)
		{
			if (ft_isspace(map->layout[x][y]))
				map->grid[x][y] = -1;
			else if (!ft_strncmp(&map->layout[x][y], "1", 1))
				map->grid[x][y] = 1;
			else
				map->grid[x][y] = 0;
			// printf("%d ", map->grid[x][y]);
			y++;
		}
		// printf("\n");
		x++;
	}
}
