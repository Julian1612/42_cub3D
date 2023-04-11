/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:01:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/11 20:26:36 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include <math.h> // cos, sin, tan
#include <stdio.h> // @note remove
#include <stdbool.h> // bool
#include <float.h> // DBL_MAX

#define UNIT 1.0f

static void	init_ray(t_ray *ray, t_vec *pos, t_vec *ray_dir)
{
	ray->dir = *ray_dir;
	ray->angle = atan2(ray_dir->x, ray_dir->y);
	ray->origin = *pos;
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

static void	set_hit_type(t_rayhit *hit, t_ray *ray, t_map *map, char target)
{
	int	enemy_index;

	if (map->arr[ray->map_y][ray->map_x] == WALL)
		hit->hit = WALL;
	else if (map->arr[ray->map_y][ray->map_x] == DOOR_CLOSED)
		hit->hit = DOOR_CLOSED;
	else if (target == DOOR_OPEN && map->arr[ray->map_y][ray->map_x] == DOOR_OPEN)
		hit->hit = DOOR_OPEN;
	else if (target == ENEMY)
	{
		enemy_index = check_enemy_collision(ray->map_x + 0.5, ray->map_y + 0.5, map, NOT_SET);
		if (enemy_index != NOT_SET)
		{
			hit->hit = ENEMY;
			hit->enemy_index = enemy_index;
		}
	}
}

static void	extend_ray(t_ray *ray)
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

static void	set_hit_tex_id(t_rayhit *hit, bool y_side, t_vec *step)
{
	if (hit->hit == WALL)
	{
		if (y_side)
		{
			if (step->y < 0)
				hit->tex_id = SOUTH;
			else
				hit->tex_id = NORTH;
		}
		else
		{
			if (step->x < 0)
				hit->tex_id = WEST;
			else
				hit->tex_id = EAST;
		}
	}
	else if (hit->hit == DOOR_CLOSED)
		hit->tex_id = DOOR_FRONT;
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
		hit->x_offset = get_x_offset(ray);
	else
		hit->x_offset = get_y_offset(ray);
}

static void	init_hit(t_rayhit *hit)
{
	hit->tex_id = 0;
	hit->enemy_index = NOT_SET;
	hit->hit = NOT_SET;
}

static void	set_distance(t_rayhit *hit, t_ray *ray, bool y_side)
{
	if (y_side)
		hit->dist = ray->length.y - ray->hypotenuse.y;
	else
		hit->dist = ray->length.x - ray->hypotenuse.x;
}

void	cast_ray(t_rayhit *hit, t_game *game, t_vec ray_dir, char target)
{
	t_ray	ray;

	init_ray(&ray, &game->player.pos, &ray_dir);
	init_hit(hit);
	set_hit_type(hit, &ray, &game->map, target);
	while (hit->hit == NOT_SET)
	{
		extend_ray(&ray);
		set_hit_type(hit, &ray, &game->map, target);
	}
	set_distance(hit, &ray, ray.y_side);
	set_hit_tex_id(hit, ray.y_side, &ray.step);
	set_hit_offset(hit, ray.y_side, &ray);
	debug_print_ray(&ray, hit);
}
