/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_enemy_sprite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 23:06:33 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/13 21:24:25 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h" // cub3D structs
#include "private_render.h" // render funcs
#include "../../libraries/libft/src/libft/libft.h" // ft_memcpy

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

void	sprite_init(t_sprite *sprite, t_vec *pos, t_tex *tex, t_game *game)
{
	double		cam_matrix_inv;
	t_player	*player;

	player = &game->player;
	sprite->tex = tex;
	sprite->dir.x = player->dir.x;
	sprite->dir.y = player->dir.y;
	sprite->dist.x = pos->x - player->pos.x;
	sprite->dist.y = pos->y - player->pos.y;
	cam_matrix_inv = 1.0
		/ (player->cplane.x * sprite->dir.y - sprite->dir.x * player->cplane.y);
	sprite->cam_pos.x = cam_matrix_inv
		* (sprite->dir.y * sprite->dist.x - sprite->dir.x * sprite->dist.y);
	sprite->cam_pos.y = cam_matrix_inv
		* (-player->cplane.y * sprite->dist.x
			+ player->cplane.x * sprite->dist.y);
	sprite->img_x = (game->img_world->width / 2)
		* (1 + sprite->cam_pos.x / sprite->cam_pos.y);
	sprite->height = ft_abs((int)(game->img_world->height / sprite->cam_pos.y));
	sprite->width = ft_abs((int)(game->img_world->height / sprite->cam_pos.y));
}
