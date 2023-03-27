/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:01:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/27 23:19:48 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include "../libraries/libft/src/libft/libft.h" // ft_putstr_fd
#include <math.h> // cos, sin, tan
#include <stdio.h> // @note remove
#include <stdbool.h> // bool
#include <float.h> // DBL_MAX

#include "../libraries/mlx/include/MLX42/MLX42.h" // @note remove

#define UNIT 1.0f

void	set_cardinal(t_map *map, t_ray *ray, bool side)
{
	if (side)
	{
		if (ray->step.y < 0)
			map->cardinal = &map->south;
		else
			map->cardinal = &map->north;
		map->adjacent_len = sqrt(pow(ray->map_y - ray->origin.y, 2)) / pow(ray->length.x, 2);
	}
	else
	{
		if (ray->step.x < 0)
			map->cardinal = &map->west;
		else
			map->cardinal = &map->east;
		map->adjacent_len = sqrt(pow(ray->map_x - ray->origin.x, 2)) / pow(ray->length.y, 2);
	}
}

void	init_ray(t_ray *ray, double x, double y, double ray_dir)
{
	ray->dir.x = sin(ray_dir);
	ray->dir.y = cos(ray_dir);
	ray->origin.x = x;
	ray->origin.y = y;
	ray->map_x = (int)ray->origin.x;
	ray->map_y = (int)ray->origin.y;
	// @note potential division by zero
	// @note genius math to get hypotenuse length to next intersection
	ray->hypotenuse.x = fabs(UNIT / ray->dir.x);
	ray->hypotenuse.y = fabs(UNIT / ray->dir.y);
	if (ray->dir.x < 0)
	{
		ray->step.x = -UNIT;
		ray->op_step.y = -UNIT / ray->dir.y;
		ray->length.x = (ray->origin.x - ray->map_x) * ray->hypotenuse.x;
	}
	else
	{
		ray->step.x = UNIT;
		ray->op_step.y = UNIT / ray->dir.y;
		ray->length.x = (ray->map_x + UNIT - ray->origin.x) * ray->hypotenuse.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -UNIT;
		ray->op_step.x = -UNIT / ray->dir.x;
		ray->length.y = (ray->origin.y - ray->map_y) * ray->hypotenuse.y;
	}
	else
	{
		ray->step.y = UNIT;
		ray->op_step.x = UNIT / ray->dir.x;
		ray->length.y = (ray->map_y + UNIT - ray->origin.y) * ray->hypotenuse.y;
	}
}

double	extend_ray(t_ray *ray, t_map *map)
{
	bool	side;

	while (map->map[ray->map_y][ray->map_x] != WALL)
	{
		if (ray->length.x < ray->length.y)
		{
			ray->map_x += ray->step.x;
			ray->length.x += ray->hypotenuse.x;
			side = false;
		}
		else
		{
			ray->map_y += ray->step.y;
			ray->length.y += ray->hypotenuse.y;
			side = true;
		}
	}
	set_cardinal(map, ray, side);
	if (side)
		return (ray->length.y - ray->hypotenuse.y);
	else
		return (ray->length.x - ray->hypotenuse.x);
}

double	cast_ray(t_game *game, double ray_dir)
{
	t_ray	ray;
	double	res;

	init_ray(&ray, game->player.x, game->player.y, ray_dir);
	res = extend_ray(&ray, &game->map);
	debug_print_ray(&ray);
	return (res);
}
