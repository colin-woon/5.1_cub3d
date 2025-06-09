/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:01:59 by cwoon             #+#    #+#             */
/*   Updated: 2025/06/09 18:32:24 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup(t_game *game);

void	cleanup(t_game *game)
{
	printf("in cleanup\n");
	if (game->ray)
		free(game->ray);
	if (game->player)
		free(game->player);
	if (game->map)
	{
		if (game->map->grid)
			ft_free_int_matrix(game->map->grid, game->map->height + 1);
		if (game->map->layout)
			ft_free_2d_array(game->map->layout);
		free(game->map);
	}
	if (game->assets)
	{
		if (game->assets->floor_rgb)
			free(game->assets->floor_rgb);
		if (game->assets->ceiling_rgb)
			free(game->assets->ceiling_rgb);
		if (game->assets->textures[NORTH].ptr)
			mlx_destroy_image(game->mlx_data->ptr, game->assets->textures[NORTH].ptr);
		if (game->assets->textures[SOUTH].ptr)
			mlx_destroy_image(game->mlx_data->ptr, game->assets->textures[SOUTH].ptr);
		if (game->assets->textures[EAST].ptr)
			mlx_destroy_image(game->mlx_data->ptr, game->assets->textures[EAST].ptr);
		if (game->assets->textures[WEST].ptr)
			mlx_destroy_image(game->mlx_data->ptr, game->assets->textures[WEST].ptr);
		free(game->assets);
	}
	if (game->mlx_data)
	{
		mlx_destroy_image(game->mlx_data->ptr, game->mlx_data->img->ptr);
			mlx_destroy_window(game->mlx_data->ptr, game->mlx_data->window);
		mlx_destroy_display(game->mlx_data->ptr);
		free(game->mlx_data->ptr);
		free(game->mlx_data->img);
		free(game->mlx_data);
	}
}
