/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:58:23 by rteoh             #+#    #+#             */
/*   Updated: 2025/06/09 21:14:07 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*fill_str_sp(char *row, int row_width, int max_width, t_game *game);
int		ft_strlen_pro(char *line);
void	save_player(t_map *map, int y, int x, char dir);

char	*fill_str_sp(char *row, int row_width, int max_width, t_game *game)
{
	char	*new_row;
	int		i;

	new_row = malloc(sizeof(char ) * max_width + 1);
	if (!new_row)
		error_msg_exit("Malloc Error filling space\n", game);
	i = 0;
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
	return (new_row);
}

int	ft_strlen_pro(char *line)
{
	int	str_len;

	if (ft_strlen(line) == 0)
		return (0);
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
