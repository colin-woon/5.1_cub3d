/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:39:44 by rteoh             #+#    #+#             */
/*   Updated: 2025/05/02 16:52:48 by rteoh            ###   ########.fr       */
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
		return true;
	return false;
}

// check if texture is complete

static void check_texture_complete(t_texture *textures)
{
	if (textures->no_img_ptr == NULL
		|| textures->ea_img_ptr == NULL 
		|| textures->we_img_ptr == NULL
		|| textures->so_img_ptr == NULL)
	{
		msg("texture not complete");
	}
}

t_texture	*init_textures(void)
{
	t_texture	*textures;
	
	textures = ft_calloc(1, sizeof(t_texture));
	if (textures == NULL)
		error_msg("CALLOC ERROR\n");
	return (textures);
}



void	parse_texture(char *line, t_game *game)
{
	if (!game->textures)
		game->textures = init_textures();
	compare_texture(line, game->textures, game);
	return ;
}

// now need to work on parsing the map
// would continue to add error handling on the textures

void	store_map(char *line, char **map_layout, int map_height)
{
	int	i;

	i = map_height;
	if (!map_layout)
		map_layout = ft_calloc(1, sizeof(char *) * (i + 2));
	while (map_layout[i] != NULL)
		i++;
	map_layout[i] = line;
	map_layout[i] = new_layout;
}

t_map	*parse_map(int fd, char *line, t_game *game)
{
	t_map	*map;
	int		map_height;
	int		map_width;
	
	map_height = 1;
	map = ft_calloc(1, sizeof(t_map));
	while (line != NULL)
	{
		store_map(line, map->map_layout, map_height);
		free(line);
		line = get_next_row(fd);
	}
	map->map_height = map_height;
	return (map);
}

void parse(char *path_to_cub, t_game *game)
{
	int 	fd;
	char	*line;

	if (ft_strend(path_to_cub, ".cub") == false)
		msg("input given is not a .cub file");
	fd = open_file(path_to_cub);
	if (fd < 0)
		error_msg("File cannot be opened");
	line = get_next_row(fd);
	while (line != NULL)
	{
		if (start_of_map(line))
			break;
		parse_texture(line, game);
		free(line);
		line = get_next_row(fd);
	}
	check_texture_complete(game->textures);
	game->map = parse_map(fd, line, game);
}