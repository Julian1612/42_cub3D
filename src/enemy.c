/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:55:13 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 03:23:07 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game
#include "types.h" // e_tex_id
#include "enemy.h" // t_enemy
#include "../libraries/mlx/include/MLX42/MLX42.h" // MLX_functions
#include <math.h> // cos, sin
#include <stdbool.h> // bool
#include <stdio.h> // @note remove

void	enemy_move(t_enemy *enemy, t_map *map, t_vec offset, int enemy_index)
{
	bool	coll_x;
	bool	coll_y;
	int		state;

	coll_x = collision_is_true(enemy->pos.x + offset.x,
			enemy->pos.y, map, enemy_index);
	coll_y = collision_is_true(enemy->pos.x,
			enemy->pos.y + offset.y, map, enemy_index);
	state = ZOMBIE_RUN1;
	if (coll_x == false && coll_y == false)
	{
		enemy->pos.x += offset.x;
		enemy->pos.y += offset.y;
	}
	else if (coll_x == false)
	{
		state = ZOMBIE_LEFT1;
		enemy->pos.x += offset.x * 2;
	}
	else if (coll_y == false)
	{
		state = ZOMBIE_RIGHT1;
		enemy->pos.y += offset.y * 2;
	}
	set_next_frame(&enemy->frame, state, 3);
}

void	enemy_attack(t_player *player, t_enemy *enemy)
{
	static int	cooldown = 0;

	if (cooldown == 0)
	{
		cooldown = mlx_get_time();
		player_take_damage(player, enemy->damage);
	}
	else if (mlx_get_time() - cooldown > 1)
	{
		cooldown = mlx_get_time();
		player_take_damage(player, enemy->damage);
	}
}

void	enemy_die(t_enemy *enemy)
{
	if (enemy->alive == false)
		return ;
	if (enemy->frame.curr < ZOMBIE_DEAD1)
		enemy->frame.curr = ZOMBIE_DEAD1;
	if (is_next_frame(&enemy->frame.time_of_last) == true)
	{
		enemy->frame.curr++;
		if (enemy->frame.curr > ZOMBIE_DEAD8)
		{
			enemy->alive = false;
			enemy->frame.curr = ZOMBIE_DEAD1;
		}
	}
}
