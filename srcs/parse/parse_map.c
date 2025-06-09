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

static int	count_tab(char *line);
static char	*make_sp_tb(char *line, int tab_count, t_game *game);
void		store_map(char *line, t_map *map, int map_height, t_game *game);
char		*conv_tab(char *line, t_game *game);
bool		parse_map(int fd, char *line, t_game *game);

void	store_map(char *line, t_map *map, int map_height, t_game *game)
{
	char	**rows;
	int		i;

	i = 0;
	rows = malloc(sizeof(*rows) * (map_height + 2));
	if (!rows)
		error_msg_exit("Malloc Error:store map\n", game);
	while (i < map_height)
	{
		rows[i] = map->layout[i];
		i++;
	}
	rows[i] = ft_strdup(line);
	rows[i + 1] = NULL;
	free(map->layout);
	map->layout = rows;
}

static int	count_tab(char *line)
{
	int	i;
	int	tab_count;

	i = 0;
	tab_count = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			tab_count++;
		i++;
	}
	return (tab_count);
}

static char	*make_sp_tb(char *line, int tab_count, t_game *game)

{
	int		i;
	int		j;
	int		tab_track;
	char	*res_line;

	res_line = malloc(sizeof(char) * ((tab_count * 4) + ft_strlen(line)));
	if (!res_line)
		error_msg_exit("Malloc Error:conv tab\n", game);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\t')
		{
			tab_track = 0;
			while (tab_track++ < 4)
				res_line[j++] = ' ';
			i++;
			continue ;
		}
		res_line[j++] = line[i++];
	}
	res_line[j] = '\0';
	return (res_line);
}

char	*conv_tab(char *line, t_game *game)
{
	char	*res_line;
	int		i;
	int		tab_count;

	if (!line)
		return (NULL);
	i = 0;
	tab_count = count_tab(line);
	if (tab_count == 0)
		return (line);
	res_line = make_sp_tb(line, tab_count, game);
	free(line);
	return (res_line);
}

bool	parse_map(int fd, char *line, t_game *game)
{
	t_map	*map;
	int		map_height;
	int		map_width;

	map_height = 0;
	if (line == NULL)
		return (error_msg("Map is missing\n"));
	game->map = ft_calloc(1, sizeof(t_map));
	while (line != NULL)
	{
		line = conv_tab(line, game);
		store_map(line, game->map, map_height, game);
		map_height++;
		free(line);
		line = get_next_row(fd);
	}
	game->map->height = map_height;
	free(line);
	if (check_valid_map(game->map, game) == false)
		return (false);
	return (true);
}
