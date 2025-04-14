/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:24:08 by cwoon             #+#    #+#             */
/*   Updated: 2025/04/14 18:26:00 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(int keycode, t_mlx *mlx);
int	key_hook(int keysym, t_mlx *mlx);
void	start_mlx();

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

void start_mlx()
{
	t_mlx	mlx;

	mlx.ptr = mlx_init();
	mlx.window = mlx_new_window(mlx.ptr, WIDTH, HEIGHT, "Cub3d");
	mlx_hook(mlx.window, DestroyNotify, 0, close_window, &mlx);
	mlx_hook(mlx.window, KeyPress, 1, key_hook, &mlx);
	mlx_loop(mlx.ptr);
}
