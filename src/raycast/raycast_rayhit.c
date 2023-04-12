/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_rayhit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:09:28 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/12 13:52:44 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycast.h" // t_rayhit
#include "private_raycast.h" // t_ray
#include "../cub3D.h" // cub3D structs and defines

void	rayhit_set_type(t_rayhit *hit, t_ray *ray, t_map *map, char target)
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
		enemy_index = collision_is_enemy(ray->map_x + 0.5, ray->map_y + 0.5, map, NOT_SET);
		if (enemy_index != NOT_SET)
		{
			hit->hit = ENEMY;
			hit->enemy_index = enemy_index;
		}
	}
}

void	rayhit_set_tex_id(t_rayhit *hit, bool y_side, t_vec *step)
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

void	rayhit_set_offset(t_rayhit *hit, bool y_side, t_ray *ray)
{
	if (y_side)
		hit->x_offset = ray_get_x_offset(ray);
	else
		hit->x_offset = ray_get_y_offset(ray);
}

void	rayhit_init(t_rayhit *hit)
{
	hit->tex_id = 0;
	hit->enemy_index = NOT_SET;
	hit->hit = NOT_SET;
}
