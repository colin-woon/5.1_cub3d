/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <ryan42cmp@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:51:45 by rteoh             #+#    #+#             */
/*   Updated: 2025/04/24 16:23:27 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

void	msg(char *err)
{
	write(1, "ERROR\n", 6);
	ft_putstr_fd(err, 1);
	exit(EXIT_SUCCESS);
}

void	error_msg(char *err)
{
	perror(err);
	exit(EXIT_FAILURE);
}