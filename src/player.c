/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:50:14 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/13 14:30:22 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h" // t_player
#include "raycast.h" // raycast_cast_ray
#include <string.h> // NULL
#include <math.h> // cos, sin

void	player_shoot(t_player *player, t_enemy *enemies, t_game *game)
{
	t_rayhit	hit;

	if (player->weapon == NULL)
		return ;
	if (is_next_frame(&player->weapon->last_frame_time) == true)
	{
		player->weapon->curr_frame++;
		if (player->weapon->curr_frame > GUN6)
			player->weapon->curr_frame = GUN3;
	}
	raycast_cast_ray(&hit, game, player->dir, ENEMY);
	if (hit.enemy_index != NOT_SET)
	{
		if (enemies[hit.enemy_index].health > 0)
			enemies[hit.enemy_index].health -= player->weapon->damage;
	}
}

void	player_move(t_vec *pos, t_map *map, double x_offset, double y_offset)
{
	if (!collision_is_true(pos->x + x_offset, pos->y, map, NOT_SET))
		pos->x += x_offset;
	if (!collision_is_true(pos->x, pos->y + y_offset, map, NOT_SET))
		pos->y += y_offset;
}

// negative rot_speed for left rotation
void	player_rotate(t_player *player, double rot_speed)
{
	double	temp;

	temp = player->dir.x;
	player->dir.x = temp * cos(rot_speed) - player->dir.y * sin(rot_speed);
	player->dir.y = temp * sin(rot_speed) + player->dir.y * cos(rot_speed);
	temp = player->cplane.x;
	player->cplane.x = temp * cos(rot_speed)
		- player->cplane.y * sin(rot_speed);
	player->cplane.y = temp * sin(rot_speed)
		+ player->cplane.y * cos(rot_speed);
}
