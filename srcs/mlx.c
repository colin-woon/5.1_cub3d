/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:24:08 by cwoon             #+#    #+#             */
/*   Updated: 2025/04/14 19:49:17 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(int keycode, t_mlx *mlx);
int	key_hook(int keysym, t_mlx *mlx);
void	start_mlx();
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

int	key_hook(int keysym, t_mlx *mlx)
{
	// printf("DEBUG: sym INT is %d\n", keysym);
	printf("DEBUG: sym HEXA is %x\n", keysym);
	if (keysym == XK_Escape)
	{
		printf("DEBUG: Escape\n");
		close_window(0, NULL);
	}
	else if (keysym == XK_Left)
		printf("Left\n");
	else if (keysym == XK_Right)
		printf("Right\n");
	else if (keysym == XK_Up)
		printf("Up\n");
	else if (keysym == XK_Down)
		printf("Down\n");
	else if (keysym == XK_w)
		printf("w\n");
	else if (keysym == XK_a)
		printf("a\n");
	else if (keysym == XK_s)
		printf("s\n");
	else if (keysym == XK_d)
		printf("d\n");
	return (0);
}

int	close_window(int keycode, t_mlx *mlx)
{
	printf("DEBUG: closing window\n");
	exit(0);
	// mlx_destroy_window(mlx->mlx, mlx->window);
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->address + (y * img->line_length + x * (img->bits_per_pixel / 8));
	// printf("endian%d\n", img->endian);
	*(unsigned int*)dst = color;
}

void put_one_pixel(t_mlx *mlx)
{
	mlx->img = malloc(sizeof(t_img));
	mlx->img->ptr = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);

	mlx->img->address = mlx_get_data_addr(mlx->img->ptr, &mlx->img->bits_per_pixel, &mlx->img->line_length,
								&mlx->img->endian);
	my_mlx_pixel_put(mlx->img, 10, 10, create_trgb(0, 220, 100, 0));
	mlx_put_image_to_window(mlx->ptr, mlx->window, mlx->img->ptr, 0, 0);
}

void start_mlx()
{
	t_mlx	mlx;

	mlx.ptr = mlx_init();
	mlx.window = mlx_new_window(mlx.ptr, WIDTH, HEIGHT, "Cub3d");
	mlx_hook(mlx.window, DestroyNotify, 0, close_window, &mlx);
	mlx_hook(mlx.window, KeyPress, 1, key_hook, &mlx);
	put_one_pixel(&mlx);
	mlx_loop(mlx.ptr);
}
