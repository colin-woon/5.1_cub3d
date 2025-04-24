/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <ryan42cmp@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:10:13 by rteoh             #+#    #+#             */
/*   Updated: 2025/04/24 16:24:23 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


char	*get_next_row(int fd)
{
	char *line;
	char *res_line;
	
	line = get_next_line(fd);
	res_line = ft_strtrim(line, "\n");
	free(line);
	return (res_line);
}

bool ft_strend(char *s, char *suffix)
{
	size_t s_len;
	size_t suffix_len;

	s_len = ft_strlen(s);
	suffix_len = ft_strlen(suffix);

	if (suffix_len > s_len)
		return false;
	while (suffix_len > 0)
	{
		if (s[s_len--] != suffix[suffix_len--])
			return (false);
	}
	return true;
}