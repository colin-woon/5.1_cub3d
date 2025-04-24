/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <ryan42cmp@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 06:57:25 by rteoh             #+#    #+#             */
/*   Updated: 2025/04/24 16:24:16 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int close_window(int keycode, t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_win);
	exit(0);
}

//goal is to get the textures and the floor colour
//something like what i did, was to put it into a struct

void	compare_texture(char *line, t_texture *textures, t_game *game)
{
	int	img_width;
	int	img_height;
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		textures->n_tex_file = ft_strchr(line, '.');
		textures->n_tex_img = mlx_xpm_file_to_image(game->mlx, textures->n_tex_file, &img_height, &img_width);
		// mlx_put_image_to_window(game->mlx, game->mlx_win, textures->n_tex_img, 0, 500);
	}
	if (ft_strncmp(line, "SO", 2) == 0)
	{
		textures->s_tex_file = ft_strchr(line, '.');
		textures->s_tex_img = mlx_xpm_file_to_image(game->mlx, textures->s_tex_file, &img_height, &img_width);
	}
	if (ft_strncmp(line, "WE", 2) == 0)
	{
		textures->w_tex_file = ft_strchr(line, '.');
		textures->s_tex_img = mlx_xpm_file_to_image(game->mlx, textures->w_tex_file, &img_height, &img_width);
	}
	if (ft_strncmp(line, "EA", 2) == 0)
	{
		textures->e_tex_file = ft_strchr(line, '.');
		textures->s_tex_img = mlx_xpm_file_to_image(game->mlx, textures->e_tex_file, &img_height, &img_width);
	}

	return ;
}

void parse_map(char *path_to_map, t_game *game)
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
		compare_texture(line, textures, game);
		free(line);
		line = get_next_row(fd);
	}
	if (textures->n_tex_img)
		mlx_destroy_image(game->mlx, textures->n_tex_img);
	free(textures);
}

int main(int ac, char *av[])
{
	t_game game;
	int x;
	int y;

	if (ac == 2)
	{
		game.mlx = mlx_init();
		parse_map(av[1], &game);
		game.mlx_win = mlx_new_window(game.mlx, 1920, 1080, "hello");
		mlx_hook(game.mlx_win, 2, 1L << 0, close_window, &game);
		mlx_loop(game.mlx);
		return (0);
	}
	printf("Wrong input\n");
	return (0);
}