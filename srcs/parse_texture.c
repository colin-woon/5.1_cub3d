/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:46:51 by rteoh             #+#    #+#             */
/*   Updated: 2025/05/07 09:46:51 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != '\t' || *line != ' ' || *line != '\n')
			return false;
		line++;
	}
	return true;
}

bool	check_texture_complete(t_texture *textures)
{
	if (textures->no_img_ptr == NULL
		|| textures->ea_img_ptr == NULL
		|| textures->we_img_ptr == NULL
		|| textures->so_img_ptr == NULL)
	{
		msg("texture not complete\n");
		return (false);
	}
	return (true);
}

t_texture	*init_textures(void)
{
	t_texture	*textures;

	textures = ft_calloc(1, sizeof(t_texture));
	if (textures == NULL)
		error_msg_exit("Calloc Error:texture init\n");
	return (textures);
}

int *init_rgb(char *rgb_c);
void *make_img(char *str, t_game *game);

t_img	*get_addr(void *img_ptr)
{
	t_img	*img_info;

	img_info = ft_calloc(1, sizeof(t_img));
	if (img_info == NULL)
		error_msg_exit("Calloc Error:get_addr\n");
	img_info->address = mlx_get_data_addr(img_ptr,
					&img_info->bits_per_pixel,
					&img_info->line_length,
					&img_info->endian);
	return (img_info);

}

static bool compare_texture(char *line, t_texture *textures, t_game *game)
{
	if (is_empty_line(line))
		return (true);
	while (*line == '\t' || *line == ' ')
		line++;
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		textures->no_img_ptr = make_img(line, game);
		textures->no_img_info = get_addr(textures->no_img_ptr);
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		textures->so_img_ptr = make_img(line, game);
		textures->so_img_info = get_addr(textures->so_img_ptr);
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		textures->we_img_ptr = make_img(line, game);
		textures->we_img_info = get_addr(textures->we_img_ptr);
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		textures->ea_img_ptr = make_img(line, game);
		textures->ea_img_info = get_addr(textures->ea_img_ptr);
	}
	else if (ft_strncmp(line, "F", 1) == 0)
		textures->floor_rgb = init_rgb(line);
	else if (ft_strncmp(line, "C", 1) == 0)
		textures->ceiling_rgb = init_rgb(line);
	else
		return (false);
	return (true);
}

bool	parse_texture(char *line, t_game *game)
{
	if (!game->textures)
		game->textures = init_textures();
	return (compare_texture(line, game->textures, game));
}
