/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <ryan42cmp@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:39:44 by rteoh             #+#    #+#             */
/*   Updated: 2025/04/25 16:28:53 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


//goal is to get the textures and the floor colour
//something like what i did, was to put it into a struct

//i have succesfully initialized it to the way i want it to
//i would want to add a checking function that is static and goes to the next point in the array or something like that
//so it would be like a iterator as such moving after initializing one.

//next step is to check that it is in a strict format of no so we ea f c
//plan to use 

static	void	match_word(char	*word_match)
{
	static	int i = 0;
	char *buff[6] = {"NO", "SO", "WE", "EA", "F", "C"};

	if (i > 5)
		msg("Format of cub is wrong\nexample NO-SO-WE-EA-F-C");
	if (ft_strncmp(word_match, buff[i], ft_strlen(buff[i])) != 0)
		msg("Format of cub is wrong\nexample NO-SO-WE-EA-F-C");
	i++;
	return ;
}


static bool	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != '\t' || *line != ' ' || *line != '\n')
			return false;
		line++;
	}
	return true;
}


//writing to initialize rgb
//removing useless information like keeping n_tex_file
//make code neater by making a function that has mlx_xpm bla bla to just make_img

int	*init_rgb(char *rgb_c)
{
		int	i = 0;
		int	j = 0;
		int	color_val = 0;
		int	len;
		char *tmp;
		int		*res_rgb;

		res_rgb = ft_calloc(3, (sizeof(int)));
		while (rgb_c[i])
		{
			while (!ft_isdigit(rgb_c[i]))
				i++;
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
	return (res_rgb);
}

void	*make_img(char	*str, t_game *game)
{
	char	*path_to_file;
	void	*img_ptr;
	int		img_width;
	int		img_height;
	
	path_to_file = ft_strchr(str, '.');
	img_ptr = mlx_xpm_file_to_image(game->mlx, path_to_file, &img_height, &img_width);
}

static void	compare_texture(char *line, t_texture *textures, t_game *game)
{
	if (is_empty_line(line))
		return ;
	while (*line == '\t' || *line == ' ')
		line++;
	match_word(line);
	if (ft_strncmp(line, "NO", 2) == 0)
		textures->n_tex_img = make_img(line, game);
	else if (ft_strncmp(line, "SO", 2) == 0)
		textures->s_tex_img = make_img(line, game);
	else if (ft_strncmp(line, "WE", 2) == 0)
		textures->w_tex_img = make_img(line, game);
	else if (ft_strncmp(line, "EA", 2) == 0)
		textures->e_tex_img = make_img(line, game);
	else if (ft_strncmp(line, "F", 1) == 0)
		textures->floor_rgb = init_rgb(line);
	else if (ft_strncmp(line, "C", 1) == 0)
		textures->ceiling_rgb = init_rgb(line);
	return ;
}



void parse_map(char *path_to_cub, t_game *game)
{
	int fd;
	char *line;
	t_texture	*textures;

	if (ft_strend(path_to_cub, ".cub") == false)
		msg("input given is not a .cub file");
	fd = open_file(path_to_cub);
	textures = ft_calloc(1, sizeof(t_texture));
	line = get_next_row(fd);
	while (line != NULL)
	{
		compare_texture(line, textures, game);
		free(line);
		line = get_next_row(fd);
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, textures->n_tex_img, 0, 0);
	if (textures->n_tex_img)
		mlx_destroy_image(game->mlx, textures->n_tex_img);
	free(textures->ceiling_rgb);
	free(textures->floor_rgb);
	free(textures);
}