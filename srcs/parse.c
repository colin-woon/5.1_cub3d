/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rteoh <ryan42cmp@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 16:39:44 by rteoh             #+#    #+#             */
/*   Updated: 2025/04/25 21:25:55 by rteoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static	void	match_word(char	*word_match)
{
	static	int i = 0;
	int		j;
	char 	**buff;
	buff = (char *[6]){"NO", "SO", "WE", "EA", "F", "C"};

	j = 0;
	while (j < i)
	{
		if (ft_strncmp(word_match, buff[j], ft_strlen(buff[j])) == 0)
		{
			ft_putstr_fd("ERROR:\n", 1);
			ft_dprintf(1, "Duplicate of %s found", buff[j]);
			exit(EXIT_SUCCESS);
		}
		j++;
	}
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

t_texture	*parse_texture(int fd, t_game *game)
{
	char *line;
	t_texture	*textures;
	
	textures = ft_calloc(1, sizeof(t_texture));
	line = get_next_row(fd);
	while (line != NULL)
	{
		compare_texture(line, textures, game);
		free(line);
		line = get_next_row(fd);
	}
	return (textures);
}

//now need to work on parsing the map
//would continue to add error handling on the textures

char	**parse_map(int fd, t_game *game)
{
	
}

void	parse(char *path_to_cub, t_game *game)
{
	int fd;

	if (ft_strend(path_to_cub, ".cub") == false)
		msg("input given is not a .cub file");
	fd = open_file(path_to_cub);
	if (fd < 0)
		error_msg("File cannot be opened");
	game->textures = parse_texture(fd, game);
	game->map = parse_map(fd, game);
}