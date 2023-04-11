/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 23:06:33 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/12 01:40:59 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h" // cub3D structs
#include "../../libraries/libft/src/libft/libft.h" // ft_memcpy
#include <stdio.h> // @note remove
#include <math.h> // cos, sin, tan
#include <unistd.h> // @note for write, remove
#include <stdbool.h> // bool

typedef struct s_start_end
{
	int	start;
	int	end;
}	t_start_end;

typedef struct s_draw_sprite
{
	t_start_end	row;
	t_start_end	column;
	t_coor		tex_coor;
	int			temp;
	t_coor		img_coor;
	double		ratio;
	t_hexcolor	color;
}	t_draw_sprite;

static void	set_row_start_end(t_start_end *row, int sprite_height, int img_height, int offset)
{
	row->start = -sprite_height / 2 + img_height / 2;
	if (row->start < 0)
		row->start = 0;
	row->end = sprite_height / 2 + img_height / 2;
	if (row->end >= img_height)
		row->end = img_height - 1;
}

static void	set_stripe_start_end(t_start_end *stripe, int sprite_width, int img_width, int img_x)
{
	stripe->start = -sprite_width / 2 + img_x;
	if (stripe->start < 0)
		stripe->start = 0;
	stripe->end = sprite_width / 2 + img_x;
	if (stripe->end < 0) // @note prevent overflow when comparing with uint img width
		stripe->end = 0;
	if (stripe->end >= img_width)
		stripe->end = img_width - 1;
}

static bool	is_invisible(t_hexcolor color)
{
	if (color == 0x00000000)
		return (true);
	return (false);
}

static void	draw_sprite_column(t_sprite *sprite,
	t_draw_sprite *hlpr, mlx_image_t *img)
{
	hlpr->img_coor.y = hlpr->row.start;
	while (hlpr->img_coor.y++ < hlpr->row.end)
	{
		hlpr->tex_coor.y = hlpr->temp * hlpr->ratio;
		hlpr->color = sprite->tex->tex->pixels[coor_to_pixel(
				sprite->tex->tex->width, hlpr->tex_coor.x, hlpr->tex_coor.y)];
		if (is_invisible(hlpr->color) == false)
			tex_pixel_to_img(img, sprite->tex->tex,
				&hlpr->tex_coor, &hlpr->img_coor);
		hlpr->temp++;
	}
}

static void	draw_sprite_init(t_draw_sprite *hlpr,
	t_sprite *sprite, mlx_image_t *img)
{
	set_row_start_end(&hlpr->row, sprite->height, img->height, 0);
	set_stripe_start_end(&hlpr->column, sprite->width,
		img->width, sprite->img_x);
	hlpr->ratio = (double)sprite->tex->tex->height / sprite->height;
}

static bool	draw_sprite_is_visible(
	t_sprite *sprite, t_draw_sprite *hlpr, mlx_image_t *img, int *wall_height)
{
	if (sprite->cam_pos.y < 0 || hlpr->img_coor.x < 0
		|| hlpr->img_coor.x >= img->width
		|| wall_height[hlpr->img_coor.x] > sprite->height)
		return (false);
	return (true);
}

// @note split up in 2d and 3d functions
// @todo check for out of bounds
static void	draw_sprite(t_sprite *sprite, mlx_image_t *img, int *wall_height)
{
	t_draw_sprite	hlpr;

	draw_sprite_init(&hlpr, sprite, img);
	hlpr.img_coor.x = hlpr.column.start;
	while (hlpr.img_coor.x++ < hlpr.column.end)
	{
		if (draw_sprite_is_visible(sprite, &hlpr, img, wall_height) == false)
			continue ;
		hlpr.tex_coor.x = (hlpr.img_coor.x - (-sprite->width / 2
					+ sprite->img_x)) * sprite->tex->tex->width / sprite->width;
		hlpr.temp = 0;
		if (sprite->height > img->height)
			hlpr.temp = (sprite->height - img->height) / 2;
		draw_sprite_column(sprite, &hlpr, img);
	}
}

static void	init_sprite(
	t_sprite *sprite, t_vec *pos, t_tex *tex, t_player *player, t_game *game)
{
	double	cam_matrix_inv;

	sprite->tex = tex;
	sprite->dir.x = player->dir.x;
	sprite->dir.y = player->dir.y;
	sprite->dist.x = pos->x - player->pos.x;
	sprite->dist.y = pos->y - player->pos.y;
	cam_matrix_inv = 1.0
		/ (player->cplane.x * sprite->dir.y - sprite->dir.x * player->cplane.y);
	sprite->cam_pos.x = -cam_matrix_inv
		* (sprite->dir.y * sprite->dist.x - sprite->dir.x * sprite->dist.y);
	sprite->cam_pos.y = cam_matrix_inv
		* (-player->cplane.y * sprite->dist.x
			+ player->cplane.x * sprite->dist.y);
	sprite->img_x = (game->img_world->width / 2)
		* (1 + sprite->cam_pos.x / sprite->cam_pos.y);
	sprite->height = ft_abs((int)(game->img_world->height / sprite->cam_pos.y));
	sprite->width = ft_abs((int)(game->img_world->height / sprite->cam_pos.y));
}

double get_distance(t_vec *a, t_vec *b)
{
	return ((a->x - b->x) * (a->x - b->x) + (a->y - b->y) * (a->y - b->y));
}

// @todo create dist array to calculate dists only once
void	sort_sprites(t_vec *pos, t_object *objects, t_enemy *enemies, int enemy_count)
{
	t_enemy		temp;
	int			i;
	double		dist_old;
	double		dist_new;

	i = 0;
	while (i < enemy_count - 1)
	{
		dist_old = get_distance(pos, &enemies[i].pos);
		dist_new = get_distance(pos, &enemies[i + 1].pos);
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

void	render_sprites(
	t_game *game, t_object *objects, t_enemy *enemies, int *wall_height)
{
	t_sprite	sprite;
	int			i;

	sort_sprites(&game->player.pos, objects, enemies, game->map.enemy_count);
	i = 0;
	while (i < game->map.obj_count)
	{
		init_sprite(&sprite, &objects[i].pos,
			objects[i].tex, &game->player, game);
		debug_print_sprite(&sprite);
		draw_sprite(&sprite, game->img_world, wall_height);
		i++;
	}
	i = -1;
	while (i++ < game->map.enemy_count)
	{
		if (game->map.enemies[i].alive == false)
			continue ;
		init_sprite(&sprite, &enemies[i].pos,
			&game->map.textures[enemies[i].curr_frame], &game->player, game);
		debug_print_sprite(&sprite);
		draw_sprite(&sprite, game->img_world, wall_height);
	}
}
