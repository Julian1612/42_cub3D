/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:46:52 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/27 20:20:34 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include <stdio.h> // @note remove
#include <math.h> // PI
#include <string.h> // @note memmove, remove
#include <stdlib.h> // @note exit, remove

#define FOV 60

int	coor_to_pixel(int width, int x, int y)
{
	int	pixel;

	pixel = y * width + x;
	// @note multiply to get from int32 to int8
	pixel *= 4;
	return (pixel);
}

void	switch_pixel(mlx_image_t *img, int x, int y, uint8_t src[4])
{
	int	dest;

	dest = coor_to_pixel(img->width, x, y);
	img->pixels[dest] = src[0];
	img->pixels[dest + 1] = src[1];
	img->pixels[dest + 2] = src[2];
	img->pixels[dest + 3] = src[3];
}

void	paint_reflection(t_game *game, double obj_dist, int x, double ray_offset)
{
	int		reflec_height;
	int		y;
	int		i;
	double	step;
	double	block_offset;
	int		tex_x;
	int		tex_y;

	if (obj_dist < 1)
		obj_dist = 1;
	reflec_height = (int)(HEIGHT / obj_dist);
	step = (double)(game->map.cardinal->texture->height - 1) / reflec_height;
	block_offset = fabs(ray_offset * game->map.adjacent_len);
	tex_x = block_offset * (game->map.cardinal->texture->width);
	// tex_x = game->map.adjacent_len;
	// tex_x -= tex_x % 4;
	y = 0;
	while (y < HEIGHT / 2 - reflec_height / 2)
	{
		mlx_put_pixel(game->img_a, x, y, game->map.ceiling_color);
		y++;
	}
	i = 0;
	while (y < HEIGHT / 2 + reflec_height / 2)
	{
		tex_y = i * step;
		// printf("tex_x: %d, tex_y: %d\n", tex_x, tex_y);
		switch_pixel(game->img_a, x, y, &game->map.cardinal->texture->pixels[coor_to_pixel(game->map.cardinal->texture->width, tex_x, tex_y)]);
		i++;
		y++;
	}
	// printf("\n\nadjacent_len: %i\n", game->map.adjacent_len);
	// printf("ray_offset: %f\n", ray_offset);
	// printf("block_offset: %f\n", block_offset);
	// printf("\nstep: %f\n", step);
	// printf("reflec_height: %i\n", reflec_height);
	// printf("y: %i\n", y);
	// printf("tex_x: %d, tex_y: %d\n", tex_x, tex_y);
	while (y < HEIGHT)
	{
		mlx_put_pixel(game->img_a, x, y, game->map.floor_color);
		y++;
	}
		// exit(0);
}

double	calc_mini_offset(t_game *game, double ray_dir)
{
	double player_opposite;
	double ray_opposite;

	player_opposite = tan(game->player.view_dir) * game->map.adjacent_len;
	ray_opposite = tan(ray_dir) * game->map.adjacent_len;
	return (ray_opposite - player_opposite);
}

int	render_world(t_game *game)
{
	double	wall_dist;
	double	ray_dir;
	double	fov;
	int		x;

	debug_print_player(&game->player);
	fov = 1;
	ray_dir = game->player.view_dir - (fov / 2);
	x = 0;
	while (x < WIDTH)
	{
		ray_dir += fov / game->mlx->width;
		wall_dist = cast_ray(game, ray_dir);
		// @note prevent fisheye effect
		wall_dist *= cos(game->player.view_dir - ray_dir);
		paint_reflection(game, wall_dist, x, game->player.view_dir - ray_dir);
		x++;
	}
	// exit(0);
	return (SUCCESS);
}

/*
	- ray_offset len = (ray_dir - view_dir) * (map(x | y) - origin(x | y))
	- step = wall height / texture height
	- texture pixel y = yiter / step
	- texture pixel x = ray_offset len * texture width
*/
