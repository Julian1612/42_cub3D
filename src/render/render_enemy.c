/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 14:38:22 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/13 18:16:57 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_render.h" // render funcs
#include "../enemy.h" // t_enemy
#include "../debug.h" // debug funcs
#include "libraries/mlx/include/MLX42/MLX42.h" // mlx typedefs

static void	spritehelper_init(t_spritehelper *hlpr,
	t_sprite *sprite, mlx_image_t *img)
{
	row_set_start_end(&hlpr->row, sprite->height, img->height);
	column_set_start_end(&hlpr->column, sprite->width,
		img->width, sprite->img_x);
	hlpr->ratio = (double)sprite->tex->tex->height / sprite->height;
}

void	draw_column(t_sprite *sprite,
	t_spritehelper *hlpr, mlx_image_t *img)
{
	hlpr->img_coor.y = hlpr->row.start;
	while (hlpr->img_coor.y++ < hlpr->row.end)
	{
		hlpr->tex_coor.y = hlpr->temp * hlpr->ratio;
		hlpr->color = sprite->tex->tex->pixels[coor_to_pixel(
				sprite->tex->tex->width, hlpr->tex_coor.x, hlpr->tex_coor.y)];
		if (is_transparent(hlpr->color) == false)
			tex_pixel_to_img(img, sprite->tex->tex,
				&hlpr->tex_coor, &hlpr->img_coor);
		hlpr->temp++;
	}
}

static void	draw_sprite(t_sprite *sprite,
	mlx_image_t *img, int *wall_height)
{
	t_spritehelper	hlpr;

	spritehelper_init(&hlpr, sprite, img);
	hlpr.img_coor.x = hlpr.column.start;
	while (hlpr.img_coor.x++ < hlpr.column.end)
	{
		if (is_visible(sprite, &hlpr, img, wall_height) == false)
			continue ;
		hlpr.tex_coor.x = (hlpr.img_coor.x - (-sprite->width / 2
					+ sprite->img_x)) * sprite->tex->tex->width / sprite->width;
		hlpr.temp = 0;
		if (sprite->height > img->height)
			hlpr.temp = (sprite->height - img->height) / 2;
		draw_column(sprite, &hlpr, img);
	}
}

static void	sort_enemies(t_vec *pos, t_enemy *enemies, int enemy_count)
{
	t_enemy		temp;
	int			i;
	double		dist_old;
	double		dist_new;

	i = 0;
	if (enemy_count == 0)
		return ;
	while (i < enemy_count - 1)
	{
		dist_old = get_dist_of_vecs(pos, &enemies[i].pos);
		dist_new = get_dist_of_vecs(pos, &enemies[i + 1].pos);
		if (dist_old < dist_new)
		{
			temp = enemies[i];
			enemies[i] = enemies[i + 1];
			enemies[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}

void	enemies_render(
	t_game *game, t_enemy *enemies, int *wall_height)
{
	t_sprite	sprite;
	int			i;

	sort_enemies(&game->player.pos, enemies, game->map.enemy_count);
	if (game->map.enemy_count == 0)
		return ;
	i = -1;
	while (i++ < game->map.enemy_count)
	{
		if (game->map.enemies[i].alive == false)
			continue ;
		sprite_init(&sprite, &enemies[i].pos,
			&game->map.textures[enemies[i].curr_frame], game);
		debug_print_sprite(&sprite);
		draw_sprite(&sprite, game->img_world, wall_height);
	}
}
