/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 06:57:25 by rteoh             #+#    #+#             */
/*   Updated: 2025/04/28 19:25:24 by cwoon            ###   ########.fr       */
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
	// parse(av[1], &game);
	start_mlx(&game);
	return (0);
}
