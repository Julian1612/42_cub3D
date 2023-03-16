/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:41:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/16 18:23:40 by lorbke           ###   ########.fr       */
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
		nearest = (BLOCK_SIZE - fmod(coor_x, BLOCK_SIZE));
	else
		nearest = fmod(coor_x, BLOCK_SIZE) * -1;
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

bool	is_wall(t_map *map, double x, double y)
{
	int		map_x;
	int		map_y;
	int		map_width;
	int		map_height;

	map_width = map->width - 1;
	map_height = map->height - 1;
	map_x = (int)(x / BLOCK_SIZE);
	map_y = (int)(y / BLOCK_SIZE);
	if (map_x > map->width - 1 || map_x < 0)
		return (true);
	if (map_y > map->height - 1 || map_y < 0)
		return (true);
	if (map->map[map_y][map_x] == WALL)
		return (true);
	return (false);
}

double	add_preserve_sign(double a, double b)
{
	if (a < 0)
		return (a - b);
	return (a + b);
}

double	get_abs(double a)
{
	if (a < 0)
		return (a * -1);
	return (a);
}

void	get_nearest(t_ray *ray, double ray_dir, t_player *player)
{
	ray->nx_latitude.y = get_nearest_latitude(player->y, ray_dir);
	ray->nx_latitude.x = get_triangle_opposite(ray->nx_latitude.y, ray_dir);
	ray->nx_longitude.x = get_nearest_longitude(player->x, ray_dir);
	// @note why do I have to add M_PI_2 to the ray_dir?
	ray->nx_longitude.y = get_triangle_opposite(ray->nx_longitude.x, ray_dir + M_PI_2);
}

// @note returns the distance to the next wall (ray length)
double	cast_ray(t_game *game, double ray_dir)
{
	t_ray	ray;
	double	ray_length_long;
	double	ray_length_lat;
	double	add;

	ray.dir = ray_dir;
	get_nearest(&ray, ray_dir, &game->player);
	ray_length_long = 1000000;
	ray_length_lat = 1000000;
	add = get_triangle_opposite(BLOCK_SIZE, ray_dir + M_PI_2);
	while (!is_wall(&game->map, game->player.x + ray.nx_longitude.x, game->player.y + ray.nx_longitude.y))
	{
		ray.nx_longitude.x = add_preserve_sign(ray.nx_longitude.x, BLOCK_SIZE);
		ray.nx_longitude.y += add;
	}
	add = get_triangle_opposite(BLOCK_SIZE, ray_dir);
	while (!is_wall(&game->map, game->player.x + ray.nx_latitude.x, game->player.y + ray.nx_latitude.y))
	{
		ray.nx_latitude.x += add;
		ray.nx_latitude.y = add_preserve_sign(ray.nx_latitude.y, BLOCK_SIZE);
	}
	ray_length_long = sqrt(get_abs(ray.nx_longitude.x * ray.nx_longitude.x) + get_abs(ray.nx_longitude.y * ray.nx_longitude.y));
	ray_length_lat = sqrt(get_abs(ray.nx_latitude.x * ray.nx_latitude.x) + get_abs(ray.nx_latitude.y * ray.nx_latitude.y));
	debug_print_ray(&ray, ray_length_lat, ray_length_long);
	if (ray_length_lat < ray_length_long)
		return (ray_length_lat);
	else
		return (ray_length_long);
}
