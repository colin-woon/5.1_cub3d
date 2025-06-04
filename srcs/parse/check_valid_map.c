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

bool	check_above_wall(char **rows, int i, int j);
bool	check_wall_behind(char *row, int i);
bool	ft_iszero(char c);
bool	ft_isplayer(char c);
bool	ft_iswall(int c);

bool	check_horizontal_walls(t_map *map)
{
	int		i;
	int		j;
	char	**rows;
	char	*row;

	j = 0;
	rows = map->layout;
	while (j < map->height)
	{
		row = rows[j];
		i = 0;
		if (row[i] == '0')
		{
			msg("Hor: map is not closed\n");
			return (false);
		}
		while (row[i])
		{
			if (ft_isspace(row[i]))
			{
				if (check_wall_behind(row, i) == false)
					return (false);
				while (ft_isspace(row[i]))
					i++;
				if (row[i] == '\0')
					return (true);
				if (!ft_iswall(row[i]))
				{
					msg("Hor: map is not closed\n");
					return (false);
				}
				i++;
			}
			while (ft_iszero(row[i]) || ft_isplayer(row[i]))
				i++;
			if (!ft_iswall(row[i++]))
			{
				msg("Hor: map is not closed what the\n");
				return (false);
			}
		}
		j++;
	}
	return (true);
}

bool	check_vertical_walls(t_map	*map)
{
	int	i;
	int	j;
	char	**rows;
	int		len_col;

	j = 0;
	rows = map->layout;
	while (j < map->width)
	{
		i = 0;
		if (rows[i][j] == '0')
		{
			msg("Ver: map is not closed\n");
			return (false);
		}
		while (i < map->height)
		{
			if (ft_isspace(rows[i][j]))
			{
				check_above_wall(rows, i, j);
				while (ft_isspace(rows[i][j]) && i + 1 != map->height)
					i++;
				if (i + 1 >= map->height)
					break ;
				if (!ft_iswall(rows[i][j]))
				{
					msg("ver: map not closed\n");
					return (false);
				}
			}
			while (i + 1 < map->height && (ft_iszero(rows[i][j]) || ft_isplayer(rows[i][j])))
				i++;
			if (!ft_iswall(rows[i][j]) && i < map->height)
			{
				msg("ver: map not closed\n");
				return (false);
			}
			i++;
		}
		j++;
	}
	return (true);
}

char	*fill_str_sp(char *row, int row_width, int max_width)
{
	char *new_row;

	new_row = malloc(sizeof(char ) * max_width + 1);
	if (!new_row)
		error_msg_exit("Malloc Error filling space\n");
	int i = 0;
	while (i < row_width)
	{
		new_row[i] = row[i];
		i++;
	}
	while (max_width > row_width)
	{
		new_row[row_width] = ' ';
		row_width++;
	}
	new_row[max_width] = '\0';
	return new_row;
}

void	make_map_square(t_map *map)
{
	int	i;
	int	width;
	int	row_width;
	int	max_width;
	char **rows;

	i = 0;
	rows = map->layout;
	max_width = map->width;
	char *new_row;
	while (rows[i])
	{
		row_width = ft_strlen(rows[i]);
		if (row_width < max_width)
		{
			new_row = fill_str_sp(rows[i], row_width, max_width);
			free(rows[i]);
			rows[i] = new_row;
		}
		i++;
	}
}

int		ft_strlen_pro(char *line)
{
	int	str_len;

	if (ft_strlen(line) == 0)
		return 0;
	str_len = ft_strlen(line) - 1;
	while (str_len != 0 && !ft_iswall(line[str_len]))
		str_len--;
	return (str_len);
}

void	save_player(t_map *map, int y, int x, char dir)
{
	map->player_x = x;
	map->player_y = y;
	if (ft_strncmp(&dir, "N", 1) == 0)
		map->player_dir = NORTH;
	else if (ft_strncmp(&dir, "S", 1) == 0)
		map->player_dir = SOUTH;
	else if (ft_strncmp(&dir, "W", 1) == 0)
		map->player_dir = WEST;
	else if (ft_strncmp(&dir, "E", 1) == 0)
		map->player_dir = EAST;
}

static bool	check_invalid_char(t_map *map, t_game *game)
{
	int		i;
	int		j;
	char	**rows;
	char	*line;
	int		true_len;

	true_len = 0;
	rows = map->layout;
	j = 0;
	while (rows[j])
	{
		line = rows[j];
		i = 0;
		while (line[i])
		{
			while (ft_isspace(line[i]))
				i++;
			if (line[i] == '\0')
				break ;
			if (!ft_iswall(line[i]) && !ft_iszero(line[i]) && !ft_isplayer(line[i]))
			{
				msg("Invalid char in map\n");
				return (false);
			}
			i++;
		}
		true_len = ft_strlen_pro(line);
		if (true_len > map->width)
			map->width= true_len + 1;
		j++;
	}
	if (true_len == 0)
		return (error_msg("Map Is Not Surrounded By Walls\n"));
	return (true);
}

bool	check_valid_pos(t_map *map, int x, int y)
{
	if ((x - 1 < 0 || x >= map->width)
		|| (y - 1 < 0 || y >= map->height))
		return (error_msg("Invalid Player Pos\n"));
	return (true);
}

bool	check_player(t_map *map, t_game *game)
{
	int		i;
	int		j;
	bool	player_found;

	player_found = false;
	i = 0;
	while (map->layout[i])
	{
		j = 0;
		while (map->layout[i][j])
		{
			if (ft_isplayer(map->layout[i][j]) == true)
			{
				if (player_found == true)
				{
					msg("Multiple players found\n");
					return (false);
				}
				else
				{
					if (check_valid_pos(map, j, i) == false)
						return (false);
;					save_player(map, j, i, map->layout[i][j]);
					player_found = true;
				}
			}
			j++;
		}
		i++;
	}
	if (player_found == false)
		return (error_msg("Player not found\n"));
	return (true);
}

bool	check_valid_map(t_map *map, t_game *game)
{
	if (check_invalid_char(map, game) == false)
		return (false);
	if (check_player(map, game) == false)
		return (false);
	make_map_square(map);
	if (check_horizontal_walls(map) == false || check_vertical_walls(map) == false)
		return (false);
	return (true);
}
