/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:01:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/01 18:36:05 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include "../libraries/libft/src/libft/libft.h" // ft_putstr_fd
#include <math.h> // cos, sin, tan
#include <stdio.h> // @note remove
#include <stdbool.h> // bool
#include <float.h> // DBL_MAX

#define UNIT 1.0f

static void	init_ray(t_ray *ray, double x, double y, t_coor ray_dir, double ray_angle)
{
	// ray->dir = ray_dir;
	ray->dir.y = cos(ray_angle);
	ray->dir.x = sin(ray_angle);
	ray->angle = ray_angle;
	ray->origin.x = x;
	ray->origin.y = y;
	ray->map_x = (int)ray->origin.x;
	ray->map_y = (int)ray->origin.y;
	// @note potential division by zero
	ray->hypotenuse.x = fabs(UNIT / ray->dir.x);
	ray->hypotenuse.y = fabs(UNIT / ray->dir.y);
	if (ray->dir.x < 0)
	{
		ray->step.x = -UNIT;
		ray->length.x = (ray->origin.x - ray->map_x) * ray->hypotenuse.x;
	}
	else
	{
		ray->step.x = UNIT;
		ray->length.x = (ray->map_x + UNIT - ray->origin.x) * ray->hypotenuse.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -UNIT;
		ray->length.y = (ray->origin.y - ray->map_y) * ray->hypotenuse.y;
	}
	else
	{
		ray->step.y = UNIT;
		ray->length.y = (ray->map_y + UNIT - ray->origin.y) * ray->hypotenuse.y;
	}
}

static void	set_distance(t_rayhit *hit, t_ray *ray, t_map *map)
{
	while (map->map[ray->map_y][ray->map_x] != WALL)
	{
		if (ray->length.x < ray->length.y)
		{
			ray->map_x += ray->step.x;
			ray->length.x += ray->hypotenuse.x;
			ray->y_side = false;
		}
		else
		{
			ray->map_y += ray->step.y;
			ray->length.y += ray->hypotenuse.y;
			ray->y_side = true;
		}
	}
	if (ray->y_side)
		hit->dist = ray->length.y - ray->hypotenuse.y;
	else
		hit->dist = ray->length.x - ray->hypotenuse.x;
}

static void	set_hit_wall_id(t_rayhit *hit, bool y_side, t_coor *step)
{
	if (y_side)
	{
		if (step->y < 0)
			hit->wall_id = SOUTH;
		else
			hit->wall_id = NORTH;
	}
	else
	{
		if (step->x < 0)
			hit->wall_id = WEST;
		else
			hit->wall_id = EAST;
	}
}

static double	get_y_offset(t_ray *ray)
{
	double	x_adjacent;
	double	y_opposite;

	if (ray->step.x < 0)
		x_adjacent = ray->map_x - ray->origin.x + UNIT;
	else
		x_adjacent = ray->map_x - ray->origin.x;
	y_opposite = x_adjacent / tan(ray->angle);
	return (fmod(y_opposite + ray->origin.y, UNIT));
}

static double	get_x_offset(t_ray *ray)
{
	double	y_adjacent;
	double	x_opposite;

	if (ray->step.y < 0)
		y_adjacent = ray->map_y - ray->origin.y + UNIT;
	else
		y_adjacent = ray->map_y - ray->origin.y;
	x_opposite = y_adjacent * tan(ray->angle);
	return (fmod(x_opposite + ray->origin.x, UNIT));
}

static void	set_hit_offset(t_rayhit *hit, bool y_side, t_ray *ray)
{
	if (y_side)
		hit->stripe = get_x_offset(ray);
	else
		hit->stripe = get_y_offset(ray);
}

void	cast_ray(t_rayhit *hit, t_game *game, t_coor ray_dir, double ray_angle)
{
	t_ray			ray;

	init_ray(&ray, game->player.x, game->player.y, ray_dir, ray_angle);
	set_distance(hit, &ray, &game->map);
	set_hit_wall_id(hit, ray.y_side, &ray.step);
	set_hit_offset(hit, ray.y_side, &ray);
	debug_print_ray(&ray, hit);
}
