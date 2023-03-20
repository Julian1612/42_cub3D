/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:01:24 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/20 23:02:31 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include "../libraries/libft/src/libft/libft.h" // ft_putstr_fd
#include <math.h> // cos, sin, tan
#include <stdio.h> // @note remove
#include <stdbool.h> // bool

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

double	cast_ray(t_game *game, double ray_dir)
{
	double	dir_sin;
	double	dir_cos;
	double	px;
	double	py;
	double	x;
	double	y;
	double	ray_len;

	dir_sin = sin(ray_dir);
	dir_cos = cos(ray_dir);
	px = game->player.x / MM_BLOCK_SIZE;
	py = game->player.y / MM_BLOCK_SIZE;
	x = px;
	y = py;
	set_transparent(game->img_a);
	while (game->map.map[(int)y][(int)x] != WALL)
	{
		x += dir_sin / 20;
		y += dir_cos / 20;
		if (x >= 0 && y >= 0 && x < game->map.width && y < game->map.height)
			mlx_put_pixel(game->img_a, x * MM_BLOCK_SIZE, y * MM_BLOCK_SIZE, convert_to_hexcode(255, 0, 0, 255));
	}
	ray_len = sqrt(pow(x - px, 2) + pow(y - py, 2));
	printf("ray_len: %f\n", ray_len);
	return (ray_len);
}
