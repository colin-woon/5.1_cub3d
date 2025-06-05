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

static int	ft_atoi_pro_max(char *rgb_c)
{
	int		i;
	int		rgb;
	char	*tmp;

	i = 0;
	if (rgb_c[i] == '\0')
		return (-1);
	while (ft_isdigit(rgb_c[i]) || rgb_c[i] == '-' || rgb_c[i] == '+')
		i++;
	tmp = malloc(i + 1);
	if (!tmp)
	{
		msg("Malloc Error:rgb atoi\n");
		return (-1);
	}
	tmp[i] = '\0';
	while (i-- > 0)
		tmp[i] = rgb_c[i];
	rgb = ft_atoi(tmp);
	free(tmp);
	return (rgb);
}

bool	init_rgb(char *rgb_c, int **rgb_ptr)
{
	int	color_val;
	int	*res_rgb;

	color_val = 0;
	res_rgb = ft_calloc(3, (sizeof(int)));
	if (!res_rgb)
		error_msg_exit("Calloc Error:rgb init\n");
	*rgb_ptr = res_rgb;
	while (*rgb_c)
	{
		while (!ft_isdigit(*rgb_c) && *rgb_c != '\0'
			&& *rgb_c != '-' && *rgb_c != '+')
			rgb_c++;
		res_rgb[color_val] = ft_atoi_pro_max(rgb_c);
		if (res_rgb[color_val] > 255 || res_rgb[color_val] < 0)
			return (error_msg("Invalid RGB\n"));
		color_val++;
		while (ft_isdigit(*rgb_c) || *rgb_c == '-' || *rgb_c == '+')
			rgb_c++;
	}
	if (color_val != 3)
		return (error_msg("RGB incomplete\n"));
	return (true);
}

void	fill_img_info(void *img_ptr, t_img *img)
{
	if (!img_ptr || img == NULL)
	{
		msg("img_ptr doesnt exist or t_img struct doesn't exist\n");
		return ;
	}
	img->address = mlx_get_data_addr(img_ptr,
			&img->bits_per_pixel,
			&img->line_length,
			&img->endian);
}

char	*get_file_path(char *line)
{
	char	**words;
	char	*file_path;
	int		i;

	words = ft_split(line, ' ');
	i = 0;
	while (words[i + 1])
	{
		free(words[i]);
		i++;
	}
	file_path = words[i];
	free(words);
	return (file_path);
}

void	make_img(char *str, t_game *game, t_img *texture)
{
	char	*path_to_file;

	path_to_file = get_file_path(str);
	if (!path_to_file)
		error_msg_exit("texture file given cannot be read or found\n");
	if (ft_strend(path_to_file, ".xpm") == false)
		error_msg_exit("texture file given is not a .xpm file\n");
	texture->ptr = mlx_xpm_file_to_image(game->mlx_data->ptr, path_to_file,
			&texture->height, &texture->width);
	free(path_to_file);
	if (texture->ptr == NULL)
		error_msg_exit("texture file given cannot be read\n");
	fill_img_info(texture->ptr, texture);
}
