/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:51:13 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/01 22:27:46 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game
#include "../libraries/mlx/include/MLX42/MLX42.h" // MLX_functions
#include <stdio.h> // @note remove
#include <math.h> // cos, sin
#include <stdbool.h> // bool

#define MOV_SPEED 10 // @note the higher, the slower
#define ROT_SPEED 0.5 // @note the higher, the slower
#define PLAYER_SIZE 0.2 // @todo size of player, switch to actual player size

// @todo drifting collision
// @note collision problem: if speed is too high, player can move through walls
// @note function usable for enemies?
bool	check_collision(double x, double y, char **map)
{
	if (map[(int)(y + PLAYER_SIZE)][(int)(x)] == WALL)
		return (true);
	if (map[(int)(y - PLAYER_SIZE)][(int)(x)] == WALL)
		return (true);
	if (map[(int)(y)][(int)(x + PLAYER_SIZE)] == WALL)
		return (true);
	if (map[(int)(y)][(int)(x - PLAYER_SIZE)] == WALL)
		return (true);
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
		if (!check_collision(player->x + sin(player->view_dir) / MOV_SPEED, player->y, map))
			player->x += sin(player->view_dir) / MOV_SPEED;
		if (!check_collision(player->x, player->y + cos(player->view_dir) / MOV_SPEED, map))
			player->y += cos(player->view_dir) / MOV_SPEED;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		if (!check_collision(player->x - sin(player->view_dir) / MOV_SPEED, player->y, map))
			player->x -= sin(player->view_dir) / MOV_SPEED;
		if (!check_collision(player->x, player->y - cos(player->view_dir) / MOV_SPEED, map))
			player->y -= cos(player->view_dir) / MOV_SPEED;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		if (!check_collision(player->x + sin(player->view_dir - M_PI_2) / MOV_SPEED, player->y, map))
			player->x += sin(player->view_dir - M_PI_2) / MOV_SPEED;
		if (!check_collision(player->x, player->y + cos(player->view_dir - M_PI_2) / MOV_SPEED, map))
			player->y += cos(player->view_dir - M_PI_2) / MOV_SPEED;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		if (!check_collision(player->x - sin(player->view_dir - M_PI_2) / MOV_SPEED, player->y, map))
			player->x -= sin(player->view_dir - M_PI_2) / MOV_SPEED;
		if (!check_collision(player->x, player->y - cos(player->view_dir - M_PI_2) / MOV_SPEED, map))
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
