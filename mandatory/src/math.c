/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:19:51 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/15 00:53:50 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // typedefs
#include "../libraries/mlx42/include/MLX42/MLX42.h" // mlx typedefs
#include <math.h> // sin, cos

uint32_t	coor_to_pixel(uint32_t width, int x, int y, uint32_t height)
{
	uint32_t	pixel;

	pixel = y * width + x;
	if (pixel > (width - 1) * (height - 1))
		return (0);
	pixel *= 4;
	return (pixel);
}

double	rotate_x(double x, double y, double angle)
{
	double	rotated_x;

	rotated_x = x * cos(angle) - y * sin(angle);
	return (rotated_x);
}

double	rotate_y(double x, double y, double angle)
{
	double	rotated_y;

	rotated_y = y * cos(angle) + x * sin(angle);
	return (rotated_y);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

double	get_dist_of_vecs(t_vec *a, t_vec *b)
{
	return ((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
}
