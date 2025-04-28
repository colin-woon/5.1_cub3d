/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:39:44 by rteoh             #+#    #+#             */
/*   Updated: 2025/04/28 16:49:53 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != '\t' || *line != ' ' || *line != '\n')
			return false;
		line++;
	}
	return true;
}

// writing to initialize rgb
// removing useless information like keeping n_tex_file
// make code neater by making a function that has mlx_xpm bla bla to just make_img

int *init_rgb(char *rgb_c)
{
	int i = 0;
	int j = 0;
	int color_val = 0;
	int len;
	char *tmp;
	int *res_rgb;

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

void *make_img(char *str, t_game *game)
{
	char *path_to_file;
	void *img_ptr;
	int img_width;
	int img_height;

	path_to_file = ft_strchr(str, '.'); // not./ maybe
	img_ptr = mlx_xpm_file_to_image(game->mlx, path_to_file, &img_height, &img_width);
	return (img_ptr);
}

static void compare_texture(char *line, t_texture *textures, t_game *game)
{
	if (is_empty_line(line))
		return;
	while (*line == '\t' || *line == ' ')
		line++;
	if (ft_strncmp(line, "NO", 2) == 0)
		textures->no_img_ptr = make_img(line, game);
	else if (ft_strncmp(line, "SO", 2) == 0)
		textures->so_img_ptr = make_img(line, game);
	else if (ft_strncmp(line, "WE", 2) == 0)
		textures->we_img_ptr = make_img(line, game);
	else if (ft_strncmp(line, "EA", 2) == 0)
		textures->ea_img_ptr = make_img(line, game);
	else if (ft_strncmp(line, "F", 1) == 0)
		textures->floor_rgb = init_rgb(line);
	else if (ft_strncmp(line, "C", 1) == 0)
		textures->ceiling_rgb = init_rgb(line);
	return;
}

// i need to check if its the start of the map
// defined by 1 0 number found on the line

static bool start_of_map(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_isdigit(line[i]))
	{
		printf("%s\n", line);
		return true;
	}
	return false;
}

// check if texture is complete

static void check_texture_complete(t_texture *textures)
{
	if (textures->no_img_ptr == NULL || textures->ea_img_ptr == NULL 
		|| textures->we_img_ptr == NULL
		|| textures->so_img_ptr == NULL)
	{
		msg("texture not complete");
	}
}

t_texture *parse_texture(int fd, t_game *game)
{
	char *line;
	t_texture *textures;

	textures = ft_calloc(1, sizeof(t_texture));
	line = get_next_row(fd);
	while (line != NULL)
	{
		if (start_of_map(line))
			break;
		compare_texture(line, textures, game);
		free(line);
		line = get_next_row(fd);
	}
	check_texture_complete(textures);
	return (textures);
}

// now need to work on parsing the map
// would continue to add error handling on the textures

// char	**parse_map(int fd, t_game *game)
// {

// }

void parse(char *path_to_cub, t_game *game)
{
	int fd;

	if (ft_strend(path_to_cub, ".cub") == false)
		msg("input given is not a .cub file");
	fd = open_file(path_to_cub);
	if (fd < 0)
		error_msg("File cannot be opened");
	game->textures = parse_texture(fd, game);
	// game->map = parse_map(fd, game);
}