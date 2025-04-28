/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 06:57:25 by rteoh             #+#    #+#             */
/*   Updated: 2025/04/28 19:01:16 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int close_window(int keycode, t_game *game)
{
	mlx_destroy_window(game->mlx_data->ptr, game->mlx_data->window);
	exit(0);
}

int main(int ac, char *av[])
{
	t_game game;

	if (ac != 2)
	{
		msg("Bad Input\nExample: ./cub3D .cub\n");
		return (0);
	}
		// game.mlx_data->ptr = mlx_init();
		// game.mlx_data->window = mlx_new_window(game.mlx_data->ptr, WIDTH, HEIGHT, "hello");
		// mlx_put_image_to_window(game.mlx_data->ptr, game.mlx_data->window, game.textures->no_img_ptr, 0, 0);
		// mlx_hook(game.mlx_data->window, 2, 1L << 0, close_window, &game);
		// mlx_loop(game.mlx_data->ptr);
	parse(av[1], &game);
	start_mlx();
	return (0);
}
