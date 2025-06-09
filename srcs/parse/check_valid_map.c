/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:28:43 by rteoh             #+#    #+#             */
/*   Updated: 2025/05/07 09:28:43 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		make_map_square(t_map *map);
bool		check_valid_map(t_map *map, t_game *game);
bool		get_map_width(t_map *map);
bool		check_player(t_map *map);
static bool	check_invalid_char(t_map *map, t_game *game);

void	make_map_square(t_map *map)
{
	char	*new_row;
	char	**rows;
	int		i;
	int		row_width;

	i = 0;
	rows = map->layout;
	while (rows[i])
	{
		row_width = ft_strlen(rows[i]);
		if (row_width < map->width)
		{
			new_row = fill_str_sp(rows[i], row_width, map->width);
			free(rows[i]);
			rows[i] = new_row;
		}
		i++;
	}
}

static bool	check_invalid_char(t_map *map, t_game *game)
{
	int		i;
	int		j;
	char	**rows;
	char	*line;

	rows = map->layout;
	j = -1;
	while (rows[++j])
	{
		line = rows[j];
		i = -1;
		while (line[++i])
		{
			while (line[i] && ft_isspace(line[i]))
				i++;
			if (line[i] && !ft_iswall(line[i])
				&& !ft_iszero(line[i]) && !ft_isplayer(line[i]))
				return (error_msg("Invalid char in map\n"));
		}
	}
	return (true);
}

bool	check_player(t_map *map)
{
	int		i;
	int		j;
	bool	player_found;

	player_found = false;
	i = -1;
	while (map->layout[++i])
	{
		j = -1;
		while (map->layout[i][++j])
		{
			if (ft_isplayer(map->layout[i][j]) == true)
			{
				if (player_found == true)
					return (error_msg("Multiple players found\n"));
				save_player(map, j, i, map->layout[i][j]);
				player_found = true;
			}
		}
	}
	if (player_found == false)
		return (error_msg("Player not found\n"));
	return (true);
}

bool	get_map_width(t_map *map)
{
	int		true_len;
	char	**rows;
	char	*line;
	int		i;

	true_len = 0;
	rows = map->layout;
	i = -1;
	while (rows[++i])
	{
		line = rows[i];
		true_len = ft_strlen_pro(line);
		if (true_len > map->width)
			map->width = true_len + 1;
	}
	if (true_len == 0)
		return (error_msg("Map Is Not Surrounded By Walls\n"));
	return (true);
}

bool	check_valid_map(t_map *map, t_game *game)
{
	if (check_invalid_char(map, game) == false)
		return (false);
	if (get_map_width(map) == false)
		return (false);
	if (check_player(map) == false)
		return (false);
	make_map_square(map);
	if (check_horizontal_walls(map) == false
		|| check_vertical_walls(map) == false)
		return (false);
	return (true);
}
