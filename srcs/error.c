/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:51:45 by rteoh             #+#    #+#             */
/*   Updated: 2025/06/09 21:11:58 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	msg(char *err)
{
	write(1, "ERROR:\n", 7);
	ft_putstr_fd(err, 1);
}

bool	error_msg(char *err)
{
	msg(err);
	return (false);
}

void	error_msg_exit(char *err, t_game *game)
{
	msg(err);
	cleanup(game);
	exit(EXIT_FAILURE);
}
