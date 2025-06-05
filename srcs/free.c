/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:17:55 by rteoh             #+#    #+#             */
/*   Updated: 2025/05/13 18:17:55 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_rgb(int *rgb)
{
	if (rgb)
		free(rgb);
}

void	free_texture(t_assets *assets)
{
	free_rgb(assets->ceiling_rgb);
	free_rgb(assets->floor_rgb);
}
