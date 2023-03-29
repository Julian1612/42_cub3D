/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:46:52 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/29 20:38:10 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include <stdio.h> // @note remove
#include <math.h> // PI
#include <string.h> // @note memmove, remove
#include <stdlib.h> // @note exit, remove
#include <unistd.h> // @note remove

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

void	paint_reflection(t_game *game, double obj_dist, int x)
{
	int		reflec_height;
	int		y;
	int		i;
	double	step;
	int		tex_x;
	int		tex_y;

	reflec_height = game->mlx->height / obj_dist;
	step = (double)(game->map.cardinal->tex->height - 1) / reflec_height;
	tex_x = (game->map.cardinal->tex->width - 1) * game->map.stripe;
	y = 0;
	while (y < game->mlx->height && y < game->mlx->height / 2 - reflec_height / 2)
	{
		mlx_put_pixel(game->img_a, x, y, game->map.ceiling_color);
		y++;
	}
	i = y - game->mlx->height / 2 + reflec_height / 2;
	while (y < game->mlx->height && y < game->mlx->height / 2 + reflec_height / 2)
	{
		tex_y = i * step;
		switch_pixel(game->img_a, x, y, &game->map.cardinal->tex->pixels[coor_to_pixel(game->map.cardinal->tex->width, tex_x, tex_y)]);
		i++;
		y++;
	}
	while (y < game->mlx->height)
	{
		mlx_put_pixel(game->img_a, x, y, game->map.floor_color);
		y++;
	}
}

double	fix_fisheye(double ray_dir, double view_dir, double wall_dist)
{
	return (wall_dist * cos(view_dir - ray_dir));
}

// @todo proper fov handling (cubes are not square)
int	render_world(t_game *game)
{
	double	wall_dist;
	double	ray_dir;
	double	fov;
	int		x;

	debug_print_player(&game->player);
	fov = (double)game->mlx->width / game->mlx->height;
	ray_dir = game->player.view_dir - (fov / 2);
	x = 0;
	while (x < game->mlx->width)
	{
		ray_dir += fov / game->mlx->width;
		wall_dist = cast_ray(game, ray_dir);
		wall_dist = fix_fisheye(ray_dir, game->player.view_dir, wall_dist);
		paint_reflection(game, wall_dist, x);
		x++;
	}
	printf("game->mlx->height: %d\n", game->mlx->height);
	// exit(0);
	return (SUCCESS);
}
