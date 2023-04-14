/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 01:22:27 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 01:29:56 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_render.h" // render funcs
#include "libraries/mlx/include/MLX42/MLX42.h" // mlx typedefs

void	render_texture(mlx_image_t *img, t_tex *tex,
	t_coor pos, double ratio)
{
	t_coor	img_coor;
	t_coor	tex_coor;
	int		temp;

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
