/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:10:13 by rteoh             #+#    #+#             */
/*   Updated: 2025/05/30 13:39:02 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_map_grid(t_map *map);

char	*get_next_row(int fd)
{
	char	*line;
	char	*res_line;

	line = get_next_line(fd);
	res_line = ft_strtrim(line, "\n");
	free(line);
	return (res_line);
}

bool ft_strend(char *s, char *suffix)
{
	size_t s_len;
	size_t suffix_len;

	s_len = ft_strlen(s);
	suffix_len = ft_strlen(suffix);

	if (suffix_len > s_len)
		return false;
	while (suffix_len > 0)
	{
		if (s[s_len--] != suffix[suffix_len--])
			return (false);
	}
	return true;
}

int	open_file(char *path_to_file)
{
	int	fd;
	fd = open(path_to_file, O_RDONLY);
	if (fd == -1)
		error_msg("file not found or cant be open");
	return (fd);
}

void	get_map_grid(t_map *map)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	map->grid = malloc(map->height * sizeof(int*));
	while (i < map->height)
	{
		map->grid[i] = malloc(map->width * sizeof(int));
		i++;
	}
	x = -1;
	while(++x < map->height)
	{
		y = -1;
		while (++y < map->width)
		{
			if (ft_isspace(map->layout[x][y]))
				map->grid[x][y] = -1;
			else if (!ft_strncmp(&map->layout[x][y], "1", 1))
				map->grid[x][y] = 1;
			else
				map->grid[x][y] = 0;
		}
	}
}
