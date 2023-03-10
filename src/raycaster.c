/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 14:41:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/10 22:27:13 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs

int	get_nearest_intersection(int position)
{
	return (BLOCK_SIZE - position % BLOCK_SIZE);
}

int	cast_ray(t_game *game, float ray_dir)
{
	t_ray	ray;

	ray.dir = ray_dir;
	ray.nearest_x = get_nearest_intersection(game->player.x);
	ray.nearest_y = get_nearest_intersection(game->player.y);
	debug_print_ray(&ray);
	return (SUCCESS);
}
