/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:01:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/13 16:28:55 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_raycast.h" // t_ray
#include "../raycast.h" // t_rayhit
#include "../cub3D.h" // cub3D structs
#include "../debug.h" // debug_print_ray
#include <stdbool.h> // bool

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

void	raycast_cast_ray(
	t_rayhit *hit, t_game *game, t_vec ray_dir, char target)
{
	t_ray	ray;

	ray_init(&ray, &game->player.pos, &ray_dir);
	rayhit_init(hit);
	rayhit_set_type(hit, &ray, &game->map, target);
	while (hit->hit == NOT_SET)
	{
		extend_ray(&ray);
		rayhit_set_type(hit, &ray, &game->map, target);
	}
	ray_set_distance(hit, &ray, ray.y_side);
	rayhit_set_tex_id(hit, ray.y_side, &ray.step);
	rayhit_set_offset(hit, ray.y_side, &ray);
}
