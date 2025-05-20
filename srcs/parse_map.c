/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:23:15 by rteoh             #+#    #+#             */
/*   Updated: 2025/05/07 09:23:15 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_valid_map(t_map *map);

void	store_map(char *line, t_map *map, int map_height)
{
	char	**rows;
	int		i;

	i = 0;
	rows = malloc(sizeof(*rows) * (map_height + 2));
	if (!rows)
		error_msg_exit("Malloc Error:store map\n");
	while (i < map_height)
	{
		rows[i] = map->map_layout[i];
		i++;
	}
	rows[i] = line;
	rows[i + 1] = NULL;
	free(map->map_layout);
	map->map_layout = rows;
}


char	*conv_tab(char *line)
{
	char	*res_line;
	int		i;
	int		tab_count;
	int		j;

	tab_count = 0;
	if (!line)
		return NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			tab_count++;
		i++;
	}
	if (tab_count == 0)
		return (line);
	res_line = malloc(sizeof(char) * ((tab_count * 4) + ft_strlen(line)) + 1);
	if (!res_line)
		error_msg_exit("Malloc Error:conv tab\n");
	i = 0;
	int	tab_track;
	while (line[i])
	{
		while (line[i] == '\t')
		{
			tab_track = 0;
			while (tab_track < 4)
			{
				res_line[j++] = ' ';
				tab_track++;
			}
			i++;
		}
		res_line[j++] = line[i++];
	}
	res_line[j] = '\0';
	free(line);
	return (res_line);
}

bool	*parse_map(int fd, char *line, t_game *game)
{
	t_map	*map;
	int		map_height;
	int		map_width;

	map_height = 0;
	game->map = ft_calloc(1, sizeof(t_map));
	while (line != NULL)
	{
		line = conv_tab(line);
		store_map(line, game->map, map_height);
		map_height++;
		line = get_next_row(fd);
	}
	game->map->map_height = map_height;
	if (check_valid_map(game->map) == false)
		return (false);
	return (true);
}
