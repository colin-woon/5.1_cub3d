/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 06:57:25 by rteoh             #+#    #+#             */
/*   Updated: 2025/04/28 16:11:39 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int close_window(int keycode, t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_win);
	exit(0);
}

int main(int ac, char *av[])
{
	t_game game;
	int x;
	int y;

	if (ac == 2)
	{
		game.mlx = mlx_init();
		game.mlx_win = mlx_new_window(game.mlx, 1920, 1080, "hello");
		parse(av[1], &game);
		mlx_put_image_to_window(game.mlx, game.mlx_win, game.textures->n_tex_img, 0, 0);
		mlx_hook(game.mlx_win, 2, 1L << 0, close_window, &game);
		mlx_loop(game.mlx);
		return (0);
	}
	msg("Bad Input\nExample ./cub3D .cub\n");
	return (0);
}
