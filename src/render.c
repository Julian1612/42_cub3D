/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:46:52 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/30 16:13:01 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include <stdio.h> // @note remove
#include <math.h> // PI
#include <string.h> // @note memmove, remove
#include <stdlib.h> // @note exit, remove
#include <unistd.h> // @note remove

static void	paint_reflection(t_game *game, double obj_dist, int x)
{
	double	reflec_height;
	int		y;
	int		i;
	double	step;
	int		tex_x;
	int		tex_y;

	reflec_height = game->mlx->height / obj_dist;
	step = (game->map.cardinal->tex->height - 1) / reflec_height;
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

static double	fix_fisheye(double ray_dir, double view_dir, double wall_dist, double fov)
{
	double	difference;

	difference = view_dir - ray_dir;
	wall_dist *= cos(difference);
	return (wall_dist);
}

int	render_world(t_game *game)
{
	t_rayhit	ray_hit;
	double		ray_dir;
	double		fov;
	int			x;

	debug_print_player(&game->player);
	fov = (double)game->mlx->width / game->mlx->height;
	ray_dir = game->player.view_dir - (fov / 2);
	x = 0;
	while (x < game->mlx->width)
	{
		ray_dir += fov / game->mlx->width;
		ray_hit = cast_ray(game, ray_dir);
		ray_hit.distance = fix_fisheye(ray_dir, game->player.view_dir, ray_hit.distance, fov);
		paint_reflection(game, ray_hit.distance, x);
		x++;
	}
	return (SUCCESS);
}
