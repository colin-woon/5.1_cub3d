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

bool	check_texture_complete(t_assets *assets)
{
	if (assets->textures[NORTH] == NULL
		|| assets->textures[SOUTH] == NULL
		|| assets->textures[EAST] == NULL
		|| assets->textures[WEST] == NULL)
	{
		msg("texture not complete\n");
		return (false);
	}
	return (true);
}

t_assets	*init_assets(void)
{
	t_assets	*assets;

	assets = ft_calloc(1, sizeof(t_assets));
	if (assets == NULL)
		error_msg_exit("Calloc Error:texture init\n");
	return (assets);
}

int *init_rgb(char *rgb_c);
void *make_img(char *str, t_game *game);

static bool compare_texture(char *line, t_assets *assets, t_game *game)
{
	if (is_empty_line(line))
		return (true);
	while (*line == '\t' || *line == ' ')
		line++;
	if (ft_strncmp(line, "NO", 2) == 0 && assets->textures[NORTH] == NULL)
		assets->textures[NORTH] = make_img(line, game);
	else if (ft_strncmp(line, "SO", 2) == 0 && assets->textures[SOUTH] == NULL)
		assets->textures[SOUTH] = make_img(line, game);
	else if (ft_strncmp(line, "WE", 2) == 0 && assets->textures[WEST] == NULL)
		assets->textures[WEST] = make_img(line, game);
	else if (ft_strncmp(line, "EA", 2) == 0 && assets->textures[EAST] == NULL)
		assets->textures[EAST] = make_img(line, game);
	else if (ft_strncmp(line, "F", 1) == 0 && assets->floor_rgb == NULL)
		assets->floor_rgb = init_rgb(line);
	else if (ft_strncmp(line, "C", 1) == 0 && assets->ceiling_rgb == NULL)
		assets->ceiling_rgb = init_rgb(line);
	else
	{
		msg("texture given incorrect\n");
		return (false);
	}
	return (true);
}

bool	parse_texture(char *line, t_game *game)
{
	if (!game->assets)
		game->assets = init_assets();
	return (compare_texture(line, game->assets, game));
}
