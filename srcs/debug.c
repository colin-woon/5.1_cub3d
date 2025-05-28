/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:22:21 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/29 00:51:49 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int debug_event(int keycode, t_mlx *mlx);

int debug_event(int keycode, t_mlx *mlx)
{
	// printf("DEBUG: event\n");
	return (0);
}

void	DEBUG_init_map(t_game *game)
{
	int		debug_map[24][24] =
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	// int		debug_map[DEBUG_MAP_HEIGHT][DEBUG_MAP_WIDTH] =
	// {
	// 	{1,1,1,1,1},
	// 	{1,0,1,0,1},
	// 	{1,0,0,0,1},
	// 	{1,0,0,0,1},
	// 	{1,1,1,1,1},
	// };
	memcpy(game->debug_map, debug_map, sizeof(debug_map));
}

// void DEBUG_print_map_assets(t_game *game)
// {
//     if (!game)
//     {
//         printf("DEBUG: Game pointer is NULL.\n");
//         return;
//     }
//     printf("\n--- Debug Map Layout (from game->map->layout) ---\n");
//     if (game->map && game->map->layout && game->map->height > 0)
//     {
//         printf("Map Dimensions: Width=%d, Height=%d\n", game->map->width, game->map->height);
//         for (int i = 0; i < game->map->height; i++)
//         {
//             if (game->map->layout[i])
//             {
//                 printf("[%2d]: %s\n", i, game->map->layout[i]);
//             }
//             else
//             {
//                 printf("[%2d]: (NULL row)\n", i);
//             }
//         }
//     }
//     else if (game->map && game->map->height <= 0)
//     {
//          printf("Map height is %d. No layout to print from game->map->layout.\n", game->map->height);
//     }
//     else
//     {
//         printf("game->map or game->map->layout is NULL. Cannot print map layout.\n");
//     }

//     printf("\n--- Debug Floor and Ceiling Colors (from game->assets) ---\n");
//     if (game->assets)
//     {
// 		for (int i = 0; i < 4; i++) // Assuming 4 textures for N, S, E, W
//         {
//             printf("Texture [%d]:\n", i);
//             if (game->assets->textures[i])
//             {
//                 printf("  Address: %p\n", (void *)game->assets->textures[i]);
//                 printf("  Width:   %d\n", game->assets->textures[i]->width);
//                 printf("  Height:  %d\n", game->assets->textures[i]->height);
//                 // You could also print other t_img members if needed, e.g.:
//                 // printf("  Bits per pixel: %d\n", game->assets->textures[i]->bits_per_pixel);
//                 // printf("  Line length:    %d\n", game->assets->textures[i]->line_length);
//                 // printf("  Endian:         %d\n", game->assets->textures[i]->endian);
//                 // printf("  Image Ptr:      %p\n", game->assets->textures[i]->ptr);
//                 // printf("  Data Address:   %p\n", (void *)game->assets->textures[i]->address);
//             }
//             else
//             {
//                 printf("  game->assets->textures[%d] pointer is NULL.\n", i);
//             }
//         }
//         if (game->assets->floor_rgb)
//         {
//             // Assuming floor_rgb points to an array of 3 ints [R, G, B]
//             printf("Floor RGB: [%d, %d, %d]\n", game->assets->floor_rgb[0], game->assets->floor_rgb[1], game->assets->floor_rgb[2]);
//             // You can also print the combined hex if you have a function to create it
//             // For example: printf("Floor Color (combined hex): 0x%08X\n", create_trgb(0, game->assets->floor_rgb[0], game->assets->floor_rgb[1], game->assets->floor_rgb[2]));
//         }
//         else
//         {
//             printf("game->assets->floor_rgb pointer is NULL.\n");
//         }

//         if (game->assets->ceiling_rgb)
//         {
//             // Assuming ceiling_rgb points to an array of 3 ints [R, G, B]
//             printf("Ceiling RGB: [%d, %d, %d]\n", game->assets->ceiling_rgb[0], game->assets->ceiling_rgb[1], game->assets->ceiling_rgb[2]);
//             // For example: printf("Ceiling Color (combined hex): 0x%08X\n", create_trgb(0, game->assets->ceiling_rgb[0], game->assets->ceiling_rgb[1], game->assets->ceiling_rgb[2]));
//         }
//         else
//         {
//             printf("game->assets->ceiling_rgb pointer is NULL.\n");
//         }
//     }
//     else
//     {
//         printf("game->assets pointer is NULL. Cannot print colors.\n");
//     }
//     printf("--- End Debug Print ---\n\n");
// }
