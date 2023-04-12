/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_ray.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:01:58 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/12 14:02:37 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_raycast.h" // t_ray
#include "../cub3D.h" // cub3D structs
#include <math.h> // math funcs
#include <stdbool.h> // bool

#define UNIT 1.0f

void	ray_set_distance(t_rayhit *hit, t_ray *ray, bool y_side)
{
	if (y_side)
		hit->dist = ray->length.y - ray->hypotenuse.y;
	else
		hit->dist = ray->length.x - ray->hypotenuse.x;
}

double	ray_get_y_offset(t_ray *ray)
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

double	ray_get_x_offset(t_ray *ray)
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

void	ray_init(t_ray *ray, t_vec *pos, t_vec *ray_dir)
{
	ray->dir = *ray_dir;
	ray->angle = atan2(ray_dir->x, ray_dir->y);
	ray->origin = *pos;
	ray->map_x = (int)ray->origin.x;
	ray->map_y = (int)ray->origin.y;
	ray->hypotenuse.x = fabs(UNIT / ray->dir.x);
	ray->hypotenuse.y = fabs(UNIT / ray->dir.y);
	ray->step.x = UNIT;
	if (ray->dir.x < 0)
	{
		ray->step.x = -UNIT;
		ray->length.x = (ray->origin.x - ray->map_x) * ray->hypotenuse.x;
	}
	else
		ray->length.x = (ray->map_x + UNIT - ray->origin.x) * ray->hypotenuse.x;
	ray->step.y = UNIT;
	if (ray->dir.y < 0)
	{
		ray->step.y = -UNIT;
		ray->length.y = (ray->origin.y - ray->map_y) * ray->hypotenuse.y;
	}
	else
		ray->length.y = (ray->map_y + UNIT - ray->origin.y) * ray->hypotenuse.y;
}
