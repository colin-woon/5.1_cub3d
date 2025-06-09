/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 23:27:16 by rteoh             #+#    #+#             */
/*   Updated: 2025/06/10 01:06:35 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_rgb(int	*rgb);

bool	check_rgb(int	*rgb)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (rgb[i] > 255 || rgb[i] < 0)
			return (error_msg("Invalid RGB\n"));
	}
	return (true);
}
