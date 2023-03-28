/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:01:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/28 18:44:38 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include "../libraries/libft/src/libft/libft.h" // ft_putstr_fd
#include <math.h> // cos, sin, tan
#include <stdio.h> // @note remove
#include <stdbool.h> // bool
#include <float.h> // DBL_MAX

#include "../libraries/mlx/include/MLX42/MLX42.h" // @note remove

#define UNIT 1.0f

void	set_cardinal(t_map *map, t_ray *ray, bool side)
{
	if (side)
	{
		if (ray->step.y < 0)
			map->cardinal = &map->south;
		else
			map->cardinal = &map->north;
		map->adjacent_len = sqrt(pow(ray->map_y - ray->origin.y, 2)) / pow(ray->length.x, 2);
	}
	else
	{
		if (ray->step.x < 0)
			map->cardinal = &map->west;
		else
			map->cardinal = &map->east;
		map->adjacent_len = sqrt(pow(ray->map_x - ray->origin.x, 2)) / pow(ray->length.y, 2);
	}
}

void	init_ray(t_ray *ray, double x, double y, double ray_dir)
{
	ray->angle = ray_dir;
	ray->dir.x = sin(ray_dir);
	ray->dir.y = cos(ray_dir);
	ray->origin.x = x / MM_BLOCK_SIZE;
	ray->origin.y = y / MM_BLOCK_SIZE;
	ray->map_x = (int)ray->origin.x;
	ray->map_y = (int)ray->origin.y;
	// @note potential division by zero
	// @note genius math to get hypotenuse length to next intersection
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

// ray hit coordinates / ray block offset
// ray->origin = origin coordinates
// x_length = ray->origin.x + map_x
// angle = ray->angle
// y offset = origin.y % UNIT
// y_length = x_length * ray->dir.y + y_offset
// y_offset = y_length % UNIT

double	get_y_offset(t_ray *ray)
{
	double	x_length;
	double	y_length;
	double	y_offset;

	x_length = fabs(ray->origin.x - ray->map_x);
	y_offset = fmod(ray->origin.y, ray->step.x);
	y_length = x_length / tan(ray->angle) + y_offset;
	// return (y_length);
	return (fmod(y_length, UNIT));
}

double	get_x_offset(t_ray *ray)
{
	double	y_length;
	double	x_length;
	double	x_offset;

	y_length = fabs(ray->origin.y - ray->map_y);
	x_offset = fmod(ray->origin.x, ray->step.y);
	x_length = y_length * tan(ray->angle) + x_offset;
	// return (x_length);
	return (fmod(x_length, UNIT));
}


double	extend_ray(t_ray *ray, t_map *map, t_game *game)
{
	bool	side;

	ray->op_step.x = 0;
	ray->op_step.y = 0;
	while (map->map[ray->map_y][ray->map_x] != WALL)
	{
		if (ray->length.x < ray->length.y)
		{
			ray->map_x += ray->step.x;
			ray->length.x += ray->hypotenuse.x;
			ray->op_step.y = get_y_offset(ray);
			mlx_put_pixel(game->img_a, ray->map_x * MM_BLOCK_SIZE, (ray->map_y + ray->op_step.y) * MM_BLOCK_SIZE, convert_to_hexcode(255, 0, 0, 255));
			side = false;
		}
		else
		{
			ray->map_y += ray->step.y;
			ray->length.y += ray->hypotenuse.y;
			ray->op_step.x = get_x_offset(ray);
			mlx_put_pixel(game->img_a, (ray->map_x + ray->op_step.x) * MM_BLOCK_SIZE, ray->map_y * MM_BLOCK_SIZE, convert_to_hexcode(0, 255, 0, 255));
			side = true;
		}
	}
	// set_cardinal(map, ray, side);
	if (side)
		return (ray->length.y - ray->hypotenuse.y);
	else
		return (ray->length.x - ray->hypotenuse.x);
}

void	set_transparent(mlx_image_t *img)
{
	int		i;
	int		j;

	i = 0;
	while (i < img->width)
	{
		j = 0;
		while (j < img->height)
		{
			mlx_put_pixel(img, i, j, convert_to_hexcode(0, 0, 0, 0));
			j++;
		}
		i++;
	}
}

double	cast_ray(t_game *game, double ray_dir)
{
	t_ray	ray;
	double	res;

	init_ray(&ray, game->player.x, game->player.y, ray_dir);
	set_transparent(game->img_a);
	res = extend_ray(&ray, &game->map, game);
	debug_print_ray(&ray);
	return (res);
}
