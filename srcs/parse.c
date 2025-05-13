/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:39:44 by rteoh             #+#    #+#             */
/*   Updated: 2025/05/13 11:20:20 by rteoh            ###   ########.fr       */
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

void	check_texture_complete(t_texture *textures);

void parse(char *path_to_cub, t_game *game)
{
	int 	fd;
	char	*line;

	if (ft_strend(path_to_cub, ".cub") == false)
		msg("input given is not a .cub file");
	fd = open_file(path_to_cub);
	if (fd < 0)
		error_msg("File cannot be opened");
	line = get_next_row(fd);
	while (line != NULL)
	{
		if (start_of_map(line))
			break;
		parse_texture(line, game);
		printf("%s\n", line);
		free(line);
		line = get_next_row(fd);
	}
	// check_texture_complete(game->textures);
	game->map = parse_map(fd, line, game);
}
