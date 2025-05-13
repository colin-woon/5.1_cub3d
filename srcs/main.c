/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 06:57:25 by rteoh             #+#    #+#             */
/*   Updated: 2025/05/13 10:30:10 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int main(int ac, char *av[])
{
	t_game game;

	if (ac != 2)
	{
		msg("Bad Input\nExample: ./cub3D .cub\n");
		return (0);
	}
	start_mlx(&game);
	parse(av[1], &game);
	mlx_loop(game.mlx_data->ptr);
	return (0);
}
