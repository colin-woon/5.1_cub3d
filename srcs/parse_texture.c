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

bool	check_texture_complete(t_textures *textures)
{
	if (textures->imgs[NORTH] == NULL
		|| textures->imgs[SOUTH] == NULL
		|| textures->imgs[EAST] == NULL
		|| textures->imgs[WEST] == NULL)
	{
		msg("texture not complete\n");
		return (false);
	}
	return (true);
}

t_textures	*init_textures(void)
{
	t_textures	*textures;

	textures = ft_calloc(1, sizeof(t_textures));
	if (textures == NULL)
		error_msg_exit("Calloc Error:texture init\n");
	return (textures);
}

int *init_rgb(char *rgb_c);
void *make_img(char *str, t_game *game);

static bool compare_texture(char *line, t_textures *textures, t_game *game)
{
	if (is_empty_line(line))
		return (true);
	while (*line == '\t' || *line == ' ')
		line++;
	if (ft_strncmp(line, "NO", 2) == 0)
		textures->imgs[NORTH] = make_img(line, game);
	else if (ft_strncmp(line, "SO", 2) == 0)
		textures->imgs[SOUTH] = make_img(line, game);
	else if (ft_strncmp(line, "WE", 2) == 0)
		textures->imgs[WEST] = make_img(line, game);
	else if (ft_strncmp(line, "EA", 2) == 0)
		textures->imgs[EAST] = make_img(line, game);
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
