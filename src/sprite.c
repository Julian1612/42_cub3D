
#include "cub3D.h" // cub3D structs
#include <stdio.h> // @note remove
#include <math.h> // cos, sin, tan
#include <stdlib.h> // @note for abs, remove
#include <unistd.h> // @note for write, remove

// void	put_square(mlx_image_t *img, int x, int y, int size, int color)
// {
// 	int	x_iter;
// 	int	y_iter;

// 	y_iter = y;
// 	while (y_iter < y + size)
// 	{
// 		x_iter = x;
// 		while (x_iter < x + size)
// 		{
// 			mlx_put_pixel(img, x_iter, y_iter, color);
// 			x_iter++;
// 		}
// 		y_iter++;
// 	}
// }

// void	render_sprite(t_sprite *sprite, t_game *game)
// {
// 	int	x_start;
// 	int	x_end;
// 	int	y_start;
// 	int	y_end;
// 	int	x_iter;
// 	int	y_iter;
// 	int	x_tex;
// 	int	y_tex;
// 	double	x_offset;
// 	int	y_offset;

// 	x_offset = fmod(sprite->angle, M_PI) * game->img_a->width;
// 	printf("x_offset: %f\n", x_offset);
// 	y_offset = game->img_a->height / 2;
// 	x_start = (game->img_a->width / 2 - sprite->width / 2) + x_offset;
// 	x_end = x_start + sprite->width ;
// 	y_start = sprite->x - sprite->height / 2 + y_offset;
// 	y_end = sprite->x + sprite->height / 2 + y_offset;

// 	printf("x_start: %d, x_end: %d\n", x_start, x_end);
// 	printf("y_start: %d, y_end: %d\n", y_start, y_end);
// 	// put_square(game->img_a, x_start, y_start, 10, 0x00FF00FF);

// 	y_iter = y_start;
// 	while (y_iter < y_end)
// 	{
// 		if (y_iter < 0 || y_iter >= game->img_a->height)
// 		{
// 			y_iter++;
// 			continue ;
// 		}
// 		// y_tex = (y_iter - y_start) * sprite->texture->tex->height / sprite->height;
// 		y_tex = 0;
// 		x_iter = x_start;
// 		while (x_iter < x_end)
// 		{
// 			if (x_iter < 0 || x_iter >= game->img_a->width)
// 			{
// 				x_iter++;
// 				continue ;
// 			}
// 			// x_tex = (x_iter - x_start) * sprite->texture->tex->width / sprite->width;
// 			x_tex = 0;
// 			mlx_put_pixel(game->img_a, x_iter, y_iter, 0x00FF00FF);
// 			x_iter++;
// 			x_tex++;
// 		}
// 		y_iter++;
// 		y_tex++;
// 	}
// 	printf("x_tex: %d, y_tex: %d\n", x_tex, y_tex);
// }

// void	init_sprite(t_game *game)
// {
// 	t_sprite	sprite;
// 	double		fov;

// 	sprite.x = 5;
// 	sprite.y = 5;
// 	sprite.texture = &game->map.objects[SPRITE];
// 	sprite.dist = sqrt(pow(sprite.x - game->player.x, 2) + pow(sprite.y - game->player.y, 2));
// 	sprite.angle = atan2(sprite.y - game->player.y, sprite.x - game->player.x) - game->player.view_angle + M_PI / 2;
// 	fov = 1;
// 	sprite.height = game->img_a->height / sprite.dist;
// 	sprite.width = sprite.height;
// 	debug_print_sprite(&sprite);
// 	render_sprite(&sprite, game);
// }

void	init_sprite(t_game *game)
{
	t_sprite	sprite;
	double		distance_x;
	double		distance_y;
	double		dir_x;
	double		dir_y;
	double		transform_x;
	double		transform_y;
	double		sprite_screen_x;
	double		height;
	int			draw_start_y;
	int			draw_end_y;
	double		width;
	int			draw_start_x;
	int			draw_end_x;

	sprite.x = 5;
	sprite.y = 5;
	sprite.texture = &game->map.objects[SPRITE];
	dir_x = cos(game->player.view_angle);
	dir_y = sin(game->player.view_angle);
	printf("dir_x: %f, dir_y: %f\n", dir_x, dir_y);
	distance_x = sprite.x - game->player.pos.x;
	distance_y = sprite.y - game->player.pos.y;
	printf("distance_x: %f, distance_y: %f\n", distance_x, distance_y);
	transform_x = dir_x * distance_x + dir_y * distance_y;
	transform_y = dir_y * distance_x - dir_x * distance_y;
	printf("transform_x: %f, transform_y: %f\n", transform_x, transform_y);
	sprite_screen_x = (game->img_a->width / 2) * (1 + transform_x / transform_y);
	printf("sprite_screen_x: %f\n", sprite_screen_x);

	// determine start and end of sprite on screen (y axis)
	height = abs((int)(game->img_a->height / transform_y));
	printf("height: %f\n", height);
	draw_start_y = -height / 2 + game->img_a->height / 2;
	if (draw_start_y < 0)
		draw_start_y = 0;
	draw_end_y = height / 2 + game->img_a->height / 2;
	if (draw_end_y >= game->img_a->height)
		draw_end_y = game->img_a->height - 1;
	printf("draw_start_y: %d, draw_end_y: %d\n", draw_start_y, draw_end_y);

	// determine start and end of sprite on screen (x axis)
	width = height;
	draw_start_x = -width / 2 + sprite_screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	draw_end_x = width / 2 + sprite_screen_x;
	if (draw_end_x >= game->img_a->width)
		draw_end_x = game->img_a->width - 1;
	printf("draw_start_x: %d, draw_end_x: %d\n", draw_start_x, draw_end_x);

	// draw sprite
	for (int x = draw_start_x; x < draw_end_x; x++)
	{
		int	tex_x = (int)(256 * (x - (-width / 2 + sprite_screen_x)) * sprite.texture->tex->width / width) / 256;
		for (int y = draw_start_y; y < draw_end_y; y++)
		{
			int	d = y * 256 - game->img_a->height * 128 + height * 128;
			int	tex_y = ((d * sprite.texture->tex->height) / height) / 256;
			u_int32_t color = sprite.texture->tex->pixels[sprite.texture->tex->width * tex_y + tex_x];
			mlx_put_pixel(game->img_a, x, y, color);
		}
	}
}
