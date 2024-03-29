/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic_door.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 18:27:04 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 09:22:43 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h" // t_game
#include "../raycast.h" // raycast_cast_ray, t_rayhit
#include "../types.h" // t_rayhit, tex enum
#include <stdbool.h> // bool

#define DOOR_COOLDOWN 0.2
#define PLAYER_REACH 2.0

static bool	switch_bool(bool b)
{
	if (b == true)
		return (false);
	return (true);
}

static enum e_tex_id	switch_state(enum e_tex_id state, int *sound_id)
{
	sound_play(&sound_id[SOUND_DOOR], "./sounds/door.mp3",
		"afplay ./sounds/door.mp3 &");
	if (state == DOOR_CLOSED)
		return (DOOR_OPEN);
	else
		return (DOOR_CLOSED);
}

void	handle_door(t_game *game, t_player *player)
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
				game->map.arr[game->map.doors[i].y][game->map.doors[i].x]
					= switch_state(game->map.arr[game->map.doors[i].y]
					[game->map.doors[i].x], game->sound_id);
				game->map.doors[i].open = switch_bool(game->map.doors[i].open);
			}
			game->map.doors[i].last_action = mlx_get_time();
		}
		i++;
	}
}
