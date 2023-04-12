/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:26:54 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/12 19:21:39 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_render.h" // render funcs
#include "libraries/mlx/include/MLX42/MLX42.h" // mlx typedefs
#include <string.h> // NULL

static void	draw_weapon(mlx_image_t *img, t_tex *weapon_tex)
{
	t_coor	img_coor;
	t_coor	tex_coor;
	int		temp;
	double	ratio;

	ratio = (double)weapon_tex->tex->height / img->height * 3;
	img_coor.x = img->width / 2 - weapon_tex->tex->width / 2;
	tex_coor.x = 0;
	while (tex_coor.x < weapon_tex->tex->width)
	{
		img_coor.y = img->height - weapon_tex->tex->height / ratio;
		temp = 0;
		while (temp < weapon_tex->tex->height / ratio)
		{
			tex_coor.y = temp * ratio;
			tex_pixel_to_img(img, weapon_tex->tex, &tex_coor, &img_coor);
			img_coor.y++;
			temp++;
		}
		img_coor.x++;
		tex_coor.x++;
	}
}

void	hud_render(t_game *game)
{
	if (game->player.weapon != NULL)
		draw_weapon(game->img_hud,
			game->map.textures[game->player.weapon->curr_frame]);
}
