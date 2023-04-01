/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:51:13 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/01 21:50:17 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game
#include "../libraries/mlx/include/MLX42/MLX42.h" // MLX_functions
#include <stdio.h> // @note remove
#include <math.h> // cos, sin
#include <stdbool.h> // bool

#define MOV_SPEED 10 // @note the higher, the slower
#define ROT_SPEED 1 // @note the higher, the slower

// @todo drifting collision
// @note collision problem: if speed is too high, player can move through walls
// @note function usable for enemies?
bool	check_collision_x(double x, double y, double offset, char **map)
{
	x += offset;
	if (map[(int)(y)][(int)(x)] == WALL)
	{
		// printf("collision!\n");
		return (true);
	}
	// printf("no...\n");
	return (false);
}

bool	check_collision_y(double x, double y, double offset, char **map)
{
	y += offset;
	if (map[(int)(y)][(int)(x)] == WALL)
	{
		// printf("collision!\n");
		return (true);
	}
	// printf("no...\n");
	return (false);
}

void	keys(mlx_t *mlx, t_minimap *minimap, t_player *player, char **map)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		errexit_msg("Escape pressed. Exiting program.");
	}
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		if (!check_collision_x(player->x, player->y, sin(player->view_dir) / MOV_SPEED, map))
			player->x += sin(player->view_dir) / MOV_SPEED;
		if (!check_collision_y(player->x, player->y, cos(player->view_dir) / MOV_SPEED, map))
			player->y += cos(player->view_dir) / MOV_SPEED;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		if (!check_collision_x(player->x, player->y, -sin(player->view_dir) / MOV_SPEED, map))
			player->x -= sin(player->view_dir) / MOV_SPEED;
		if (!check_collision_y(player->x, player->y, -cos(player->view_dir) / MOV_SPEED, map))
			player->y -= cos(player->view_dir) / MOV_SPEED;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		if (!check_collision_x(player->x, player->y, sin(player->view_dir - M_PI_2) / MOV_SPEED, map))
			player->x += sin(player->view_dir - M_PI_2) / MOV_SPEED;
		if (!check_collision_y(player->x, player->y, cos(player->view_dir - M_PI_2) / MOV_SPEED, map))
			player->y += cos(player->view_dir - M_PI_2) / MOV_SPEED;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		if (!check_collision_x(player->x, player->y, -sin(player->view_dir - M_PI_2) / MOV_SPEED, map))
			player->x -= sin(player->view_dir - M_PI_2) / MOV_SPEED;
		if (!check_collision_y(player->x, player->y, -cos(player->view_dir - M_PI_2) / MOV_SPEED, map))
			player->y -= cos(player->view_dir - M_PI_2) / MOV_SPEED;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->view_dir += M_PI / 90 / ROT_SPEED; // @note radian rotated by 5 degrees (1pi = 180 degrees)
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->view_dir -= M_PI / 90 / ROT_SPEED;
	if (mlx_is_key_down(mlx, MLX_KEY_1))
		player->view_dir = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_2))
		player->view_dir = M_PI / 2;
	if (mlx_is_key_down(mlx, MLX_KEY_3))
		player->view_dir = M_PI;
	if (mlx_is_key_down(mlx, MLX_KEY_4))
		player->view_dir = M_PI * 1.5;
}

void	hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	// mouse handling
	// minimap
	// collision
	// enemy
	keys(game->mlx, &game->minimap, &game->player, game->map.map);
	render_world(game);
	// @note all images have to be resized here
	mlx_resize_image(game->img_a, game->mlx->width, game->mlx->height);
}
