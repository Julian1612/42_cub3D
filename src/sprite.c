
#include "cub3D.h" // cub3D structs
#include <stdio.h> // @note remove
#include <math.h> // cos, sin, tan
#include <stdlib.h> // @note for abs, remove

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
	dir_x = cos(game->player.view_dir);
	dir_y = sin(game->player.view_dir);
	printf("dir_x: %f, dir_y: %f\n", dir_x, dir_y);
	distance_x = sprite.x - game->player.x;
	distance_y = sprite.y - game->player.y;
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
