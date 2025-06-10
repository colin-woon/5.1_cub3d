/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:43:47 by cwoon             #+#    #+#             */
/*   Updated: 2025/06/10 13:39:16 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		movement_keys(int keysym, t_game *game);
bool	is_valid_keys(int keysym);
void	recalculate_variables\
(t_game *game, t_map *map, t_player *player, int keysym);

int	movement_keys(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		close_window(game);
	if (is_valid_keys(keysym))
		recalculate_variables(game, game->map, game->player, keysym);
	return (0);
}

bool	is_valid_keys(int keysym)
{
	if (
		keysym == XK_Left || \
keysym == XK_Right || \
keysym == XK_w || \
keysym == XK_a || \
keysym == XK_s || \
keysym == XK_d
	)
		return (true);
	return (false);
}

void	recalculate_variables\
(t_game *game, t_map *map, t_player *player, int keysym)
{
	if (keysym == XK_Left || keysym == XK_Right)
		look_left_or_right(keysym, player, game);
	else if (keysym == XK_w || keysym == XK_s)
		move_forward_or_backward(keysym, player, game, map);
	else if (keysym == XK_a || keysym == XK_d)
		move_left_or_right(keysym, player, game, map);
}
