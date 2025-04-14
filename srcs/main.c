/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 06:57:25 by rteoh             #+#    #+#             */
/*   Updated: 2025/04/14 17:23:53 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	key_hook1(int keysym, t_vars *vars)
{
	printf("DEBUG: sym int is %d\n", keysym);
	printf("DEBUG: sym hexa is %x\n", keysym);
	if (keysym == XK_Escape)
		printf("Escape\n");
	else if (keysym == XK_Left)
		printf("Left\n");
	else if (keysym == XK_Right)
		printf("Right\n");
	else if (keysym == XK_Up)
		printf("Up\n");
	else if (keysym == XK_Down)
		printf("Down\n");
	return (0);
}

int	close_window(int keycode, t_vars *vars)
{
	printf("hello");
	exit(0);
	// mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	mlx_hook(vars.win, DestroyNotify, 0, close_window, &vars);
	mlx_hook(vars.win, KeyPress, 1, key_hook1, &vars);
	mlx_loop(vars.mlx);
}
