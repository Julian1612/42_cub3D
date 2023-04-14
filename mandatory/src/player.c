/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:50:14 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 23:20:30 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h" // t_player
#include "raycast.h" // raycast_cast_ray
#include "cub3D.h" // sound
#include <string.h> // NULL
#include <math.h> // cos, sin

void	player_move(t_vec *pos, t_map *map, double x_offset, double y_offset)
{
	if (!collision_is_true(pos->x + x_offset, pos->y, map))
		pos->x += x_offset;
	if (!collision_is_true(pos->x, pos->y + y_offset, map))
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
