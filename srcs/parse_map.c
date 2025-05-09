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

void	check_valid_map(t_map *map);

void	store_map(char *line, t_map *map, int map_height)
{
	char	**rows;
	int		i;

	i = 0;
	rows = malloc(sizeof(*rows) * (map_height + 2));
	if (!rows)
		error_msg("malloc error\n");
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

t_map	*parse_map(int fd, char *line, t_game *game)
{
	t_map	*map;
	int		map_height;
	int		map_width;

	map_height = 0;
	map = ft_calloc(1, sizeof(t_map));
	while (line != NULL)
	{
		store_map(line, map, map_height);
		map_height++;
		line = get_next_row(fd);
	}
	map->map_height = map_height;
	check_valid_map(map);
	return (map);
}
