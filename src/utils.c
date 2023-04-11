/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:19:51 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/11 23:51:12 by lorbke           ###   ########.fr       */
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

void	tex_pixel_to_img(
	mlx_image_t *img, mlx_texture_t *tex, t_coor *tex_coor, t_coor *img_coor)
{
	uint8_t	*src;
	uint8_t	*dst;

	src = &tex->pixels[coor_to_pixel(tex->width, tex_coor->x, tex_coor->y)];
	dst = &img->pixels[coor_to_pixel(img->width, img_coor->x, img_coor->y)];
	ft_memcpy(dst, src, 4);
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

bool	switch_bool(bool b)
{
	if (b == true)
		return (false);
	return (true);
}
