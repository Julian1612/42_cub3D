/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:01:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/23 13:13:05 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include "../libraries/libft/src/libft/libft.h" // ft_putstr_fd
#include <math.h> // cos, sin, tan
#include <stdio.h> // @note remove
#include <stdbool.h> // bool

#define UNIT 1

void	set_transparent(mlx_image_t *image)
{
	int		i;
	int		j;
	int		color;

	i = 0;
	while (i < image->width)
	{
		j = 0;
		while (j < image->height)
		{
			mlx_put_pixel(image, i, j, convert_to_hexcode(0, 0, 0, 0));
			j++;
		}
		i++;
	}
}

void	init_ray(t_ray *ray, t_game *game, double ray_dir)
{
	ray->dir.x = sin(ray_dir);
	ray->dir.y = cos(ray_dir);
	ray->origin.x = game->player.x / MM_BLOCK_SIZE;
	ray->origin.y = game->player.y / MM_BLOCK_SIZE;
	ray->map_x = (int)ray->origin.x;
	ray->map_y = (int)ray->origin.y;
	ray->hypotenuse.x = sqrt(UNIT + (ray->dir.y * ray->dir.y) / (ray->dir.x * ray->dir.x));
	ray->hypotenuse.y = sqrt(UNIT + (ray->dir.x * ray->dir.x) / (ray->dir.y * ray->dir.y));
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

double	extend_ray(mlx_image_t *img, t_ray *ray, char **map)
{
	double	temp;

	while (map[ray->map_y][ray->map_x] != WALL)
	{
		if (ray->length.x < ray->length.y)
		{
			ray->map_x += ray->step.x;
			temp = ray->length.x;
			ray->length.x += ray->hypotenuse.x;
		}
		else
		{
			ray->map_y += ray->step.y;
			temp = ray->length.y;
			ray->length.y += ray->hypotenuse.y;
		}
	}
	return (temp);
}

double	cast_ray(t_game *game, double ray_dir)
{
	t_ray	ray;
	double	res;

	init_ray(&ray, game, ray_dir);
	// why do we need to subtract UNIT?
	res = extend_ray(game->img_a, &ray, game->map.map);
	// printf("res: %f\n", res);
	return (res);
}
