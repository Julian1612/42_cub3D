/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:22:27 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 23:10:38 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_render.h" // render funcs
#include "../../libraries/mlx/include/MLX42/MLX42.h" // mlx typedefs
#include "../../libraries/libft/src/libft/libft.h" // ft_memcpy
#include <stdio.h>

void	render_texture(mlx_image_t *img, t_tex *tex,
	t_coor pos, double ratio)
{
	t_coor		img_coor;
	t_coor		tex_coor;
	int			temp;

	img_coor.x = pos.x;
	tex_coor.x = 0;
	while ((uint32_t)tex_coor.x < tex->tex->width)
	{
		img_coor.y = pos.y;
		temp = 0;
		while (temp < tex->tex->height / ratio)
		{
			tex_coor.y = temp * ratio;
			tex_pixel_to_img(img, tex->tex, &tex_coor, &img_coor);
			img_coor.y++;
			temp++;
		}
		img_coor.x++;
		tex_coor.x++;
	}
}

void	tex_pixel_to_img(
	mlx_image_t *img, mlx_texture_t *tex, t_coor *tex_coor, t_coor *img_coor)
{
	uint8_t	*src;
	uint8_t	*dst;

	src = &tex->pixels[coor_to_pixel(tex->width, tex_coor->x,
			tex_coor->y, tex->height)];
	dst = &img->pixels[coor_to_pixel(img->width, img_coor->x,
			img_coor->y, img->height)];
	ft_memcpy(dst, src, tex->bytes_per_pixel);
}
