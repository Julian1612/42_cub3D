/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 01:18:00 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/15 00:53:33 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game
#include "../libraries/mlx42/include/MLX42/MLX42.h" // MLX_functions
#include <stdio.h> // @note remove
#include <math.h> // cos, sin
#include <stdbool.h> // bool

#define PLAYER_SIZE 0.2
#define SPRITE_SIZE_SQ 0.25

static bool	is_non_permeable(char c)
{
	if (c == WALL)
		return (true);
	return (false);
}

static bool	is_wall(double x, double y, char **map)
{
	if (x - PLAYER_SIZE < 0)
		x = PLAYER_SIZE;
	if (y - PLAYER_SIZE < 0)
		y = PLAYER_SIZE;
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

bool	collision_is_true(double x, double y, t_map *map)
{
	if (is_wall(x, y, map->arr))
		return (true);
	return (false);
}
