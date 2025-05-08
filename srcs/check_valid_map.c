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

void	check_above_wall(char **rows, int i, int j);
void	check_wall_behind(char *row, int i);
bool	ft_iszero(char c);
bool	ft_isplayer(char c);
bool	ft_iswall(int c);

void	check_horizontal_walls(t_map *map)
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
				check_wall_behind(row, i);
				while (ft_isspace(row[i]))
					i++;
				if (row[i] == '\0')
					return ;
				if (!ft_iswall(row[i]))
					msg("hor: map is not closed\n");
				i++;
			}
			while (ft_iszero(row[i]) || ft_isplayer(row[i]))
				i++;
			if (!ft_iswall(row[i++]) && row[i] != '\0')
				msg("hor : map is not closed\n");
		}
		j++;
	}
}

void	check_vertical_walls(t_map	*map)
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
					msg("ver: map not closed\n");
			}
			while (ft_iszero(rows[i][j]) || ft_isplayer(rows[i][j]))
				i++;
			if (!ft_iswall(rows[i][j]) && i < map->map_height)
				msg("ver ; map not closed\n");
			i++;
		}
		j++;
	}
}

char	*fill_str_sp(char *row, int row_width, int max_width)
{
	char *new_row;

	new_row = malloc(sizeof(char ) * max_width + 1);
	if (!new_row)
		error_msg("Malloc error\n");
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

void	check_valid_map(t_map *map)
{
	make_map_square(map);
	check_horizontal_walls(map);
	check_vertical_walls(map);
}
