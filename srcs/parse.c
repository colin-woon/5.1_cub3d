/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <ryan42cmp@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:39:44 by rteoh             #+#    #+#             */
/*   Updated: 2025/04/24 17:56:04 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


//goal is to get the textures and the floor colour
//something like what i did, was to put it into a struct


//next step is to check that it is in a strict format of no so we ea f c
//plan to use 

static void	compare_texture(char *line, t_texture *textures, t_game *game)
{
	int	img_width;
	int	img_height;
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		textures->n_tex_file = ft_strchr(line, '.');
		textures->n_tex_img = mlx_xpm_file_to_image(game->mlx, textures->n_tex_file, &img_height, &img_width);
		mlx_put_image_to_window(game->mlx, game->mlx_win, textures->n_tex_img, 0, 0);
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



void parse_map(char *path_to_cub, t_game *game)
{
	int fd;
	char *line;
	t_texture	*textures;

	if (ft_strend(path_to_cub, ".cub") == false)
		msg("input given is not a .cub file");
	fd = open_file(path_to_cub);
	textures = ft_calloc(1, sizeof(t_texture));

	line = get_next_row(fd);
	while (line != NULL)
	{
		compare_texture(line, textures, game);
		free(line);
		line = get_next_row(fd);
	}
	if (textures->n_tex_img)
		mlx_destroy_image(game->mlx, textures->n_tex_img);
	free(textures);
}