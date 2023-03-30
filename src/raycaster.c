/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:01:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/30 16:11:48 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include "../libraries/libft/src/libft/libft.h" // ft_putstr_fd
#include <math.h> // cos, sin, tan
#include <stdio.h> // @note remove
#include <stdbool.h> // bool
#include <float.h> // DBL_MAX

#define UNIT 1.0f

static void	init_ray(t_ray *ray, double x, double y, double ray_dir)
{
	ray->angle = ray_dir;
	ray->dir.x = sin(ray_dir);
	ray->dir.y = cos(ray_dir);
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


static void	extend_ray(t_ray *ray, t_map *map, t_game *game)
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
		ray->length.y -= ray->hypotenuse.y;
	else
		ray->length.x -= ray->hypotenuse.x;
}

static void	set_hit_offset(bool	y_side, t_rayhit *hit, t_ray *ray)
{
	if (y_side)
		hit->offset = get_x_offset(ray);
	else
		hit->offset = get_y_offset(ray);
}

static void	set_cardinal(bool y_side, t_coor *step, t_rayhit *hit)
{
	if (y_side)
	{
		if (step->y < 0)
			hit->tex = SOUTH;
		else
			hit->tex = NORTH;
	}
	else
	{
		if (step->x < 0)
			hit->tex = WEST;
		else
			hit->tex = EAST;
	}
}

t_rayhit	cast_ray(t_game *game, double ray_dir)
{
	t_ray			ray;
	t_rayhit		hit;

	init_ray(&ray, game->player.x, game->player.y, ray_dir);
	extend_ray(&ray, &game->map, game);
	set_cardinal(ray.y_side, &ray.step, &hit);
	set_hit_offset(ray.y_side, &hit, &ray);
	debug_print_ray(&ray, &hit);
	return (hit);
}
