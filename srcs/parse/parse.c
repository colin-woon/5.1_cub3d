/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:39:44 by rteoh             #+#    #+#             */
/*   Updated: 2025/06/09 21:18:22 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool		parse(char *path_to_cub, t_game *game);
static bool	start_of_map(char *line);

static bool	start_of_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_isdigit(line[i]))
		return (true);
	return (false);
}

bool	parse(char *path_to_cub, t_game *game)
{
	int		fd;
	char	*line;

	if (ft_strend(path_to_cub, ".cub") == false)
		error_msg_exit("input given is not a .cub file\n", game);
	fd = open_file(path_to_cub);
	if (fd < 0)
		return (false);
	game->assets = init_assets(game);
	line = get_next_row(fd);
	while (line != NULL && !start_of_map(line))
	{
		if (parse_texture(line, game) == false)
		{
			free(line);
			return (false);
		}
		free(line);
		line = get_next_row(fd);
	}
	if (check_texture_complete(game->assets) == false)
	{
		printf("helo\n");
		free(line);
		return (false);
	}
	if (parse_map(fd, line, game) == false)
		return (false);
	return (true);
}
