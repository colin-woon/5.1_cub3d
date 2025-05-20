/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:24:08 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/06 16:07:50 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(int keycode, t_game *game);
void	start_mlx(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void init_mlx_img(t_mlx *mlx);
void draw_vertical_line(t_mlx *mlx, int x, int from, int to, int color);
void init_floor_and_ceiling(t_mlx *mlx, int color);

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

	dst = img->address + (y * img->line_length + x * (img->bits_per_pixel / 8));
	// printf("endian%d\n", img->endian);
	*(unsigned int*)dst = color;
}

void init_mlx_img(t_mlx *mlx)
{
	mlx->img = malloc(sizeof(t_img));
	mlx->img->ptr = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);

	mlx->img->address = mlx_get_data_addr(mlx->img->ptr, &mlx->img->bits_per_pixel, &mlx->img->line_length,
								&mlx->img->endian);
}
// DEBUG: create_trgb should change to color/texture
void draw_vertical_line(t_mlx *mlx, int x, int from, int to, int color)
{
	(void)color;
	int y = from;

	while (y < to)
	{
		my_mlx_pixel_put(mlx->img, x, y, create_trgb(0, 220, 100, 0));
		y++;
	}
}

// DEBUG: should add ceiling texture, floor texture
void init_floor_and_ceiling(t_mlx *mlx, int color)
{
	int x;
	int y;

	(void)color;
	x = 0;
	while (x < HEIGHT/2)
	{
		y = 0;
		while (y < WIDTH)
		{
			my_mlx_pixel_put(mlx->img, y, x, create_trgb(0, 0, 0, 220));
			y++;
		}
		x++;
	}
	while (x < HEIGHT)
	{
		y = 0;
		while (y < WIDTH)
		{
			my_mlx_pixel_put(mlx->img, y, x, create_trgb(0, 0, 220, 0));
			y++;
		}
		x++;
	}
}

void start_mlx(t_game *game)
{
	t_mlx	mlx;
	void	*img;
	// char	*relative_path = "imgs/Tung_tung_tung_tung_tung_sahur.xpm";
	int		img_width;
	int		img_height;

	game->mlx_data = malloc(sizeof(t_mlx));
	game->mlx_data->ptr = mlx_init();
	game->mlx_data->window = mlx_new_window(game->mlx_data->ptr, WIDTH, HEIGHT, "Cub3d");
	mlx_hook(game->mlx_data->window, DestroyNotify, 0, close_window, &game);
	init_mlx_img(game->mlx_data);
	// draw_pixels(game->mlx_data);
	// img = mlx_xpm_file_to_image(game->mlx_data->ptr, relative_path, &img_width, &img_height);
	// if (!img)
	// 	printf("image failed to read\n");
	// mlx_put_image_to_window(game->mlx_data->ptr, game->mlx_data->window, img, 100, 100);
	// mlx_loop(game->mlx_data->ptr);
}
