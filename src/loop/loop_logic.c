/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:20:05 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 19:36:26 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_loop.h" // loop door funcs
#include "../cub3D.h"
#include "../raycast.h" // raycast funcs
#include "../debug.h" // debug_print_player
#include <math.h> // math funcs
#include <string.h> // NULL
#include <stdbool.h> // bool

static void	handle_enemies_take_action(int i, t_game *game,
	double enemy_speed, int *sound_id)
{
	double	angle;
	t_vec	offset;

	if (game->map.enemies[i].alive == false || map->enemies[i].health <= 0)
	{
		enemy_die(&map->enemies[i], sound_id);
		return ;
	}
	angle = atan2(player->pos.y - map->enemies[i].pos.y,
			player->pos.x - map->enemies[i].pos.x);
	if (fabs(map->enemies[i].pos.x - player->pos.x) < 0.5
		&& fabs(map->enemies[i].pos.y - player->pos.y) < 0.5)
		enemy_attack(player, &map->enemies[i], sound_id);
	else
	{
		offset.x = cos(angle) * enemy_speed;
		offset.y = sin(angle) * enemy_speed;
		enemy_move(&map->enemies[i], map, offset, i);
	}
}

static void	handle_enemies(t_map *map, t_player *player,
	double fps_mult, int *sound_id)
{
	int		i;
	double	enemy_speed;

	if (map->enemy_count == 0)
		return ;
	enemy_speed = ENEMY_SPEED * fps_mult;
	i = -1;
	while (i++ < map->enemy_count - 1)
		handle_enemies_take_action(i, map, player, enemy_speed, sound_id);
}

static void	handle_mouse_movement(mlx_t *mlx, t_player *player)
{
	double			rot_speed;
	int32_t			new_x;
	int32_t			new_y;
	static int32_t	last_x = 0;
	static int32_t	last_y = 0;

	if (last_x == 0 && last_y == 0)
		mlx_get_mouse_pos(mlx, &last_x, &last_y);
	mlx_get_mouse_pos(mlx, &new_x, &new_y);
	rot_speed = (double)(new_x - last_x) *player->rot_speed * 0.015;
	player_rotate(player, rot_speed);
	last_x = new_x;
}

void	loop_logic(t_game *game, double fps_mult)
{
	game->player.mov_speed = MOV_SPEED * fps_mult;
	game->player.rot_speed = ROT_SPEED * fps_mult;
	handle_action_keys(game->mlx, &game->player, game);
	handle_movement_keys(game->mlx, &game->player, &game->map);
	handle_mouse_movement(game->mlx, &game->player);
	handle_enemies(&game->map, &game->player, fps_mult, game->sound_id);
	debug_print_player(&game->player);
}
