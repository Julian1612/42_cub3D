/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/26 21:17:44 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parser.h"
#include "player_position.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define WIDTH 512
#define HEIGHT 512
#define PLAYER_SIZE 2
#define DIRECTION 2
#define WALL_BLOCK 10

static mlx_image_t	*img;
static mlx_image_t	*view_direction;
static mlx_image_t	*walls;

void hook(void* param)
{
	t_hook		*hook_data;
	t_player	*player;
	mlx_t		*mlx;

	hook_data = param;
	mlx = hook_data->mlx;
	player = hook_data->player;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		img->instances[0].y += cos(player->player_angle) * 5;
		img->instances[0].x += sin(player->player_angle) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		img->instances[0].y -= cos(player->player_angle) * 5;
		img->instances[0].x -= sin(player->player_angle) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		img->instances[0].y += cos(player->player_angle - M_PI_2) * 5;
		img->instances[0].x += sin(player->player_angle - M_PI_2) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		img->instances[0].y += cos(player->player_angle + M_PI_2) * 5;
		img->instances[0].x += sin(player->player_angle + M_PI_2) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->player_angle += M_PI / 180 * 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->player_angle -= M_PI / 180 * 5;
	view_direction->instances[0].y = img->instances[0].y + 10 * cos(player->player_angle);
	view_direction->instances[0].x = img->instances[0].x + 10 * sin(player->player_angle);
}

// int draw_walls(t_map *map_data)
// {
// 	int i = 0;

// 	while (i < 10)
// 	{
// 		i++;
// 	}

// }

int	main(int argc, char **argv)
{
	mlx_t			*mlx;
	t_player		player;
	t_hook			hook_data;
	t_map			map_data;
	// t_player		player_pos;

	(void)argc;
	(void)argv;
	if (!(mlx = mlx_init (WIDTH, HEIGHT, "Cub3D", true)))
		return (EXIT_FAILURE);
	player.player_angle = M_PI;
	hook_data.mlx = mlx;
	hook_data.player = &player;
	// if (parser(&argc, argv, &map_data))
	// 	return (1);
	// if (init_player_position(&map_data, &player_pos))
	// 	return (1);
	img = mlx_new_image(mlx, PLAYER_SIZE, PLAYER_SIZE);
	view_direction = mlx_new_image(mlx, DIRECTION, DIRECTION);
	walls = mlx_new_image(mlx, WALL_BLOCK, WALL_BLOCK);
	memset(img->pixels, 255, img->width * img->height * sizeof(int));
	memset(view_direction->pixels, 255, view_direction->width * view_direction->height * sizeof(int));
	memset(walls->pixels, 255, walls->width * walls->height * sizeof(int));
	mlx_image_to_window(mlx, img, 200, 200);
	mlx_image_to_window(mlx, view_direction, 0, 0);
	mlx_image_to_window(mlx, walls, 0, 0);
	mlx_image_to_window(mlx, walls, 10, 0);
	mlx_image_to_window(mlx, walls, 20, 0);
	// draw_walls(&map_data);
	mlx_loop_hook(mlx, &hook, &hook_data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);

}
