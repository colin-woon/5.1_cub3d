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
	// printf("tab count: %i", tab_count);
	if (tab_count == 0)
		return (line);
	res_line = malloc(sizeof(char) * ((tab_count * 4) + ft_strlen(line)) + 1);
	if (!res_line)
		error_msg("Malloc error\n");
	i = 0;
	int	tab_track = 0;
	while (line[i])
	{
		if (line[i] == '\t')
		{
			j = 0;
			while (j < 4)
				res_line[i + j++] = ' ';
			tab_track++;
		}
		res_line[i + (4 * tab_track)] = line[i + tab_track];
		i++;
	}
	res_line[i + (4 * tab_track)] = '\0';
	free(line);
	return (res_line);
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
		line = conv_tab(line);
		store_map(line, map, map_height);
		map_height++;
		line = get_next_row(fd);
	}
	map->map_height = map_height;
	check_valid_map(map);
	return (map);
}
