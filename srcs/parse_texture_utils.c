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

bool init_rgb(char *rgb_c, int *rgb_ptr)
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
		while (!ft_isdigit(rgb_c[i]) && rgb_c[i] != '\0' && rgb_c[i] != '-' && rgb_c[i] != '+')
			i++;
		if (rgb_c[i] == '\0')
			break;
		j = i;
		while (ft_isdigit(rgb_c[j]) || rgb_c[j] == '-' || rgb_c[j] == '+')
			j++;
		len = j - i;
		tmp = malloc(len + 1);
		tmp[len] = '\0';
		i = j;
		while (len-- > 0)
			tmp[len] = rgb_c[--j];
		res_rgb[color_val] = ft_atoi(tmp);
		if (res_rgb[color_val] > 255 || res_rgb[color_val] < 0)
		{
			msg("Invalid RGB\n");
			return (false);
		}
		color_val++;
		free(tmp);
	}
	if (color_val != 3)
	{
		msg("RGB incomplete\n");
		return (false);
	}
	rgb_ptr = res_rgb;
	return (true);
}

void fill_img_info(void *img_ptr, t_img *img)
{
	if (!img_ptr || img == NULL)
	{
		msg("img_ptr doesnt exist or t_img struct doesn't exist");
		return;
	}
	img->address = mlx_get_data_addr(img_ptr,
									 &img->bits_per_pixel,
									 &img->line_length,
									 &img->endian);
}

void make_img(char *str, t_game *game, t_img *texture)
{
	char *path_to_file;
	// t_img	*img;

	path_to_file = ft_strchr(str, '.'); // not./ maybe
	if (!path_to_file)
	{
		msg("texture file given cannot be read or found\n");
		return 	;
	}
	// img = ft_calloc(1, sizeof(t_img));
	// if (!img)
	// 	error_msg_exit("Calloc Error: make img");
	texture->ptr = mlx_xpm_file_to_image(game->mlx_data->ptr, path_to_file, &texture->height, &texture->width);
	if (texture->ptr == NULL)
		msg("texture file given cannot be read or found\n");
	fill_img_info(texture->ptr, texture);
	// return (texture);
}
