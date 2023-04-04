/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:46:52 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/03 18:50:30 by lorbke           ###   ########.fr       */
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
	while (y_img < game->img_a->height && y_img < ceil_height)
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
	y_tex_iter = 0;
	y_img = game->img_a->height / 2 - wall_height / 2;
	if (y_img < 0)
	{
		y_tex_iter = y_img * -1;
		y_img = 0;
	}
	while (y_img < game->img_a->height && y_img < game->img_a->height / 2 + wall_height / 2)
	{
		// @todo improve this ugly shit
		ft_memcpy(&game->img_a->pixels
		[coor_to_pixel(game->img_a->width, x_img, y_img)],
			&game->map.objects[hit->wall_id].tex->pixels
		[coor_to_pixel(game->map.objects[hit->wall_id].tex->width,
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
	while (y_img < game->img_a->height && y_img < game->img_a->height)
	{
		mlx_put_pixel(game->img_a, x_img, y_img, game->map.floor_color);
		y_img++;
	}
}

static double	fix_fisheye(double ray_angle, double view_angle, double wall_dist)
{
	double	difference;

	difference = view_angle - ray_angle;
	wall_dist *= cos(difference);
	return (wall_dist);
}

static void set_ray_dir(t_coor *ray_dir, double x, int img_width, double view_angle)
{
	static const double	plane_x = 0;
	static const double	plane_y = 0.66;
	double				camera_x;

	camera_x = 2 * x / img_width - 1;
	ray_dir->x = sin(view_angle) + plane_x * camera_x;
	ray_dir->y = cos(view_angle) + plane_y * camera_x;
}

// @todo fix fisheye for angles > 60
int	render_world(t_game *game)
{
	t_rayhit	ray_hit;
	t_coor		ray_dir;
	double		wall_height;
	int			x_img;

	debug_print_player(&game->player);
	x_img = 0;
	while (x_img < game->img_a->width)
	{
		set_ray_dir(&ray_dir, x_img, game->img_a->width, game->player.view_angle);
		cast_ray(&ray_hit, game, ray_dir);
		wall_height = game->img_a->height / ray_hit.dist;
		draw_ceiling(game, wall_height, x_img);
		draw_wall(game, wall_height, x_img, &ray_hit);
		draw_floor(game, wall_height, x_img);
		x_img++;
	}
	// init_sprite(game);
	return (SUCCESS);
}
