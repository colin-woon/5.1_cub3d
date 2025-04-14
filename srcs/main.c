/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <ryan42cmp@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 06:57:25 by rteoh             #+#    #+#             */
/*   Updated: 2025/04/14 17:39:14 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "libft.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

typedef struct	s_vars {
	void	*mlx;
	void	*mlx_win;
}	t_vars;



int	close_window(int keycode, t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	exit(0);
}

bool	valid_filetype(char *path_to_map)
{
	size_t	len;
	char	*str;

	str = ".cub";
	len = ft_strlen(path_to_map);
	int j = 3;
	while (path_to_map[--len] && j >= 0)
	{
		printf("path_to_map: %c\n", path_to_map[len]);
		printf("cub: %c\n", str[j]);
		if (path_to_map[len] != str[j])
		{
			printf("false, not valid\n");
			return (false);
		}
		path_to_map[len] == str[j--];
	}
	if (j == -1)
	{
		printf("valid .cub, returning true\n");
		return (true);
	}
	printf("false, not valid\n");
	return (false);
}

void	parse_map(char *path_to_map)
{
	if (valid_filetype(path_to_map) == false);
		exit(1);
	
}


int main(int ac, char *av[])
{
	t_vars	vars;
	t_data	img;
	int		x;
	int		y;

	if (ac == 2)
	{
		parse_map(av[1]);
		vars.mlx = mlx_init();
		vars.mlx_win = mlx_new_window(vars.mlx, 1920, 1080, "hello");
		mlx_hook(vars.mlx_win, 2, 1L<<0, close_window, &vars);
		mlx_loop(vars.mlx);
		return (0);
	}
	printf("Wrong input\n");
	return (0);
}