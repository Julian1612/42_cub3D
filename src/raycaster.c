/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:41:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/11 00:10:34 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include <math.h> // cos, sin, tan

double	get_nearest_intersection_y(int coor_y, double ray_dir)
{
	double	nearest;

	// if (cos(ray_dir) > 0)
		nearest = BLOCK_SIZE - coor_y % BLOCK_SIZE;
	// else
		// nearest = coor_y % BLOCK_SIZE;
	return (nearest);
}

double	get_nearest_intersection_x(int coor_x, double ray_dir)
{
	double	nearest;

	// if (sin(ray_dir) > 0)
		nearest = BLOCK_SIZE - coor_x % BLOCK_SIZE;
	// else
		// nearest = coor_x % BLOCK_SIZE;
	return (nearest);
}

double	get_opposite_length(double adjacent, double angle)
{
	double	opposite;

	opposite = tan(angle) * adjacent;
	return (opposite);
}

int	cast_ray(t_game *game, double ray_dir)
{
	t_ray	ray;

	ray.dir = ray_dir;
	ray.nearest_y = get_nearest_intersection_y(game->player.y, ray_dir);
	ray.nearest_x = get_nearest_intersection_x(game->player.x, ray_dir);
	ray.nearest_x = get_opposite_length(ray_dir, ray.nearest_x);
	debug_print_ray(&ray);
	return (SUCCESS);
}
