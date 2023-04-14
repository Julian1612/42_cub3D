/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 01:18:00 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/15 00:14:04 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "enemy.h" // t_enemy
#include "cub3D.h" // t_game
#include "../libraries/mlx/include/MLX42/MLX42.h" // MLX_functions
#include "../libraries/libft/src/libft/libft.h" // ft_strlen
#include <stdio.h> // @note remove
#include <math.h> // cos, sin
#include <stdbool.h> // bool

#define ENTITY_SIZE 0.2
#define ENTITY_SIZE_SQ 0.25

static bool	is_non_permeable(char c)
{
	if (c == WALL || c == DOOR_CLOSED)
		return (true);
	return (false);
}

static bool	is_wall(double x, double y, char **map)
{
	if (ft_strlen(map[(int)(y)]) <= x)
		return (true);
	if (is_non_permeable(map[(int)(y + ENTITY_SIZE)][(int)(x)]) == true)
		return (true);
	if (is_non_permeable(map[(int)(y - ENTITY_SIZE)][(int)(x)]) == true)
		return (true);
	if (is_non_permeable(map[(int)(y)][(int)(x + ENTITY_SIZE)]) == true)
		return (true);
	if (is_non_permeable(map[(int)(y)][(int)(x - ENTITY_SIZE)]) == true)
		return (true);
	if (is_non_permeable(map[(int)(y + ENTITY_SIZE)]
		[(int)(x + ENTITY_SIZE)]) == true)
		return (true);
	if (is_non_permeable(map[(int)(y - ENTITY_SIZE)]
		[(int)(x - ENTITY_SIZE)]) == true)
		return (true);
	if (is_non_permeable(map[(int)(y - ENTITY_SIZE)]
		[(int)(x + ENTITY_SIZE)]) == true)
		return (true);
	if (is_non_permeable(map[(int)(y + ENTITY_SIZE)]
		[(int)(x - ENTITY_SIZE)]) == true)
		return (true);
	return (false);
}

// returns the index of the enemy that is in the way, NOT_SET if none
int	collision_is_enemy(double x, double y, t_map *map, int enemy_num)
{
	int		i;
	double	dist_x;
	double	dist_y;

	if (map->enemy_count == 0)
		return (NOT_SET);
	i = NOT_SET;
	while (i++ < map->enemy_count - 1)
	{
		if (i == enemy_num || map->enemies[i].health <= 0)
			continue ;
		dist_x = x - map->enemies[i].pos.x;
		dist_y = y - map->enemies[i].pos.y;
		if (dist_x * dist_x + dist_y * dist_y < ENTITY_SIZE_SQ)
			return (i);
	}
	return (NOT_SET);
}

bool	collision_is_true(double x, double y, t_map *map, int enemy_num)
{
	if (is_wall(x, y, map->arr))
		return (true);
	if (collision_is_enemy(x, y, map, enemy_num) != NOT_SET)
		return (true);
	return (false);
}
