/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <ryan42cmp@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:39:44 by rteoh             #+#    #+#             */
/*   Updated: 2025/04/25 14:59:16 by rteoh            ###   ########.fr       */
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
	
	printf("word match: %s\n", word_match);
	printf("buff: %s\n", buff[i]);
	printf("i: %i\n", i);
	while (*word_match == '\t' || *word_match == ' ')
		word_match++;
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
		printf("%s\n", line);
		line++;
	}
	return true;
}

static void	compare_texture(char *line, t_texture *textures, t_game *game)
{
	int	img_width;
	int	img_height;

	if (is_empty_line(line))
		return ;
	printf("line: %s\n", line);
	match_word(line);
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		textures->n_tex_file = ft_strchr(line, '.');
		textures->n_tex_img = mlx_xpm_file_to_image(game->mlx, textures->n_tex_file, &img_height, &img_width);
		mlx_put_image_to_window(game->mlx, game->mlx_win, textures->n_tex_img, 0, 0);
	}
	if (ft_strncmp(line, "SO", 2) == 0)
	{
		textures->s_tex_file = ft_strchr(line, '.');
		textures->s_tex_img = mlx_xpm_file_to_image(game->mlx, textures->s_tex_file, &img_height, &img_width);
	}
	if (ft_strncmp(line, "WE", 2) == 0)
	{
		textures->w_tex_file = ft_strchr(line, '.');
		textures->s_tex_img = mlx_xpm_file_to_image(game->mlx, textures->w_tex_file, &img_height, &img_width);
	}
	if (ft_strncmp(line, "EA", 2) == 0)
	{
		textures->e_tex_file = ft_strchr(line, '.');
		textures->s_tex_img = mlx_xpm_file_to_image(game->mlx, textures->e_tex_file, &img_height, &img_width);
	}
	if (ft_strncmp(line, "F", 1) == 0)
	{
		int	i = 0;
		int	j = 0;
		int	color_val = 0;
		int	len;
		char *tmp;

		textures->floor_rgb = ft_calloc(3, (sizeof(int)));
		while (line[i])
		{
			while (!ft_isdigit(line[i]))
				i++;
			j = i;
			while (ft_isdigit(line[j]))
				j++;
			len = j - i;
			tmp = malloc(len + 1);
			tmp[len] = '\0';
			i = j;
			while (len-- > 0)
				tmp[len] = line[--j];
			textures->floor_rgb[color_val] = ft_atoi(tmp);
			color_val++;
			free(tmp);
		}
	}
	if (ft_strncmp(line, "C", 1) == 0)
	{
		int	i = 0;
		int	j = 0;
		int	color_val = 0;
		int	len;
		char *tmp;

		textures->ceiling_rgb = ft_calloc(3, (sizeof(int)));
		while (line[i])
		{
			while (!ft_isdigit(line[i]))
				i++;
			j = i;
			while (ft_isdigit(line[j]))
				j++;
			len = j - i;
			tmp = malloc(len + 1);
			tmp[len] = '\0';
			i = j;
			while (len-- > 0)
				tmp[len] = line[--j];
			textures->ceiling_rgb[color_val] = ft_atoi(tmp);
			color_val++;
			free(tmp);
		}	
	}
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
	printf("line: %s\n", line);
	while (line != NULL)
	{
		compare_texture(line, textures, game);
		free(line);
		line = get_next_row(fd);
	}
	int i = 0;
	// while (i < 3)
	// 	printf("%i\n", textures->floor_rgb[i++]);
	if (textures->n_tex_img)
		mlx_destroy_image(game->mlx, textures->n_tex_img);
	free(textures);
}