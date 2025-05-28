/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:24:08 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/29 01:05:53 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		close_window(int keycode, t_game *game);
void	start_mlx(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	init_mlx_img(t_mlx *mlx);

int	close_window(int keycode, t_game *game)
{
	printf("DEBUG: closing window\n");
	cleanup(game);
	exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->address \
+ (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	init_mlx_img(t_mlx *mlx)
{
	mlx->img = malloc(sizeof(t_img));
	mlx->img->ptr = mlx_new_image(mlx->ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	mlx->img->address = mlx_get_data_addr(mlx->img->ptr, \
&mlx->img->bits_per_pixel, &mlx->img->line_length, &mlx->img->endian);
}

void	start_mlx(t_game *game)
{
	t_mlx	mlx;
	void	*img;
	int		img_width;
	int		img_height;

	game->mlx_data = malloc(sizeof(t_mlx));
	game->mlx_data->ptr = mlx_init();
	game->mlx_data->window = mlx_new_window\
(game->mlx_data->ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
	mlx_hook(game->mlx_data->window, DestroyNotify, 0, close_window, &game);
	init_mlx_img(game->mlx_data);
}
