/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 01:18:00 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/12 19:00:25 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h" // t_enemy
#include "cub3D.h" // t_game
#include "../libraries/mlx/include/MLX42/MLX42.h" // MLX_functions
#include <stdio.h> // @note remove
#include <math.h> // cos, sin
#include <stdbool.h> // bool

#define PLAYER_SIZE 0.2
#define SPRITE_SIZE_SQ 0.25

static bool	is_non_permeable(char c)
{
	if (c == WALL || c == DOOR_CLOSED)
		return (true);
	return (false);
}

static bool	is_wall(double x, double y, char **map)
{
	if (is_non_permeable(map[(int)(y + PLAYER_SIZE)][(int)(x)]) == true)
		return (true);
	if (is_non_permeable(map[(int)(y - PLAYER_SIZE)][(int)(x)]) == true)
		return (true);
	if (is_non_permeable(map[(int)(y)][(int)(x + PLAYER_SIZE)]) == true)
		return (true);
	if (is_non_permeable(map[(int)(y)][(int)(x - PLAYER_SIZE)]) == true)
		return (true);
	if (is_non_permeable(map[(int)(y + PLAYER_SIZE)]
		[(int)(x + PLAYER_SIZE)]) == true)
		return (true);
	if (is_non_permeable(map[(int)(y - PLAYER_SIZE)]
		[(int)(x - PLAYER_SIZE)]) == true)
		return (true);
	if (is_non_permeable(map[(int)(y - PLAYER_SIZE)]
		[(int)(x + PLAYER_SIZE)]) == true)
		return (true);
	if (is_non_permeable(map[(int)(y + PLAYER_SIZE)]
		[(int)(x - PLAYER_SIZE)]) == true)
		return (true);
	return (false);
}

// @todo (problem: Permutability?) change to regular 
// block collision (use map identifiers) after merge
static bool	is_sprite(double x, double y, t_object *objects, int obj_count)
{
	int		i;
	double	dist_x;
	double	dist_y;

	i = -1;
	while (i++ < obj_count)
	{
		if (objects[i].type != DECOR_NON_PERM)
			continue ;
		dist_x = x - objects[i].pos.x;
		dist_y = y - objects[i].pos.y;
		if (dist_x * dist_x + dist_y * dist_y < SPRITE_SIZE_SQ)
			return (true);
	}
	return (false);
}

// returns the index of the enemy that is in the way, NOT_SET if none
int	collision_is_enemy(double x, double y, t_map *map, int enemy_num)
{
	int		i;
	double	dist_x;
	double	dist_y;

	i = NOT_SET;
	while (i++ < map->enemy_count)
	{
		if (i == enemy_num || map->enemies[i].health <= 0)
			continue ;
		dist_x = x - map->enemies[i].pos.x;
		dist_y = y - map->enemies[i].pos.y;
		if (dist_x * dist_x + dist_y * dist_y < SPRITE_SIZE_SQ)
			return (i);
	}
	return (NOT_SET);
}

bool	collision_is_true(double x, double y, t_map *map, int enemy_num)
{
	if (is_wall(x, y, map->arr))
		return (true);
	if (is_sprite(x, y, map->objects, map->obj_count))
		return (true);
	if (collision_is_enemy(x, y, map, enemy_num) != NOT_SET)
		return (true);
	return (false);
}
