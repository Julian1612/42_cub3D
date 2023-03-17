/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:41:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/17 14:52:29 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include "../libraries/libft/src/libft/libft.h" // ft_putstr_fd
#include <math.h> // cos, sin, tan
#include <stdio.h> // @note remove
#include <stdbool.h> // bool

// @note angle (ray_dir) is known
// @note this function calculates the adjacent side of a triangle
// @note adjacent side = y distance to the next longitude
double	get_nearest_longitude(double coor_x, double ray_dir)
{
	double	nearest;

	if (cos(ray_dir) >= 0)
		nearest = fmod(coor_x, 1);
	else
		nearest = (1 - fmod(coor_x, 1)) * -1;
	return (nearest);
}

// @note angle (ray_dir) is known
// @note this function calculates the adjacent side of a triangle
// @note adjacent side = x distance to the next latitude
double	get_nearest_latitude(double coor_y, double ray_dir)
{
	double	nearest;

	if (sin(ray_dir) >= 0)
		nearest = fmod(coor_y, 1);
	else
		nearest = (1 - fmod(coor_y, 1)) * -1;
	return (nearest);
}

// @note angle (ray_dir) is known, adjacent side is known
// @note formula: adjacent side * tan(angle) = opposite side of triangle
double	get_y_from_x(double x, double ray_dir)
{
	double	opposite;

	opposite = x * tan(ray_dir) * -1;
	return (opposite);
}

double	get_x_from_y(double y, double ray_dir)
{
	double	opposite;

	y *= -1;
	opposite = y / tan(ray_dir);
	return (opposite);
}

// @todo remove checks later
bool	is_wall(t_map *map, double x, double y)
{
	if (y < 0 || x < 0)
		return (true);
	if (y > map->height)
		return (true);
	if (x > ft_strlen(map->map[(int)y]))
		return (true);
	if (map->map[(int)y][(int)x] == WALL)
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

// @todo remove BLOCK_SIZE from calculations
void	init_ray(t_ray	*ray, double ray_dir, t_player *player)
{
	ray->dir = ray_dir;
	ray->longitude.x = get_nearest_longitude(player->x / MM_BLOCK_SIZE, ray_dir);
	ray->longitude.y = get_y_from_x(ray->longitude.x, ray_dir);
	ray->latitude.x = get_x_from_y(get_nearest_latitude(player->y / MM_BLOCK_SIZE, ray_dir), ray_dir);
	ray->latitude.y = get_nearest_latitude(player->y / MM_BLOCK_SIZE, ray_dir);
	ray->lat_len = 1000000;
	ray->long_len = 1000000;
}

double	extend_until_wall(t_map *map, t_player *player, double ray_x, double ray_y, double ray_dir)
{
	double	add;
	double	new_x;
	double	new_y;

	add = get_x_from_y(1, ray_dir);
	new_x = player->x / MM_BLOCK_SIZE + ray_x;
	new_y = player->y / MM_BLOCK_SIZE + ray_y;
	// while (!is_wall(map, new_x, new_y))
	// {
	// 	ray_x = add_preserve_sign(ray_x, 1);
	// 	ray_y += add;
	// 	new_x = player->x / MM_BLOCK_SIZE + ray_x;
	// 	new_y = player->y / MM_BLOCK_SIZE + ray_y;
	// }
	return (sqrt(get_abs(ray_x * ray_x) + get_abs(ray_y * ray_y)));
}

double	cast_ray(t_game *game, double ray_dir)
{
	t_ray	ray;

	init_ray(&ray, ray_dir, &game->player);
	ray.long_len = extend_until_wall(&game->map, &game->player, ray.longitude.x, ray.longitude.y, ray_dir);
	ray.lat_len = extend_until_wall(&game->map, &game->player, ray.latitude.x, ray.latitude.y, ray_dir);
	debug_print_ray(&ray);
	if (ray.lat_len < ray.long_len)
		return (ray.lat_len);
	else
		return (ray.long_len);
}
