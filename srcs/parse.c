/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <rteoh@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:39:44 by rteoh             #+#    #+#             */
/*   Updated: 2025/05/06 02:19:25 by rteoh            ###   ########.fr       */
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

// void	free_layout(char **map_layout)
// {
// 	int	i;

// 	i = 0;
// 	if (!map_layout)
// 		return ;
// 	while (map_layout[i] != NULL)
// 		free(map_layout[i++]);
// 	free(map_layout[i]);
// 	return ;
// }

void	store_map(char *line, t_map *map, int map_height)
{
	char	**rows;
	int		i;

	i = 0;
	rows = malloc(sizeof(*rows) * (map_height + 2));
	if (!rows)
		error_msg("malloc error\n");
	if (ft_strlen(line) > map->map_width)
		map->map_width = ft_strlen(line);
	while (i < map_height)
	{
		rows[i] = map->map_layout[i];
		i++;
	}
	rows[i] = line;
	rows[i + 1] = NULL;
	free(map->map_layout);
	map->map_layout = rows;
}

bool	ft_iswall(int c)
{
	if (c == '1')
		return true;
	return false;
}

void	check_wall_behind(char *row, int i)
{
	if (i == 0)
		return ;
	else
		if (!ft_iswall(row[i - 1]))
			msg("map is not closed\n");
	return ;
}

bool	ft_isplayer(char c)
{
	if (c == 'W' || c == 'E' || c == 'N' || c == 'S')
		return true;
	return false;
}

bool	ft_iszero(char c)
{
	if (c == '0')
		return true;
	return false;
}


void	check_horizontal_walls(char *row)
{
	int	i;

	i = 0;
	while (row[i])
	{
		if (ft_isspace(row[i]))
		{
			check_wall_behind(row, i);
			while (ft_isspace(row[i]))
				i++;
			if (!ft_iswall(row[i++]))
				msg("map is not closed\n");
		}
		while (ft_iszero(row[i]) || ft_isplayer(row[i]))
			i++;
		if (!ft_iswall(row[i++]))
			msg("map is not closed\n");
	}
	// 	printf("%c", row[i]);
}

void	check_above_wall(char **rows, int i, int j)
{
	if (i == 0)
		return ;
	if (!ft_iswall(rows[--i][j]))
		msg("map is not closed\n");
	return ;
}

void	check_vertical_walls(t_map	*map)
{
	int	i;
	int	j;
	char	**rows;

	j = 0;
	rows = map->map_layout;
	printf("map width: %i\n", map->map_width);
	printf("map height: %i\n", map->map_height);
	while (j < map->map_width)
	{
		i = 0;
		while (i < map->map_height)
		{
			printf("%c", rows[i][j]);
			if (ft_isspace(rows[i][j]))
			{
				printf("checking space\n");
				check_above_wall(rows, i, j);
				while (ft_isspace(rows[i][j]))
					i++;
				if (!ft_iswall(rows[i++][j]))
					msg("map not closed\n");
			}
			while (ft_iszero(rows[i][j]) || ft_isplayer(rows[i][j]))
			{
				printf("%c", rows[i][j]);
				i++;
			}
			if (!ft_iswall(rows[i][j]))
				msg("map not closed\n");
			i++;
		}
		printf("\nline done\n");
		j++;
	}
}

void	check_valid_map(t_map *map)
{
	int	i;

	i = 0;
	//i first look at a string
	//i skip all spaces
	//if i dont find a one
	//its error
	//imagine the spaces are squares
	// i only need to check the 1 and 0 if its the last row of the space square
	//also the first row
	while (i < map->map_height)
	{
		check_horizontal_walls(map->map_layout[i]);
		i++;
	}
	// we can run a backwards check in horizontal to make sure that it ends with a 1
	//also after that we can check if the 0 behind the 1 has a 1 surrounding it
	check_vertical_walls(map);
}

t_map	*parse_map(int fd, char *line, t_game *game)
{
	t_map	*map;
	int		map_height;
	int		map_width;

	map_height = 0;
	map = ft_calloc(1, sizeof(t_map));
	while (line != NULL)
	{
		store_map(line, map, map_height);
		map_height++;
		line = get_next_row(fd);
	}
	// int i;
	// i = 0;
	// while (map->map_layout[i] != NULL)
	// {
	// 	printf("%s\n", map->map_layout[i]);
	// 	i++;
	// }
	map->map_height = map_height;
	// printf("%i\n", map->map_height);
	// printf("%i\n", map->map_width);
	check_valid_map(map);
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
