/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <ryan42cmp@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 06:57:25 by rteoh             #+#    #+#             */
/*   Updated: 2025/04/22 21:21:36 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "libft.h"
#include <fcntl.h> //for the open

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

typedef struct s_vars
{
	void *mlx;
	void *mlx_win;
} t_vars;

int close_window(int keycode, t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	exit(0);
}

static bool ft_strend(char *s, char *suffix)
{
	size_t s_len;
	size_t suffix_len;

	s_len = ft_strlen(s);
	suffix_len = ft_strlen(suffix);

	if (suffix_len > s_len)
		return false;
	while (suffix_len > 0)
	{
		if (s[s_len--] != suffix[suffix_len--])
			return (false);
	}
	return true;
}

// bool	valid_filetype(char *path_to_map)
// {
// 	size_t	len;
// 	char	*str;

// 	str = ".cub";
// 	len = ft_strlen(path_to_map);
// 	int j = 3;
// 	while (path_to_map[--len] && j >= 0)
// 	{
// 		printf("path_to_map: %c\n", path_to_map[len]);
// 		printf("cub: %c\n", str[j]);
// 		if (path_to_map[len] != str[j])
// 		{
// 			printf("false, not valid\n");
// 			return (false);
// 		}
// 		path_to_map[len] == str[j--];
// 	}
// 	if (j == -1)
// 	{
// 		printf("valid .cub, returning true\n");
// 		return (true);
// 	}
// 	printf("false, not valid\n");
// 	return (false);
// }

char	*get_next_row(int fd)
{
	char *line;
	char *res_line;
	
	line = get_next_line(fd);
	res_line = ft_strtrim(line, "\n");
	free(line);
	return (res_line);
}

typedef struct s_texture
{
	void	*n_texture;
	void	*s_texture;
	void	*e_texture;
	void	*w_texture;
}	t_texture;


void parse_map(char *path_to_map)
{
	int fd;
	t_texture	*textures;

	if (ft_strend(path_to_map, ".cub") == false)
	{
		perror("not a .cub file");
		exit(-1);
	}
	printf("%s\n", path_to_map);
	fd = open(path_to_map, O_RDONLY);
	if (fd == -1)
	{
		perror("cant open file\n");
		exit(EXIT_FAILURE);
	}
	textures = ft_calloc(1, sizeof(t_texture));
	char *line;
	line = get_next_row(fd);
	while (line != NULL)
	{
		printf("%s\n", line);
		line = get_next_row(fd);
	}

}

int main(int ac, char *av[])
{
	t_vars vars;
	t_data img;
	int x;
	int y;

	if (ac == 2)
	{
		parse_map(av[1]);
		vars.mlx = mlx_init();
		vars.mlx_win = mlx_new_window(vars.mlx, 1920, 1080, "hello");
		mlx_hook(vars.mlx_win, 2, 1L << 0, close_window, &vars);
		mlx_loop(vars.mlx);
		return (0);
	}
	printf("Wrong input\n");
	return (0);
}