/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:29:31 by rteoh             #+#    #+#             */
/*   Updated: 2025/05/07 09:29:31 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_wall_behind(char *row, int i);
bool	check_above_wall(char **rows, int i, int j);
bool	ft_iszero(char c);
bool	ft_isplayer(char c);
bool	ft_iswall(int c);

bool	ft_iswall(int c)
{
	if (c == '1')
		return (true);
	return (false);
}

bool	ft_isplayer(char c)
{
	if (c == 'W' || c == 'E' || c == 'N' || c == 'S')
		return (true);
	return (false);
}

bool	ft_iszero(char c)
{
	if (c == '0')
		return (true);
	return (false);
}

bool	check_wall_behind(char *row, int i)
{
	if (i == 0)
		return (true);
	if (!ft_iswall(row[i - 1]))
	{
		msg("map is not closed\n");
		return (false);
	}
	return (true);
}

bool	check_above_wall(char **rows, int i, int j)
{
	if (i == 0)
		return (true);
	if (!ft_iswall(rows[--i][j]))
	{
		msg("map is not closed\n");
		return (false);
	}
	return (true);
}
