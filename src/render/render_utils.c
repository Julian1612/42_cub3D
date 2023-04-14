/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:22:27 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 11:17:47 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_render.h" // render funcs
#include "../../libraries/mlx/include/MLX42/MLX42.h" // mlx typedefs
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

void	render_texture_transparent(mlx_image_t *img, t_tex *tex,
	t_coor pos, double ratio)
{
	t_coor		img_coor;
	t_coor		tex_coor;
	int			temp;
	t_hexcolor	color;

	img_coor.x = pos.x;
	tex_coor.x = 0;
	while ((uint32_t)tex_coor.x < tex->tex->width)
	{
		img_coor.y = pos.y;
		temp = 0;
		while (temp < tex->tex->height / ratio)
		{
			tex_coor.y = temp * ratio;
			color = tex->tex->pixels[coor_to_pixel(tex->tex->width,
					tex_coor.x, tex_coor.y, tex->tex->height)];
			if (is_transparent(color) == false)
				tex_pixel_to_img(img, tex->tex, &tex_coor, &img_coor);
			img_coor.y++;
			temp++;
		}
		img_coor.x++;
		tex_coor.x++;
	}
}

void	render_color_image(mlx_image_t *img, t_hexcolor color)
{
	uint32_t	x;
	uint32_t	y;

	x = 0;
	while (x < img->width)
	{
		y = 0;
		while (y < img->height)
		{
			mlx_put_pixel(img, x, y, color);
			y++;
		}
		x++;
	}
}
