/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:20:05 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/12 16:43:23 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
#include "../raycast.h" // raycast funcs
#include "../debug.h" // debug_print_player
#include <math.h> // math funcs

#define MOV_SPEED 0.1
#define ROT_SPEED 0.05
#define DOOR_COOLDOWN 0.2
#define PLAYER_REACH 2.0
#define ENEMY_SPEED 0.04

static void	handle_enemies(
	t_enemy *enemies, t_map *map, t_player *player, double fps_mult)
{
	t_vec	dir;
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
		angle = atan2(player->pos.y - enemies[i].pos.y, player->pos.x - enemies[i].pos.x);
		dir.x = cos(angle);
		dir.y = sin(angle);
		if (fabs(enemies[i].pos.x - player->pos.x) < 0.5 && fabs(enemies[i].pos.y - player->pos.y) < 0.5)
			enemy_attack(player, &enemies[i]);
		else
			enemy_move(&enemies[i], map, dir.x * enemy_speed, dir.y * enemy_speed, i);
	}
}

static void	switch_door_state(t_game *game, t_player *player)
{
	t_rayhit	hit;
	char		target;
	int			i;

	i = 0;
	while (i < game->map.door_count)
	{
		if (mlx_get_time() - game->map.doors[i].last_action > DOOR_COOLDOWN)
		{
			if (game->map.doors[i].open == false)
				target = DOOR_CLOSED;
			else
				target = DOOR_OPEN;
			raycast_cast_ray(&hit, game, player->dir, target);
			if (hit.hit == target && hit.dist <= PLAYER_REACH && hit.dist > 0.5)
			{
				if (game->map.doors[i].open == false)
					game->map.arr[game->map.doors[i].y][game->map.doors[i].x] = DOOR_OPEN;
				else
					game->map.arr[game->map.doors[i].y][game->map.doors[i].x] = DOOR_CLOSED;
				game->map.doors[i].open = switch_bool(game->map.doors[i].open);
			}
			game->map.doors[i].last_action = mlx_get_time();
		}
		i++;
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
