/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_rayhit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:09:28 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 23:15:43 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raycast.h" // t_rayhit
#include "private_raycast.h" // t_ray
#include "../cub3D.h" // cub3D structs and defines

void	rayhit_set_type(t_rayhit *hit, t_ray *ray, t_map *map)
{
	if (map->arr[ray->map_y][ray->map_x] == WALL)
		hit->hit = WALL;
}

void	rayhit_set_tex_id(t_rayhit *hit, bool y_side, t_vec *step)
{
	if (hit->hit == WALL)
	{
		if (y_side)
		{
			if (step->y < 0)
				hit->tex_id = WALL_SOUTH;
			else
				hit->tex_id = WALL_NORTH;
		}
		else
		{
			if (step->x < 0)
				hit->tex_id = WALL_WEST;
			else
				hit->tex_id = WALL_EAST;
		}
	}
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
