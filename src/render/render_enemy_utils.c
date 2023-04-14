/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_enemy_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:56:45 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/13 23:40:56 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_render.h" // render funcs
#include "../../libraries/mlx/include/MLX42/MLX42.h" // mlx typedefs
#include "../../libraries/libft/src/libft/libft.h" // ft_memcpy

bool	is_transparent(t_hexcolor color)
{
	if (color == 0x00000000)
		return (true);
	return (false);
}

bool	is_visible(t_sprite *sprite, t_spritehelper *hlpr,
	mlx_image_t *img, int *wall_height)
{
	if (sprite->cam_pos.y < 0 || hlpr->img_coor.x < 0
		|| (uint32_t)hlpr->img_coor.x >= img->width
		|| wall_height[hlpr->img_coor.x] > sprite->height)
		return (false);
	return (true);
}

void	row_set_start_end(t_start_end *row, int sprite_height, int img_height)
{
	row->start = -sprite_height / 2 + img_height / 2;
	if (row->start < 0)
		row->start = 0;
	row->end = sprite_height / 2 + img_height / 2;
	if (row->end >= img_height)
		row->end = img_height - 1;
}

void	column_set_start_end(t_start_end *stripe, int sprite_width,
	int img_width, int img_x)
{
	stripe->start = -sprite_width / 2 + img_x;
	if (stripe->start < 0)
		stripe->start = 0;
	stripe->end = sprite_width / 2 + img_x;
	if (stripe->end < 0)
		stripe->end = 0;
	if (stripe->end >= img_width)
		stripe->end = img_width - 1;
}
