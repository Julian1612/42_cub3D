/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic_keys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:44:00 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 00:12:06 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_loop.h" // loop door funcs
#include "../cub3D.h"
#include "../raycast.h" // raycast funcs
#include "../debug.h" // debug_print_player
#include <math.h> // math funcs
#include <string.h> // NULL

void	handle_action_keys(
	mlx_t *mlx, t_player *player, t_game *game)
{
	if (mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT))
		player_shoot(player, game->map.enemies, game);
	else if (player->weapon != NULL)
		player->weapon->curr_frame = GUN1;
	if (mlx_is_key_down(mlx, MLX_KEY_SPACE))
		handle_door(game, player);
}

void	handle_movement_keys(mlx_t *mlx, t_player *player, t_map *map)
{
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT_SHIFT))
		player->mov_speed *= 3;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		player_move(&player->pos, map, player->dir.x
			* player->mov_speed, player->dir.y * player->mov_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		player_move(&player->pos, map, -player->dir.x
			* player->mov_speed, -player->dir.y * player->mov_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		player_move(&player->pos, map,
			rotate_x(player->dir.x, player->dir.y, M_PI_2)
			* player->mov_speed, rotate_y(player->dir.x, player->dir.y, M_PI_2)
			* player->mov_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		player_move(&player->pos, map,
			-rotate_x(player->dir.x, player->dir.y, M_PI_2)
			* player->mov_speed, -rotate_y(player->dir.x, player->dir.y, M_PI_2)
			* player->mov_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player_rotate(player, -player->rot_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player_rotate(player, player->rot_speed);
}
