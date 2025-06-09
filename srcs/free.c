/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 16:01:59 by cwoon             #+#    #+#             */
/*   Updated: 2025/06/10 01:06:49 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup(t_game *game);
void	free_assets(t_game *game, t_assets *assets);
void	free_mlx(t_mlx *mlx_data);
void	free_map(t_map *map);

void	free_assets(t_game *game, t_assets *assets)
{
	if (game->assets->floor_rgb)
		free(game->assets->floor_rgb);
	if (game->assets->ceiling_rgb)
		free(game->assets->ceiling_rgb);
	if (game->assets->textures[NORTH].ptr)
		mlx_destroy_image(game->mlx_data->ptr, assets->textures[NORTH].ptr);
	if (game->assets->textures[SOUTH].ptr)
		mlx_destroy_image(game->mlx_data->ptr, assets->textures[SOUTH].ptr);
	if (game->assets->textures[EAST].ptr)
		mlx_destroy_image(game->mlx_data->ptr, assets->textures[EAST].ptr);
	if (game->assets->textures[WEST].ptr)
		mlx_destroy_image(game->mlx_data->ptr, assets->textures[WEST].ptr);
	free(game->assets);
}

void	free_mlx(t_mlx *mlx_data)
{
	mlx_destroy_image(mlx_data->ptr, mlx_data->img->ptr);
	mlx_destroy_window(mlx_data->ptr, mlx_data->window);
	mlx_destroy_display(mlx_data->ptr);
	free(mlx_data->ptr);
	free(mlx_data->img);
	free(mlx_data);
}

void	free_map(t_map *map)
{
	if (map->grid)
		ft_free_int_matrix(map->grid, map->height + 1);
	if (map->layout)
		ft_free_2d_array(map->layout);
	free(map);
}

void	cleanup(t_game *game)
{
	printf("in cleanup\n");
	if (game->ray)
		free(game->ray);
	if (game->player)
		free(game->player);
	if (game->map)
		free_map(game->map);
	if (game->assets)
		free_assets(game, game->assets);
	if (game->mlx_data)
		free_mlx(game->mlx_data);
}
