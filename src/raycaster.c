/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:41:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/12 18:11:50 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include <math.h> // cos, sin, tan
#include <stdio.h> // @note remove
#include <stdbool.h> // bool

double	get_nearest_intersection_y(double coor_y, double ray_dir)
{
	double	nearest;

	if (sin(ray_dir) >= 0)
		nearest = fmod(coor_y, BLOCK_SIZE);
	else
		nearest = BLOCK_SIZE - fmod(coor_y, BLOCK_SIZE);
	return (nearest);
}

double	get_nearest_intersection_x(double coor_x, double ray_dir)
{
	double	nearest;

	if (cos(ray_dir) >= 0)
		nearest = BLOCK_SIZE - fmod(coor_x, BLOCK_SIZE);
	else
		nearest = fmod(coor_x, BLOCK_SIZE);
	return (nearest);
}

int	get_opposite_length(double nearest, double ray_dir)
{
	double	opposite;

	opposite = nearest / tan(ray_dir);
	return (opposite);
}

int	cast_ray(t_game *game, double ray_dir)
{
	t_ray	ray;

	ray.dir = ray_dir;
	ray.nx_longitude.y = get_nearest_intersection_y(game->player.y, ray_dir);
	ray.nx_longitude.x = get_opposite_length(ray.nx_longitude.y, ray_dir);
	ray.nx_latitude.x = get_nearest_intersection_x(game->player.x, ray_dir);
	ray.nx_latitude.y = get_opposite_length(ray.nx_latitude.x, ray_dir);
	debug_print_ray(&ray);
	return (SUCCESS);
}
