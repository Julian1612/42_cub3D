/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:20:05 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/13 15:55:25 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_loop.h" // loop door funcs
#include "../cub3D.h"
#include "../raycast.h" // raycast funcs
#include "../debug.h" // debug_print_player
#include <math.h> // math funcs
#include <string.h> // NULL

static void	handle_enemies(
	t_enemy *enemies, t_map *map, t_player *player, double fps_mult)
{
	double	angle;
	int		i;
	double	enemy_speed;
	t_vec	offset;

	if (map->enemy_count == 0)
		return ;
	enemy_speed = ENEMY_SPEED * fps_mult;
	i = -1;
	while (i++ < map->enemy_count)
	{
		if (enemies[i].alive == false || enemies[i].health <= 0)
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
		{
			offset.x = cos(angle) * enemy_speed;
			offset.y = sin(angle) * enemy_speed;
			enemy_move(&enemies[i], map, offset, i);
		}
	}
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

void	loop_logic(t_game *game)
{
	double	fps_mult;

	fps_mult = get_fps_mult(game->mlx->delta_time, FPS);
	game->player.mov_speed = MOV_SPEED * fps_mult;
	game->player.rot_speed = ROT_SPEED * fps_mult;
	handle_action_keys(game->mlx, &game->player, game);
	handle_movement_keys(game->mlx, &game->player, &game->map);
	handle_mouse_movement(game->mlx, &game->player);
	mlx_key_hook(game->mlx, &handle_minimap_keys, game);
	handle_enemies(game->map.enemies, &game->map, &game->player, fps_mult);
	debug_print_player(&game->player);
	if (game->player.health <= 0)
		errexit_msg("You died. Exiting program.");
}
