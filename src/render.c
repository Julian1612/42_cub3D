/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:46:52 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/30 20:23:12 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include "../libraries/libft/src/libft/libft.h" // ft_memcpy
#include <stdio.h> // @note remove
#include <math.h> // PI
#include <string.h> // @note memmove, remove
#include <stdlib.h> // @note exit, remove
#include <unistd.h> // @note remove

static void	draw_ceiling(t_game *game, int wall_height, int x_img)
{
	int	ceil_height;
	int	y_img;

	ceil_height = game->img_a->height / 2 - wall_height / 2;
	y_img = 0;
	while (y_img < ceil_height)
	{
		mlx_put_pixel(game->img_a, x_img, y_img, game->map.ceiling_color);
		y_img++;
	}
}

static void	draw_wall(t_game *game, int wall_height, int x_img, t_rayhit *hit)
{
	double	scale;
	int		x_tex;
	int		y_tex_iter;
	int		y_img;

	scale = (double)(game->map.objects[hit->wall_id].tex->height - 1) / wall_height;
	x_tex = (game->map.objects[hit->wall_id].tex->width - 1) * hit->stripe;
	y_img = game->img_a->height / 2 - wall_height / 2;
	y_tex_iter = 0;
	while (y_img < game->img_a->height / 2 + wall_height / 2)
	{
		// @todo improve this ugly shit
		ft_memcpy(&game->img_a->pixels[
			coor_to_pixel(game->img_a->width, x_img, y_img)],
			&game->map.objects[hit->wall_id].tex->pixels[
			coor_to_pixel(game->map.objects[hit->wall_id].tex->width,
				x_tex, y_tex_iter * scale)],
			4);
		y_tex_iter++;
		y_img++;
	}
}

static void	draw_floor(t_game *game, int wall_height, int x_img)
{
	int	floor_start;
	int	y_img;

	floor_start = game->img_a->height / 2 + wall_height / 2;
	y_img = floor_start;
	while (y_img < game->img_a->height)
	{
		mlx_put_pixel(game->img_a, x_img, y_img, game->map.floor_color);
		y_img++;
	}
}

static double	fix_fisheye(double ray_dir, double view_dir, double wall_dist)
{
	double	difference;

	difference = view_dir - ray_dir;
	wall_dist *= cos(difference);
	return (wall_dist);
}

// @todo fix segfault when running into wall
int	render_world(t_game *game)
{
	t_rayhit	ray_hit;
	double		ray_dir;
	double		wall_height;
	double		fov;
	int			x_img;

	debug_print_player(&game->player);
	fov = (double)game->img_a->width / game->img_a->height;
	ray_dir = game->player.view_dir - (fov / 2);
	x_img = 0;
	while (x_img < game->img_a->width)
	{
		ray_dir += fov / game->img_a->width;
		cast_ray(&ray_hit, game, ray_dir);
		ray_hit.distance
			= fix_fisheye(ray_dir, game->player.view_dir, ray_hit.distance);
		wall_height = game->img_a->height / ray_hit.distance;
		draw_ceiling(game, wall_height, x_img);
		draw_wall(game, wall_height, x_img, &ray_hit);
		draw_floor(game, wall_height, x_img);
		x_img++;
	}
	return (SUCCESS);
}
