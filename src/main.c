/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/11 11:51:22 by jschneid         ###   ########.fr       */
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
#define WALL_BLOCK 50

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

int draw_walls(mlx_t *mlx, t_map *map_data)
{
	int i = 0;
	int j = 0;

	while (map_data->map[i] != NULL)
	{
		while (map_data->map[i][j] != '\0')
		{
			if (map_data->map[i][j] == '1')
				mlx_image_to_window(mlx, walls, i, j);
			j++;
		}
		j = 0;
		i++;
	}
	return 0;
}

void	play_music(void)
{
	system("afplay ./preussengloria.mp3 &");
}


int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	play_music();
}
