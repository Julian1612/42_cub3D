/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:20:05 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/12 18:31:34 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_loop.h" // loop door funcs
#include "../cub3D.h"
#include "../raycast.h" // raycast funcs
#include "../debug.h" // debug_print_player
#include <math.h> // math funcs

#define MOV_SPEED 0.1
#define ROT_SPEED 0.05
#define ENEMY_SPEED 0.04

static void	handle_enemies(
	t_enemy *enemies, t_map *map, t_player *player, double fps_mult)
{
	double	angle;
	int		i;
	double	enemy_speed;

	enemy_speed = ENEMY_SPEED * fps_mult;
	i = -1;
	while (i++ < map->enemy_count)
	{
		if (enemies[i].alive == false)
			continue ;
		if (enemies[i].health <= 0)
		{
			enemy_die(&enemies[i], map, i);
			continue ;
		}
		angle = atan2(player->pos.y - enemies[i].pos.y,
				player->pos.x - enemies[i].pos.x);
		if (fabs(enemies[i].pos.x - player->pos.x) < 0.5
			&& fabs(enemies[i].pos.y - player->pos.y) < 0.5)
			enemy_attack(player, &enemies[i]);
		else
			enemy_move(&enemies[i], map, cos(angle)
				* enemy_speed, sin(angle) * enemy_speed, i);
	}
}

static void	handle_action_keys(
	mlx_t *mlx, t_player *player, t_game *game)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		errexit_msg("Escape pressed. Exiting program.");
	}
	if (mlx_is_key_down(mlx, MLX_KEY_SPACE))
		player_shoot(player, game->map.enemies, game);
	else
		player->weapon->curr_frame = GUN1;
	if (mlx_is_key_down(mlx, MLX_KEY_E))
		switch_door_state(game, player);
}

static void	handle_movement_keys(
	mlx_t *mlx, t_player *player, t_map *map, double fps_mult)
{
	double	mov_speed;
	double	rot_speed;

	mov_speed = MOV_SPEED * fps_mult;
	rot_speed = ROT_SPEED * fps_mult;
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		player_move(&player->pos, map, player->dir.x
			* mov_speed, player->dir.y * mov_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		player_move(&player->pos, map, -player->dir.x
			* mov_speed, -player->dir.y * mov_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		player_move(&player->pos, map,
			rotate_x(player->dir.x, player->dir.y, M_PI_2)
			* mov_speed, rotate_y(player->dir.x, player->dir.y, M_PI_2)
			* mov_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		player_move(&player->pos, map,
			-rotate_x(player->dir.x, player->dir.y, M_PI_2)
			* mov_speed, -rotate_y(player->dir.x, player->dir.y, M_PI_2)
			* mov_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player_rotate(player, rot_speed, true);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player_rotate(player, rot_speed, false);
}

void	loop_logic(t_game *game)
{
	double	fps_mult;

	fps_mult = get_fps_mult(game->mlx->delta_time, FPS);
	handle_action_keys(game->mlx, &game->player, game);
	handle_movement_keys(game->mlx, &game->player, &game->map, fps_mult);
	handle_enemies(game->map.enemies, &game->map, &game->player, fps_mult);
	debug_print_player(&game->player);
	if (game->player.health <= 0)
		errexit_msg("You died. Exiting program.");
}