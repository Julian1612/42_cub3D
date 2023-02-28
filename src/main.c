/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/28 17:40:31 by jschneid         ###   ########.fr       */
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
#define WALL_BLOCK 64
#define NBR_OF_RAYS 1

static mlx_image_t	*img;
static mlx_image_t	*view_direction;
static mlx_image_t	*walls;
static mlx_image_t	*ray;

int draw_ray(mlx_t *mlx, t_player *player, t_map *map_data)
{
	float ray_x, ray_y, offset_x, offset_y;
	int mx, my, map_position;
	int i = 0;
	int this_ray = NBR_OF_RAYS;
	int rayHitDistance;
	float ray_angle = player->player_angle;
	while(i < this_ray)
	{
		rayHitDistance = 0;
		float aTan = -1/tan(ray_angle);
		if (ray_angle > M_PI)
		{
			ray_y = ((player->y / 64) * 64) - 0.0001;
			ray_x = (player->y - ray_y) * aTan + player->x;
			offset_y = -64;
			offset_x = -offset_y * aTan;
		}
		if (ray_angle < M_PI)
		{
			ray_y = ((player->y / 64) * 64) + 64;
			ray_x = (player->y - ray_y) * aTan + player->x;
			offset_y = 64;
			offset_x = -offset_y * aTan;
		}
		if (ray_angle == 0 || ray_angle == M_PI)
		{
			ray_x = player->x;
			ray_y = player->y;
			rayHitDistance = 8;
		}
		while(rayHitDistance<8)
		{
			mx = (int) (ray_x) / 64;
			my = (int) (ray_y) / 64;
			map_position = my * map_data->map_width + mx;
			if (map_position < map_data->map_width && map_data->map[mx][my] == '1')
				rayHitDistance = 8;
			else 
			{
				ray_x += offset_x;
				ray_y += offset_y;
				rayHitDistance++;
			}
		}
		mlx_image_to_window(mlx, ray, ray_x, ray_y);
		i++;
	}
	return (0);
}

void hook(void* param)
{
	t_hook		*hook_data;
	t_player	*player;
	mlx_t		*mlx;
	t_map		*map_data;

	hook_data = param;
	mlx = hook_data->mlx;
	player = hook_data->player;
	map_data = hook_data->map_data;
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
	if (player->player_angle > M_PI * 2)
		player->player_angle = 0;
	if (player->player_angle < M_PI * -2)
		player->player_angle = 0;
	view_direction->instances[0].y = img->instances[0].y + 10 * cos(player->player_angle);
	view_direction->instances[0].x = img->instances[0].x + 10 * sin(player->player_angle);
	printf("%f\n", player->player_angle);
	mlx_delete_image(mlx, ray);
	draw_ray(mlx, player, map_data);

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


int	main(int argc, char **argv)
{
	mlx_t			*mlx;
	t_player		player;
	t_hook			hook_data;
	t_map			map_data;
	// t_player		player_pos;
	int i = 0;
	int j = 0;

	(void)argc;
	(void)argv;
	if (parser(&argc, argv, &map_data))
		return (1);
	if (!(mlx = mlx_init ((map_data.map_hight * WALL_BLOCK),(map_data.map_width * WALL_BLOCK)-WALL_BLOCK, "Cub3D", true)))
		return (EXIT_FAILURE);
	player.player_angle = 0;
	hook_data.mlx = mlx;
	hook_data.player = &player;
	hook_data.map_data = &map_data;
	// if (init_player_position(&map_data, &player_pos))
	// 	return (1);
	img = mlx_new_image(mlx, PLAYER_SIZE, PLAYER_SIZE);
	view_direction = mlx_new_image(mlx, DIRECTION, DIRECTION);
	walls = mlx_new_image(mlx, WALL_BLOCK, WALL_BLOCK);
	ray = mlx_new_image(mlx, WALL_BLOCK, WALL_BLOCK);
	memset(img->pixels, 255, img->width * img->height * sizeof(int));
	memset(view_direction->pixels, 255, view_direction->width * view_direction->height * sizeof(int));
	memset(walls->pixels, 255, walls->width * walls->height * sizeof(int));
	memset(ray->pixels, 255, ray->width * ray->height * sizeof(int));
	while ((i * WALL_BLOCK) < (map_data.map_hight * WALL_BLOCK))
	{
		while ((j * WALL_BLOCK) < (map_data.map_width * WALL_BLOCK))
		{
			if (map_data.map[i][j] == '1')
				mlx_image_to_window(mlx, walls, i * WALL_BLOCK, j * WALL_BLOCK);
			j++;
		}
		j = 0;
		i++;
	}
	mlx_image_to_window(mlx, img, 80, 90);
	mlx_image_to_window(mlx, view_direction, 0, 0);
	mlx_image_to_window(mlx, ray, 0, 0);
	mlx_loop_hook(mlx, &hook, &hook_data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);

}
