/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:15:09 by rteoh             #+#    #+#             */
/*   Updated: 2025/06/05 18:52:15 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	check_horizontal_block(char *block)
{
	int	i;
	int	len;

	i = 0;
	if (block[i] != '1')
		return (false);
	len = ft_strlen(block);
	if (block[len - 1] != '1')
		return (false);
	return (true);
}

static void	free_blocks(char **blocks)
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
		j = -1;
		blocks = ft_split(rows[i], ' ');
		while (blocks[++j])
		{
			if (check_horizontal_block(blocks[j]) == false)
			{
				free_blocks(blocks);
				return (error_msg("hor: map is not closed\n"));
			}
		}
		free_blocks(blocks);
	}
	return (true);
}