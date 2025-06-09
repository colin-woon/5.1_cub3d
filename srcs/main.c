/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 06:57:25 by rteoh             #+#    #+#             */
/*   Updated: 2025/06/09 21:29:13 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		game_loop(t_game *game);
void	run_mlx(t_game *game);

int	main(int ac, char *av[])
{
	t_game	game;

	game.is_render = false;
	if (ac != 2)
	{
		msg("Bad Input\nExample: ./cub3D .cub\n");
		return (0);
	}
	game = (t_game){0};
	start_mlx(&game);
	if (ft_strend(av[1], ".cub") == false)
		error_msg_exit("input given is not a .cub file\n", &game);
	if (parse(av[1], &game) == false)
	{
		cleanup(&game);
		exit(EXIT_FAILURE);
	}
	init_player(&game.player, game.map, &game);
	game.ray = malloc(sizeof(t_ray));
	get_map_grid(game.map);
	run_raycasting(game.ray, game.player, game.mlx_data, &game);
	run_mlx(&game);
	return (0);
}

void	run_mlx(t_game *game)
{
	mlx_mouse_hide(game->mlx_data->ptr, game->mlx_data->window);
	mlx_hook(game->mlx_data->window, KeyPress, 1, movement_keys, game);
	mlx_hook(game->mlx_data->window, MotionNotify, 1L << 6, mouse_hook, game);
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
