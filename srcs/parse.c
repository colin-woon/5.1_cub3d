/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:39:44 by rteoh             #+#    #+#             */
/*   Updated: 2025/05/28 21:18:49 by rteoh            ###   ########.fr       */
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

bool	check_texture_complete(t_assets *assets, char *line);

bool parse(char *path_to_cub, t_game *game)
{
	int 	fd;
	char	*line;

	if (ft_strend(path_to_cub, ".cub") == false)
		error_msg_exit("input given is not a .cub file");
	fd = open_file(path_to_cub);
	if (fd < 0)
		return (false);
	game->assets = init_assets();
	line = get_next_row(fd);
	while (line != NULL)
	{
		if (start_of_map(line))
		{
			if (check_texture_complete(game->assets, line) == false) //change here
				return (false);
			if (parse_map(fd, line, game) == false)
				return (false);
			return (true);
		}
		if (parse_texture(line, game) == false)
			return (false);
		free(line);
		line = get_next_row(fd);
	}
	if (game->map == NULL)
	{
		msg("map is missing\n");
		free(line);
		return (false);
	}
	return (true);
}
