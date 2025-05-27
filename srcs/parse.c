/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:39:44 by rteoh             #+#    #+#             */
/*   Updated: 2025/05/27 22:04:03 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool start_of_map(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_isdigit(line[i]))
		return true;
	return false;
}

bool	check_texture_complete(t_assets *assets);

bool parse(char *path_to_cub, t_game *game)
{
	int 	fd;
	char	*line;

	if (ft_strend(path_to_cub, ".cub") == false)
		return(error_msg("input given is not a .cub file"));
	fd = open_file(path_to_cub);
	if (fd < 0)
		return (false);
	game->assets = init_assets();
	line = get_next_row(fd);
	while (line != NULL)
	{
		if (start_of_map(line))
			break;
		if (parse_texture(line, game) == false) //change here
		{
			free(line);
			return (false);
		}
		free(line);
		line = get_next_row(fd);
	}
	if (check_texture_complete(game->assets) == false) //change here
	{
		free(line);
		return (false);
	}
	if (parse_map(fd, line, game) == false)
		return (false);
	return (true);
}
