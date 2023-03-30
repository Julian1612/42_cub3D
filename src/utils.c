/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 16:19:51 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/30 20:07:05 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // typedefs
#include "../libraries/mlx/include/MLX42/MLX42.h" // mlx typedefs

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

int	coor_to_pixel(int width, int x, int y)
{
	int	pixel;

	pixel = y * width + x;
	// @note multiply to get from int32 to int8
	pixel *= 4;
	return (pixel);
}
