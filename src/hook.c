/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/04/03 14:29:05 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game
#include "../libraries/mlx/include/MLX42/MLX42.h" // MLX_functions
#include <stdio.h> // @note remove
#include <math.h> // cos, sin
#include <stdbool.h> // bool

#define MOV_SPEED 10 // @note the higher, the slower
#define ROT_SPEED 0.5 // @note the higher, the slower
#define PLAYER_SIZE 0.2

// @note function usable for enemies?
static bool	check_collision(double x, double y, char **map)
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

static void	move_player(t_player *player, char **map, double x_offset, double y_offset)
{
	if (!check_collision(player->x + x_offset, player->y, map))
		player->x += x_offset;
	if (!check_collision(player->x, player->y + y_offset, map))
		player->y += y_offset;
}

static void	keys(mlx_t *mlx, t_minimap *minimap, t_player *player, char **map)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		errexit_msg("Escape pressed. Exiting program.");
	}
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move_player(player, map, sin(player->view_angle) / MOV_SPEED, cos(player->view_angle) / MOV_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		move_player(player, map, -sin(player->view_angle) / MOV_SPEED, -cos(player->view_angle) / MOV_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_player(player, map, sin(player->view_angle - M_PI_2) / MOV_SPEED, cos(player->view_angle - M_PI_2) / MOV_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_player(player, map, -sin(player->view_angle - M_PI_2) / MOV_SPEED, -cos(player->view_angle - M_PI_2) / MOV_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->view_angle += M_PI / 90 / ROT_SPEED; // @note radian rotated by 5 degrees (1pi = 180 degrees)
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->view_angle -= M_PI / 90 / ROT_SPEED;
	if (mlx_is_key_down(mlx, MLX_KEY_1))
		player->view_angle = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_2))
		player->view_angle = M_PI / 2;
	if (mlx_is_key_down(mlx, MLX_KEY_3))
		player->view_angle = M_PI;
	if (mlx_is_key_down(mlx, MLX_KEY_4))
		player->view_angle = M_PI * 1.5;
}

static bool	skip_frame(mlx_t *mlx, int fps)
{
	if (mlx->delta_time * fps > 1.1)
		return (true);
	return (false);
}

void	hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	// mouse handling
	// minimap
	// collision
	// enemy
	if (skip_frame(game->mlx, FPS) == false)
	{
		keys(game->mlx, &game->minimap, &game->player, game->map.map);
		render_world(game);
	}
	// @note all images have to be resized here
	mlx_resize_image(game->img_a, game->mlx->width, game->mlx->height);
}
