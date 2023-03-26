/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:46:52 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/26 03:22:06 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include <stdio.h> // @note remove
#include <math.h> // PI
#include <string.h> // @note memmove, remove

#define FOV 60

void	paint_reflection(t_game *game, double obj_dist, int x)
{
	int			reflec_height;
	int			y;
	int			i;

	if (obj_dist < 1)
		obj_dist = 1;
	reflec_height = (int)(HEIGHT / obj_dist);
	y = 0;
	while (y < HEIGHT / 2 - reflec_height / 2)
	{
		mlx_put_pixel(game->img_a, x, y, game->map.ceiling_color);
		y++;
	}
	i = 0;
	while (y < HEIGHT / 2 + reflec_height / 2)
	{
		game->img_a->pixels[y * WIDTH - 1 + x] = game->map.tex_stripe[i];
		i++;
		y++;
	}
	while (y < HEIGHT)
	{
		mlx_put_pixel(game->img_a, x, y, game->map.floor_color);
		y++;
	}
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
		paint_reflection(game, wall_dist, x);
		x++;
	}
	return (SUCCESS);
}
