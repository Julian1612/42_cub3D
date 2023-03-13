/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:41:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/14 00:22:53 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include <math.h> // cos, sin, tan
#include <stdio.h> // @note remove
#include <stdbool.h> // bool

// @note angle (ray_dir) is known
// @note this function calculates the adjacent side of a triangle
// @note adjacent side = y distance to the next longitude
double	get_nearest_longitude(double coor_y, double ray_dir)
{
	double	nearest;

	// @note why sin?
	if (sin(ray_dir) >= 0)
		nearest = BLOCK_SIZE - fmod(coor_y, BLOCK_SIZE);
	else
		nearest = fmod(coor_y, BLOCK_SIZE) * -1;
	return (nearest);
}

// @note angle (ray_dir) is known
// @note this function calculates the adjacent side of a triangle
// @note adjacent side = x distance to the next latitude
double	get_nearest_latitude(double coor_x, double ray_dir)
{
	double	nearest;

	// @note why cos?
	if (cos(ray_dir) >= 0)
		nearest = (BLOCK_SIZE - fmod(coor_x, BLOCK_SIZE)) * -1;
	else
		nearest = fmod(coor_x, BLOCK_SIZE);
	return (nearest);
}

// @note angle (ray_dir) is known, adjacent side is known
// @note formula: adjacent side * tan(angle) = opposite side of triangle
int	get_triangle_opposite(double adjacent, double ray_dir)
{
	double	opposite;

	opposite = adjacent * tan(ray_dir) * -1;
	return (opposite);
}

bool	is_wall(char **map, double x, double y)
{
	int		map_x;
	int		map_y;

	if (x > 16 * BLOCK_SIZE || x < 0)
		return (true);
	if (y > 9 * BLOCK_SIZE || y < 0)
		return (true);
	map_x = (int)(x / BLOCK_SIZE);
	map_y = (int)(y / BLOCK_SIZE);
	if (map[map_y][map_x] == WALL)
		return (true);
	return (false);
}

// @note returns the distance to the next wall (ray length)
double	cast_ray(t_game *game, double ray_dir)
{
	t_ray	ray;
	double	ray_length_long;
	double	ray_length_lat;

	ray.dir = ray_dir;
	ray.nx_latitude.y = get_nearest_latitude(game->player.y, ray_dir);
	ray.nx_latitude.x = get_triangle_opposite(ray.nx_latitude.y, ray_dir);
	ray.nx_longitude.x = get_nearest_longitude(game->player.x, ray_dir);
	// @note why do I have to add M_PI_2 to the ray_dir?
	ray.nx_longitude.y = get_triangle_opposite(ray.nx_longitude.x, ray_dir + M_PI_2);
	debug_print_ray(&ray);
	while (!is_wall(game->map.map, game->player.y + ray.nx_latitude.y, game->player.x + ray.nx_latitude.x) &&
		!is_wall(game->map.map, game->player.y + ray.nx_longitude.y, game->player.x + ray.nx_longitude.x))
	{
		if (ray.nx_latitude.y >= 0)
			ray.nx_latitude.y += ray.nx_latitude.y;
		else
			ray.nx_latitude.y -= ray.nx_latitude.y;
		if (ray.nx_latitude.x >= 0)
			ray.nx_latitude.x += ray.nx_latitude.x;
		else
			ray.nx_latitude.x -= ray.nx_latitude.x;
		if (ray.nx_longitude.y >= 0)
			ray.nx_longitude.y += ray.nx_longitude.y;
		else
			ray.nx_longitude.y -= ray.nx_longitude.y;
		if (ray.nx_longitude.x >= 0)
			ray.nx_longitude.x += ray.nx_longitude.x;
		else
			ray.nx_longitude.x -= ray.nx_longitude.x;
	}
	if (is_wall(game->map.map, game->player.y + ray.nx_longitude.y, game->player.x + ray.nx_longitude.x))
	{
		ray_length_long = sqrt((ray.nx_longitude.x * ray.nx_longitude.x) + (ray.nx_longitude.y * ray.nx_longitude.y));
		// if (ray_length_long < ray_length_lat)
			return (ray_length_long);
	}
	if (is_wall(game->map.map, game->player.y + ray.nx_latitude.y, game->player.x + ray.nx_latitude.x))
	{
		ray_length_lat = sqrt((ray.nx_latitude.x * ray.nx_latitude.x) + (ray.nx_latitude.y * ray.nx_latitude.y));
		return (ray_length_lat);
	}
	return (0);
}
