/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:01:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/28 00:47:31 by lorbke           ###   ########.fr       */
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
		ray->op_step.y = -UNIT / ray->dir.y;
		ray->length.x = (ray->origin.x - ray->map_x) * ray->hypotenuse.x;
	}
	else
	{
		ray->step.x = UNIT;
		ray->op_step.y = UNIT / ray->dir.y;
		ray->length.x = (ray->map_x + UNIT - ray->origin.x) * ray->hypotenuse.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -UNIT;
		ray->op_step.x = -UNIT / ray->dir.x;
		ray->length.y = (ray->origin.y - ray->map_y) * ray->hypotenuse.y;
	}
	else
	{
		ray->step.y = UNIT;
		ray->op_step.x = UNIT / ray->dir.x;
		ray->length.y = (ray->map_y + UNIT - ray->origin.y) * ray->hypotenuse.y;
	}
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
			ray->op_step.y = fmod(ray->map_x / tan(ray->angle), UNIT);
			mlx_put_pixel(game->img_a, ray->map_x * MM_BLOCK_SIZE, (ray->op_step.y + ray->map_y) * MM_BLOCK_SIZE, convert_to_hexcode(255, 0, 0, 255));
			side = false;
		}
		else
		{
			ray->map_y += ray->step.y;
			ray->length.y += ray->hypotenuse.y;
			ray->op_step.x = fmod(ray->map_y * tan(ray->angle), UNIT);
			mlx_put_pixel(game->img_a, (ray->op_step.x + ray->map_x) * MM_BLOCK_SIZE, ray->map_y * MM_BLOCK_SIZE, convert_to_hexcode(0, 255, 0, 255));
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
