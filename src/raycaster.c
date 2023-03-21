/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:01:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/21 01:10:12 by lorbke           ###   ########.fr       */
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
	ray->hypotenuse.x = sqrt(1 + (ray->dir.y / ray->dir.x) * (ray->dir.y / ray->dir.x));
	ray->hypotenuse.y = sqrt(1 + (ray->dir.x / ray->dir.y) * (ray->dir.x / ray->dir.y));
	if (ray->dir.x < 0)
	{
		ray->step.x = -UNIT;
		ray->length.x = (ray->origin.x - ceil(ray->origin.x - 1)) * ray->hypotenuse.x;
	}
	else
	{
		ray->step.x = UNIT;
		ray->length.x = (ceil(ray->origin.x) - ray->origin.x) * ray->hypotenuse.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -UNIT;
		ray->length.y = (ray->origin.y - ceil(ray->origin.y - 1)) * ray->hypotenuse.y;
	}
	else
	{
		ray->step.y = UNIT;
		ray->length.y = (ceil(ray->origin.y) - ray->origin.y) * ray->hypotenuse.y;
	}
}

double	extend_ray(mlx_image_t *img, t_ray *ray, char **map)
{
	bool	hit;
	t_coor	next;

	hit = false;
	next = ray->origin;
	while (hit == false)
	{
		if (ray->length.x < ray->length.y)
		{
			next.x += ray->step.x;
			ray->length.x += ray->hypotenuse.x;
		}
		else
		{
			next.y += ray->step.y;
			ray->length.y += ray->hypotenuse.y;
		}
		mlx_put_pixel(img, next.x * MM_BLOCK_SIZE, next.y * MM_BLOCK_SIZE, convert_to_hexcode(0, 255, 0, 255));
		if (map[(int)next.y][(int)next.x] == WALL)
			hit = true;
	}
	if (ray->length.x < ray->length.y)
		return (fabs(ray->length.x));
	else
		return (fabs(ray->length.y));
}

double	cast_ray(t_game *game, double ray_dir)
{
	t_ray	ray;
	double	res;

	init_ray(&ray, game, ray_dir);
	set_transparent(game->img_a);
	// why do we need to subtract UNIT?
	res = extend_ray(game->img_a, &ray, game->map.map) - UNIT;
	// printf("res: %f\n", res);
	return (res);
}
