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

bool		check_texture_complete(t_assets *assets);
t_assets	*init_assets(t_game *game);
bool		parse_texture(char *line, t_game *game);
static bool	is_empty_line(char *line);
static bool	compare_texture(char *line, t_assets *assets, t_game *game);

static bool	is_empty_line(char *line)
{
	while (*line == '\t' || *line == ' ')
		line++;
	if (*line == '\0')
		return (true);
	return (false);
}

bool	check_texture_complete(t_assets *assets)
{
	if (assets->textures[NORTH].ptr == NULL
		|| assets->textures[SOUTH].ptr == NULL
		|| assets->textures[EAST].ptr == NULL
		|| assets->textures[WEST].ptr == NULL)
	{
		msg("texture not complete\n");
		return (false);
	}
	if (assets->ceiling_rgb == NULL || assets->floor_rgb == NULL)
	{
		msg("RGB not complete\n");
		return (false);
	}
	return (true);
}

t_assets	*init_assets(t_game *game)
{
	t_assets	*assets;
	int			i;

	i = 0;
	assets = ft_calloc(1, sizeof(t_assets));
	if (assets == NULL)
		error_msg_exit("Calloc Error:texture init\n", game);
	assets->ceiling_rgb = NULL;
	assets->floor_rgb = NULL;
	while (i < 4)
		assets->textures[i++].ptr = NULL;
	return (assets);
}

static bool	compare_texture(char *line, t_assets *assets, t_game *game)
{
	if (is_empty_line(line))
		return (true);
	while (*line == '\t' || *line == ' ')
		line++;
	if (ft_strncmp(line, "NO", 2) == 0 && assets->textures[NORTH].ptr == NULL)
		make_img(line, game, &assets->textures[NORTH]);
	else if (ft_strncmp(line, "SO", 2) == 0
		&& assets->textures[SOUTH].ptr == NULL)
		make_img(line, game, &assets->textures[SOUTH]);
	else if (ft_strncmp(line, "WE", 2) == 0
		&& assets->textures[WEST].ptr == NULL)
		make_img(line, game, &assets->textures[WEST]);
	else if (ft_strncmp(line, "EA", 2) == 0
		&& assets->textures[EAST].ptr == NULL)
		make_img(line, game, &assets->textures[EAST]);
	else if (ft_strncmp(line, "F", 1) == 0 && assets->floor_rgb == NULL)
		return (init_rgb(line, &assets->floor_rgb, game));
	else if (ft_strncmp(line, "C", 1) == 0 && assets->ceiling_rgb == NULL)
		return (init_rgb(line, &assets->ceiling_rgb, game));
	else
	{
		free(line);
		return (error_msg("texture given incorrect\n"));
	}
	return (true);
}

bool	parse_texture(char *line, t_game *game)
{
	if (compare_texture(line, game->assets, game) == true)
		return (true);
	free(line);
	return (false);
}
