/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 06:57:25 by rteoh             #+#    #+#             */
/*   Updated: 2025/05/29 00:44:28 by cwoon            ###   ########.fr       */
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

void	run_mlx(t_game *game)
{
	mlx_hook(game->mlx_data->window, KeyPress, 1, movement_keys, game);
	mlx_loop_hook(game->mlx_data->ptr, game_loop, game);
	mlx_loop(game->mlx_data->ptr);
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
