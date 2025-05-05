/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwoon <cwoon@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:24:08 by cwoon             #+#    #+#             */
/*   Updated: 2025/05/05 20:54:21 by cwoon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(int keycode, t_mlx *mlx);
int	key_hook(int keysym, t_game *game);
void	start_mlx(t_game *game);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void init_mlx_img(t_mlx *mlx);
void draw_vertical_line(t_mlx *mlx, int x, int from, int to, int color);
void init_floor_and_ceiling(t_mlx *mlx, int color);

int	key_hook(int keysym, t_game *game)
{
	// printf("DEBUG: sym INT is %d\n", keysym);
	printf("DEBUG: sym HEXA is %x\n", keysym);
	if (keysym == XK_Escape)
	{
		printf("DEBUG: Escape\n");
		close_window(0, NULL);
	}
	else if (keysym == XK_Left)
	{
		double old_dirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(ROTATION_SPEED) - game->player->dir_y * sin(ROTATION_SPEED);
		game->player->dir_y = old_dirX * sin(ROTATION_SPEED) + game->player->dir_y * cos(ROTATION_SPEED);
		double oldPlaneX = game->player->plane_x;
		game->player->plane_x = game->player->plane_x * cos(ROTATION_SPEED) - game->player->plane_y * sin(ROTATION_SPEED);
		game->player->plane_y = oldPlaneX * sin(ROTATION_SPEED) + game->player->plane_y * cos(ROTATION_SPEED);
		printf("Left\n");
	}
	else if (keysym == XK_Right)
	{
		double oldDirX = game->player->dir_x;
		game->player->dir_x = game->player->dir_x * cos(-ROTATION_SPEED) - game->player->dir_y * sin(-ROTATION_SPEED);
		game->player->dir_y = oldDirX * sin(-ROTATION_SPEED) + game->player->dir_y * cos(-ROTATION_SPEED);
		double oldPlaneX = game->player->plane_x;
		game->player->plane_x = game->player->plane_x * cos(-ROTATION_SPEED) - game->player->plane_y * sin(-ROTATION_SPEED);
		game->player->plane_y = oldPlaneX * sin(-ROTATION_SPEED) + game->player->plane_y * cos(-ROTATION_SPEED);
		printf("Right\n");
	}
	else if (keysym == XK_w)
	{
		if(game->map[(int)(game->player->pos_x + game->player->dir_x * MOVE_SPEED)][(int)game->player->pos_y] == false)
			game->player->pos_x += game->player->dir_x * MOVE_SPEED;
		if(game->map[(int)game->player->pos_x][(int)(game->player->pos_y + game->player->dir_y * MOVE_SPEED)] == false)
			game->player->pos_y += game->player->dir_y * MOVE_SPEED;
		printf("w\n");
	}
	else if (keysym == XK_a)
	{
		// Move left (perpendicular to direction, using plane vector)
		if(game->map[(int)(game->player->pos_x - game->player->plane_x * MOVE_SPEED)][(int)game->player->pos_y] == false)
			game->player->pos_x -= game->player->plane_x * MOVE_SPEED;
		if(game->map[(int)game->player->pos_x][(int)(game->player->pos_y - game->player->plane_y * MOVE_SPEED)] == false)
			game->player->pos_y -= game->player->plane_y * MOVE_SPEED;
		printf("a\n");
	}
	else if (keysym == XK_s)
	{
		if(game->map[(int)(game->player->pos_x - game->player->dir_x * MOVE_SPEED)][(int)game->player->pos_y] == false)
			game->player->pos_x -= game->player->dir_x * MOVE_SPEED;
		if(game->map[(int)(game->player->pos_x)][(int)(game->player->pos_y - game->player->dir_y * MOVE_SPEED)] == false)
			game->player->pos_y -= game->player->dir_y * MOVE_SPEED;
		printf("s\n");
	}
	else if (keysym == XK_d)
	{
		// Move right (perpendicular to direction, using plane vector)
		if(game->map[(int)(game->player->pos_x + game->player->plane_x * MOVE_SPEED)][(int)game->player->pos_y] == false)
			game->player->pos_x += game->player->plane_x * MOVE_SPEED;
		if(game->map[(int)game->player->pos_x][(int)(game->player->pos_y + game->player->plane_y * MOVE_SPEED)] == false)
			game->player->pos_y += game->player->plane_y * MOVE_SPEED;
		printf("d\n");
	}
	run_raycasting(game->ray, game->player, game->mlx_data, game);
	return (0);
}

int	close_window(int keycode, t_mlx *mlx)
{
	printf("DEBUG: closing window\n");
	exit(0);
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->address + (y * img->line_length + x * (img->bits_per_pixel / 8));
	// printf("endian%d\n", img->endian);
	*(unsigned int*)dst = color;
}

void init_mlx_img(t_mlx *mlx)
{
	mlx->img = malloc(sizeof(t_img));
	mlx->img->ptr = mlx_new_image(mlx->ptr, WIDTH, HEIGHT);

	mlx->img->address = mlx_get_data_addr(mlx->img->ptr, &mlx->img->bits_per_pixel, &mlx->img->line_length,
								&mlx->img->endian);
}
// DEBUG: create_trgb should change to color/texture
void draw_vertical_line(t_mlx *mlx, int x, int from, int to, int color)
{
	(void)color;
	int y = from;

	while (y < to)
	{
		my_mlx_pixel_put(mlx->img, x, y, create_trgb(0, 220, 100, 0));
		y++;
	}
}

// DEBUG: should add ceiling texture, floor texture
void init_floor_and_ceiling(t_mlx *mlx, int color)
{
	int x;
	int y;

	(void)color;
	x = 0;
	while (x < HEIGHT/2)
	{
		y = 0;
		while (y < WIDTH)
		{
			my_mlx_pixel_put(mlx->img, y, x, create_trgb(0, 0, 0, 220));
			y++;
		}
		x++;
	}
	while (x < HEIGHT)
	{
		y = 0;
		while (y < WIDTH)
		{
			my_mlx_pixel_put(mlx->img, y, x, create_trgb(0, 0, 220, 0));
			y++;
		}
		x++;
	}
}

void start_mlx(t_game *game)
{
	t_mlx	mlx;
	void	*img;
	// char	*relative_path = "imgs/Tung_tung_tung_tung_tung_sahur.xpm";
	int		img_width;
	int		img_height;


	game->mlx_data = malloc(sizeof(t_mlx));
	game->mlx_data->ptr = mlx_init();
	game->mlx_data->window = mlx_new_window(game->mlx_data->ptr, WIDTH, HEIGHT, "Cub3d");
	mlx_hook(game->mlx_data->window, DestroyNotify, 0, close_window, &game->mlx_data);
	init_mlx_img(game->mlx_data);
	// draw_pixels(game->mlx_data);
	// img = mlx_xpm_file_to_image(game->mlx_data->ptr, relative_path, &img_width, &img_height);
	// if (!img)
	// 	printf("image failed to read\n");
	// mlx_put_image_to_window(game->mlx_data->ptr, game->mlx_data->window, img, 100, 100);
	// mlx_loop(game->mlx_data->ptr);
}
