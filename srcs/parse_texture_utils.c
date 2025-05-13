/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:49:31 by rteoh             #+#    #+#             */
/*   Updated: 2025/05/07 09:49:31 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int *init_rgb(char *rgb_c)
{
	int i = 0;
	int j = 0;
	int color_val;
	int len;
	char *tmp;
	int *res_rgb;

	color_val = 0;
	res_rgb = ft_calloc(3, (sizeof(int)));
	while (rgb_c[i])
	{
		while (!ft_isdigit(rgb_c[i]) && rgb_c[i] != '\0')
			i++;
		if (rgb_c[i] == '\0')
			break ;
		j = i;
		while (ft_isdigit(rgb_c[j]))
			j++;
		len = j - i;
		tmp = malloc(len + 1);
		tmp[len] = '\0';
		i = j;
		while (len-- > 0)
			tmp[len] = rgb_c[--j];
		res_rgb[color_val] = ft_atoi(tmp);
		color_val++;
		free(tmp);
	}
	if (color_val != 3)
		msg("RGB incomplete\n");
	return (res_rgb);
}

void *make_img(char *str, t_game *game)
{
	char *path_to_file;
	void *img_ptr;
	int img_width;
	int img_height;

	path_to_file = ft_strchr(str, '.'); // not./ maybe
	if (!path_to_file)
		return ("texture file given cannot be read or found\n");
	img_ptr = mlx_xpm_file_to_image(game->mlx_data->ptr, path_to_file, &img_height, &img_width);
	if (img_ptr == NULL)
		msg("texture file given cannot be read or found\n");
	printf("img made\n");
	return (img_ptr);
}
