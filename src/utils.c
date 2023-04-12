/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:19:51 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/12 18:27:20 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // typedefs
#include "../libraries/mlx/include/MLX42/MLX42.h" // mlx typedefs
#include "../libraries/libft/src/libft/libft.h" // ft_memcpy
#include <math.h> // sin, cos

t_hexcolor	convert_to_hexcode(
	unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	unsigned int	rgba;

	rgba = r;
	rgba = (rgba << 8) + g;
	rgba = (rgba << 8) + b;
	rgba = (rgba << 8) + a;
	return (rgba);
}

// @todo switch to t_coor
int	coor_to_pixel(int width, int x, int y)
{
	int	pixel;

	pixel = y * width + x;
	// @note multiply to get from int32 to int8
	pixel *= 4;
	return (pixel);
}

// @todo move this to separate math file with other math related functions?
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

double get_dist_of_vecs(t_vec *a, t_vec *b)
{
	return ((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
}
