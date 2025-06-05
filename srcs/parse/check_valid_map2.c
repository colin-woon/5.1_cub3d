/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:15:09 by rteoh             #+#    #+#             */
/*   Updated: 2025/06/05 19:54:55 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_horizontal_blocks(char **blocks)
{
	int		i;
	int		len;
	char	*block;

	i = 0;
	while (blocks[i])
	{
		block = blocks[i];
		if (block[0] != '1')
			return (false);
		len = ft_strlen(block);
		if (block[len - 1] != '1')
			return (false);
		i++;
	}
	return (true);
}

void	free_blocks(char **blocks)
{
	int	i;

	i = -1;
	while (blocks[++i])
		free(blocks[i]);
	free(blocks);
}

bool	check_horizontal_walls(t_map *map)
{
	int		i;
	int		j;
	char	**rows;
	char	**blocks;

	i = -1;
	rows = map->layout;
	while (++i < map->height)
	{
		blocks = ft_split(rows[i], ' ');
		if (check_horizontal_blocks(blocks) == false)
		{
			free_blocks(blocks);
			return (error_msg("Hor: map not closed\n"));
		}
		free_blocks(blocks);
	}
	return (true);
}

static char	*make_string(t_map *map, int col)
{
	char	*res_str;
	char	**map_layout;
	int		i;

	i = map->height;
	map_layout = map->layout;
	res_str = malloc(sizeof(char) * i + 1);
	if (!res_str)
		return (NULL);
	res_str[i] = '\0';
	while (--i >= 0)
		res_str[i] = map_layout[i][col];
	return (res_str);
}

bool	check_vertical_walls(t_map	*map)
{
	int		i;
	char	**rows;
	char	*tmp;
	char	**blocks;

	i = 0;
	rows = map->layout;
	while (i < map->width)
	{
		tmp = make_string(map, i);
		blocks = ft_split(tmp, ' ');
		free(tmp);
		if (check_horizontal_blocks(blocks) == false)
		{
			free_blocks(blocks);
			return (error_msg("Ver: map not closed\n"));
		}
		free_blocks(blocks);
		i++;
	}
	return (true);
}
