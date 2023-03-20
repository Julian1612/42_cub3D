/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:41:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/20 13:18:58 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include "../libraries/libft/src/libft/libft.h" // ft_putstr_fd
#include <math.h> // cos, sin, tan
#include <stdio.h> // @note remove
#include <stdbool.h> // bool

#define UNIT 1

// @note angle (ray_dir) is known
// @note this function calculates the adjacent side of a triangle
// @note adjacent side = y distance to the next longitude
double	get_nearest_longitude(double coor_x, double ray_dir)
{
	double	nearest;

	if (sin(ray_dir) >= 0)
		nearest = UNIT - fmod(coor_x, UNIT);
	else
		nearest = fmod(coor_x, UNIT) * -1;
	return (nearest);
}

// @note angle (ray_dir) is known
// @note this function calculates the adjacent side of a triangle
// @note adjacent side = x distance to the next latitude
double	get_nearest_latitude(double coor_y, double ray_dir)
{
	double	nearest;

	if (cos(ray_dir) >= 0)
		nearest = UNIT - fmod(coor_y, UNIT);
	else
		nearest = fmod(coor_y, UNIT) * -1;
	return (nearest);
}

// @note angle (ray_dir) is known, adjacent side is known
// @note formula: adjacent side * tan(angle) = opposite side of triangle
double	get_y_from_x(double x, double ray_dir)
{
	double	y;

	y = x / tan(ray_dir);
	return (y);
}

double	get_x_from_y(double y, double ray_dir)
{
	double	x;

	// y *= -1;
	x = y * tan(ray_dir);
	return (x);
}

// @todo remove checks later
bool	is_wall(t_map *map, double x, double y)
{
	// printf("x: %f, y: %f\n", x, y);
	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
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

// @todo remove MM_BLOCK_SIZE from calculations
void	init_ray(t_ray	*ray, double ray_dir, t_player *player)
{
	ray->dir = ray_dir;
	ray->longitude.x = get_nearest_longitude(player->x / MM_BLOCK_SIZE, ray_dir);
	ray->longitude.y = get_y_from_x(ray->longitude.x, ray_dir);
	ray->latitude.y = get_nearest_latitude(player->y / MM_BLOCK_SIZE, ray_dir);
	ray->latitude.x = get_x_from_y(ray->latitude.y, ray_dir);
	ray->lat_len = 1000000;
	ray->long_len = 1000000;
}

void	set_transparent(mlx_image_t *image)
{
	int		i;
	int		j;
	int		color;

	i = 0;
	while (i < image->width)
	{
		j = 0;
		while (j < image->height)
		{
			mlx_put_pixel(image, i, j, convert_to_hexcode(0, 0, 0, 0));
			j++;
		}
		i++;
	}
}

double	extend_until_wall_long(mlx_image_t *image, t_map *map, t_player *player, double ray_x, double ray_y, double ray_dir)
{
	double	add;
	double	new_x;
	double	new_y;
	double	player_x;
	double	player_y;

	player_x = player->x / MM_BLOCK_SIZE;
	player_y = player->y / MM_BLOCK_SIZE;
	new_x = player_x + ray_x;
	new_y = player_y + ray_y;
	while (!is_wall(map, new_x, new_y))
	{
		ray_x = add_preserve_sign(ray_x, UNIT);
		if (ray_x >= 0)
			ray_y += get_y_from_x(UNIT, ray_dir);
		else
			ray_y -= get_y_from_x(UNIT, ray_dir);
		// printf("ray_y: %f\n", ray_y);
		new_x = player_x + ray_x;
		// printf("new_x: %f\n", new_x);
		new_y = player_y + ray_y;
		// printf("new_y: %f\n", new_y);
		if (new_x >= 0 && new_y >= 0 && new_x * MM_BLOCK_SIZE < image->width && new_y * MM_BLOCK_SIZE < image->height)
			mlx_put_pixel(image, new_x * MM_BLOCK_SIZE, new_y * MM_BLOCK_SIZE, convert_to_hexcode(0, 255, 0, 255));
	}
	if (ray_x < 0)
	{
		ray_x += UNIT;
		ray_y += get_y_from_x(UNIT, ray_dir);
	}
	return (sqrt(get_abs(ray_x * ray_x) + get_abs(ray_y * ray_y)));
}

double	extend_until_wall_lat(mlx_image_t *image, t_map *map, t_player *player, double ray_x, double ray_y, double ray_dir)
{
	double	add;
	double	new_x;
	double	new_y;
	double	player_x;
	double	player_y;

	player_x = player->x / MM_BLOCK_SIZE;
	player_y = player->y / MM_BLOCK_SIZE;
	new_x = player_x + ray_x;
	new_y = player_y + ray_y;
	while (!is_wall(map, new_x, new_y))
	{
		ray_y = add_preserve_sign(ray_y, UNIT);
		if (ray_y >= 0)
			ray_x += get_x_from_y(UNIT, ray_dir);
		else
			ray_x -= get_x_from_y(UNIT, ray_dir);
		// printf("ray_x: %f\n", ray_x);
		new_x = player_x + ray_x;
		new_y = player_y + ray_y;
		if (new_x >= 0 && new_y >= 0 && new_x * MM_BLOCK_SIZE < image->width && new_y * MM_BLOCK_SIZE < image->height)
			mlx_put_pixel(image, new_x * MM_BLOCK_SIZE, new_y * MM_BLOCK_SIZE, convert_to_hexcode(255, 0, 0, 255));
	}
	if (ray_y < 0)
	{
		ray_y += UNIT;
		ray_x += get_x_from_y(UNIT, ray_dir);
	}
	return (sqrt(get_abs(ray_x * ray_x) + get_abs(ray_y * ray_y)));
}

// @todo add parameter for collision object
double	cast_ray(t_game *game, double ray_dir)
{
	t_ray	ray;

	init_ray(&ray, ray_dir, &game->player);
	set_transparent(game->img_a);
	ray.long_len = extend_until_wall_long(game->img_a, &game->map, &game->player, ray.longitude.x, ray.longitude.y, ray_dir);
	ray.lat_len = extend_until_wall_lat(game->img_a, &game->map, &game->player, ray.latitude.x, ray.latitude.y, ray_dir);
	debug_print_ray(&ray);
	if (ray.lat_len < ray.long_len)
		return (ray.lat_len);
	else
		return (ray.long_len);
}
