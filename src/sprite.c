
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
	if (color == 0x000000FF)
		return (true);
	return (false);
}

// @note split up in 2d and 3d functions
// @todo check for out of bounds
void	draw_sprite(t_sprite *sprite, t_game *game)
{
	t_start_end	row;
	t_start_end	stripe;
	double		scale;
	int			y_tex_iter;
	int			tex_x;
	int			row_iter;
	int			stripe_iter;
	t_hexcolor	color;

	set_row_start_end(&row, sprite->height, game->img_a->height, 0);
	set_stripe_start_end(&stripe, sprite->width, game->img_a->width, sprite->img_x);
	scale = (double)(sprite->texture->tex->height) / sprite->height;
	stripe_iter = stripe.start;
	while (stripe_iter++ < stripe.end)
	{
		if (sprite->cam_pos.y < 0 || stripe_iter < 0 || stripe_iter >= game->img_a->width)
			continue ;
		tex_x = (stripe_iter - (-sprite->width / 2 + sprite->img_x)) * sprite->texture->tex->width / sprite->width;
		y_tex_iter = 0;
		if (sprite->height > game->img_a->height)
			y_tex_iter = (sprite->height - game->img_a->height) / 2;
		row_iter = row.start;
		while (row_iter++ < row.end)
		{
			color = sprite->texture->tex->pixels[coor_to_pixel(sprite->texture->tex->width, tex_x, y_tex_iter * scale)];
			if (is_invisible(color) == false)
				ft_memcpy(&game->img_a->pixels
					[coor_to_pixel(game->img_a->width, stripe_iter, row_iter)],
						&sprite->texture->tex->pixels
					[coor_to_pixel(sprite->texture->tex->width,
							tex_x, y_tex_iter * scale)],
						4); // @todo improve this ugly shit
			y_tex_iter++;
		}
	}
}

void	init_sprite(t_sprite *sprite, t_player *player, t_game *game)
{
	double	cam_matrix_inv;

	sprite->map_pos.x = 5.5;
	sprite->map_pos.y = 4.5;
	sprite->texture = &game->map.objects[SPRITE];
	sprite->dir.x = player->dir.x;
	sprite->dir.y = player->dir.y;
	sprite->dist.x = sprite->map_pos.x - player->pos.x;
	sprite->dist.y = sprite->map_pos.y - player->pos.y;
	cam_matrix_inv = 1.0 / (player->cplane.x * sprite->dir.y - sprite->dir.x * player->cplane.y);
	sprite->cam_pos.x = -cam_matrix_inv * (sprite->dir.y * sprite->dist.x - sprite->dir.x * sprite->dist.y);
	sprite->cam_pos.y = cam_matrix_inv * (-player->cplane.y * sprite->dist.x + player->cplane.x * sprite->dist.y);
	sprite->img_x = (game->img_a->width / 2) * (1 + sprite->cam_pos.x / sprite->cam_pos.y);
	sprite->height = abs((int)(game->img_a->height / sprite->cam_pos.y));
	sprite->width = abs((int)(game->img_a->height / sprite->cam_pos.y));
}

void	render_sprite(t_game *game)
{
	t_sprite	sprite;

	init_sprite(&sprite, &game->player, game);
	draw_sprite(&sprite, game);
	debug_print_sprite(&sprite);
}
