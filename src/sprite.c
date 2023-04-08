
#include "cub3D.h" // cub3D structs
#include "../libraries/libft/src/libft/libft.h" // ft_memcpy
#include <stdio.h> // @note remove
#include <math.h> // cos, sin, tan
#include <stdlib.h> // @note for abs, remove
#include <unistd.h> // @note for write, remove
#include <stdbool.h> // bool

typedef struct s_start_end
{
	int	start;
	int	end;
}	t_start_end;

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

// @note split up in 2d and 3d functions
// @todo check for out of bounds
static void	draw_sprite(t_sprite *sprite, t_game *game, double *wall_height)
{
	t_start_end	row;
	t_start_end	stripe;
	double		scale;
	int			y_tex_iter;
	int			tex_x;
	int			row_iter;
	int			stripe_iter;
	t_hexcolor	color;

	set_row_start_end(&row, sprite->height, game->img_world->height, 0);
	set_stripe_start_end(&stripe, sprite->width, game->img_world->width, sprite->img_x);
	scale = (double)(sprite->tex->tex->height) / sprite->height;
	stripe_iter = stripe.start;
	while (stripe_iter++ < stripe.end)
	{
		if (sprite->cam_pos.y < 0 || stripe_iter < 0 || stripe_iter >= game->img_world->width || wall_height[stripe_iter] > sprite->height)
			continue ;
		tex_x = (stripe_iter - (-sprite->width / 2 + sprite->img_x)) * sprite->tex->tex->width / sprite->width;
		y_tex_iter = 0;
		if (sprite->height > game->img_world->height)
			y_tex_iter = (sprite->height - game->img_world->height) / 2;
		row_iter = row.start;
		while (row_iter++ < row.end)
		{
			color = sprite->tex->tex->pixels[coor_to_pixel(sprite->tex->tex->width, tex_x, y_tex_iter * scale)];
			if (is_invisible(color) == false)
				ft_memcpy(&game->img_world->pixels
					[coor_to_pixel(game->img_world->width, stripe_iter, row_iter)],
						&sprite->tex->tex->pixels
					[coor_to_pixel(sprite->tex->tex->width,
							tex_x, y_tex_iter * scale)],
						4); // @todo improve this ugly shit
			y_tex_iter++;
		}
	}
}

static void	init_sprite(t_sprite *sprite, t_vec *pos, t_tex *tex, t_player *player, t_game *game)
{
	double	cam_matrix_inv;

	sprite->tex = tex;
	sprite->dir.x = player->dir.x;
	sprite->dir.y = player->dir.y;
	sprite->dist.x = pos->x - player->pos.x;
	sprite->dist.y = pos->y - player->pos.y;
	cam_matrix_inv = 1.0 / (player->cplane.x * sprite->dir.y - sprite->dir.x * player->cplane.y);
	sprite->cam_pos.x = -cam_matrix_inv * (sprite->dir.y * sprite->dist.x - sprite->dir.x * sprite->dist.y);
	sprite->cam_pos.y = cam_matrix_inv * (-player->cplane.y * sprite->dist.x + player->cplane.x * sprite->dist.y);
	sprite->img_x = (game->img_world->width / 2) * (1 + sprite->cam_pos.x / sprite->cam_pos.y);
	sprite->height = abs((int)(game->img_world->height / sprite->cam_pos.y));
	sprite->width = abs((int)(game->img_world->height / sprite->cam_pos.y));
}

// @todo create dist array to calculate dists only once
void	sort_sprites(t_game *game, t_object *objects, t_enemy *enemies)
{
	t_object	temp;
	int			i;
	int			dist_old;
	int			dist_new;

	i = 0;
	while (i < game->map.obj_count - 1)
	{
		dist_old = ((game->player.pos.x - objects[i].pos.x) * (game->player.pos.x - objects[i].pos.x) + (game->player.pos.y - objects[i].pos.y) * (game->player.pos.y - objects[i].pos.y));
		dist_new = ((game->player.pos.x - objects[i + 1].pos.x) * (game->player.pos.x - objects[i + 1].pos.x) + (game->player.pos.y - objects[i + 1].pos.y) * (game->player.pos.y - objects[i + 1].pos.y));
		if (dist_old < dist_new)
		{
			temp = objects[i];
			objects[i] = objects[i + 1];
			objects[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}

void	render_sprites(t_game *game, t_object *objects, t_enemy *enemies, double *wall_height)
{
	t_sprite	sprite;
	int			i;
	
	sort_sprites(game, objects, enemies);
	i = 0;
	while (i < game->map.obj_count)
	{
		init_sprite(&sprite, &objects[i].pos, objects[i].tex, &game->player, game);
		debug_print_sprite(&sprite);
		draw_sprite(&sprite, game, wall_height);
		i++;
	}
	i = 0;
	while (i < game->map.enemy_count)
	{
		init_sprite(&sprite, &enemies[i].pos, enemies[i].tex, &game->player, game);
		debug_print_sprite(&sprite);
		draw_sprite(&sprite, game, wall_height);
		i++;
	}
}
