
#include "cub3D.h" // t_game
#include "../libraries/mlx/include/MLX42/MLX42.h" // MLX_functions
#include <stdio.h> // @note remove
#include <math.h> // cos, sin
#include <stdbool.h> // bool

#define PLAYER_SIZE 0.2
#define SPRITE_SIZE_SQ 0.25

static bool	check_wall_collision(double x, double y, char **map)
{
	if (map[(int)(y + PLAYER_SIZE)][(int)(x)] == WALL)
		return (true);
	if (map[(int)(y - PLAYER_SIZE)][(int)(x)] == WALL)
		return (true);
	if (map[(int)(y)][(int)(x + PLAYER_SIZE)] == WALL)
		return (true);
	if (map[(int)(y)][(int)(x - PLAYER_SIZE)] == WALL)
		return (true);
	if (map[(int)(y - PLAYER_SIZE)][(int)(x - PLAYER_SIZE)] == WALL)
		return (true);
	if (map[(int)(y + PLAYER_SIZE)][(int)(x + PLAYER_SIZE)] == WALL)
		return (true);
	if (map[(int)(y - PLAYER_SIZE)][(int)(x + PLAYER_SIZE)] == WALL)
		return (true);
	if (map[(int)(y + PLAYER_SIZE)][(int)(x - PLAYER_SIZE)] == WALL)
		return (true);
	return (false);
}

static bool	check_sprite_collision(double x, double y, t_object *objects, int obj_count)
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

// @note function usable for enemies?
// @note can this be done less computationally expensive?
bool	check_collision(double x, double y, t_map *map)
{
	if (check_wall_collision(x, y, map->arr))
		return (true);
	if (check_sprite_collision(x, y, map->objects, map->obj_count))
		return (true);
	return (false);
}
