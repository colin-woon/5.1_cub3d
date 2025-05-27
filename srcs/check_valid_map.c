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
	int	i;
	int	j;
	char **rows;
	char *row;


	j = 0;
	rows = map->map_layout;
	while (j < map->map_height)
	{
		row = rows[j];
		i = 0;
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
			if (!ft_iswall(row[i++]) && row[i] != '\0')
			{
				msg("Hor: map is not closed\n");
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
	rows = map->map_layout;
	while (j < map->map_width)
	{
		i = 0;
		while (i < map->map_height)
		{
			if (ft_isspace(rows[i][j]))
			{
				check_above_wall(rows, i, j);
				while (ft_isspace(rows[i][j]) && i + 1 != map->map_height)
					i++;
				if (i + 1 >= map->map_height)
					break ;
				if (!ft_iswall(rows[i][j]))
				{
					msg("ver: map not closed\n");
					return (false);
				}
			}
			while (ft_iszero(rows[i][j]) || ft_isplayer(rows[i][j]))
				i++;
			if (!ft_iswall(rows[i][j]) && i < map->map_height)
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
	rows = map->map_layout;
	max_width = map->map_width;
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
	while (!ft_iswall(line[str_len]))
		str_len--;
	return (str_len);
}

void	save_player_dir(t_map *map, int x, int y, char dir)
{
	map->player_x = x;
	map->player_y = y;
	if (ft_strncmp(dir, "N", 1) == 0)
		map->player_dir = NORTH;
	else if (ft_strncmp(dir, "S", 1) == 0)
		map->player_dir = SOUTH;
	else if (ft_strncmp(dir, "W", 1) == 0)
		map->player_dir = WEST;
	else if (ft_strncmp(dir, "E", 1) == 0)
		map->player_dir = EAST;
}

static bool	check_invalid_char(t_map *map, t_game *game)
{
	int		i;
	int		j;
	char	**rows;
	char	*line;
	int		true_len;
	bool	player_found;

	true_len = 0;
	player_found = false;
	rows = map->map_layout;
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
				return (true);
			}
			if (ft_isplayer(line[i]))
			{
				if (player_found == true)
				{
					msg("Multiple players found\n");
					return (true);
				}
				save_player(map, i, j, line[i]);
				player_found = true;
			}
			i++;
		}
		true_len = ft_strlen_pro(line);
		if (true_len > map->map_width)
			map->map_width = true_len + 1;
		j++;
	}
	return (false);
}

bool	check_valid_map(t_map *map, t_game *game)
{
	if (check_invalid_char(map, game) == true)
		return (false);
	make_map_square(map);
	if (check_horizontal_walls(map) == false || check_vertical_walls(map) == false)
		return (false);
	return (true);
}
