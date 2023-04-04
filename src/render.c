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

// @todo rename variables so that x and ys come last
static void	draw_wall(t_game *game, int wall_height, int x_img, t_rayhit *hit)
{
	double	scale;
	int		x_tex;
	int		y_tex_iter;
	int		y_img;

	scale = (double)(game->map.textures[hit->tex_id].tex->height) / wall_height;
	x_tex = (game->map.textures[hit->tex_id].tex->width) * hit->stripe;
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
			&game->map.textures[hit->tex_id].tex->pixels
		[coor_to_pixel(game->map.textures[hit->tex_id].tex->width,
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

static void set_ray_dir(t_vec *ray_dir, double x, int img_width, t_player *player)
{
	double				camera_x;

	camera_x = 2 * (img_width - x - 1) / img_width - 1;
	ray_dir->x = player->dir.x + player->cplane.x * camera_x;
	ray_dir->y = player->dir.y + player->cplane.y * camera_x;
}

static void	scale_cplane(t_vec *cplane, int img_width, int img_height)
{
	double	temp;
	double	temp2;
	double	angle;

	angle = atan2(cplane->x, cplane->y);
	cplane->x = 0;
	cplane->y = (double)img_width / img_height / 2;
	cplane->x = 0 * cos(angle) - cplane->y * sin(angle);
	cplane->y = 0 * sin(angle) + cplane->y * cos(angle);
}

// @todo fix scale plane function
int	render_world(t_game *game)
{
	t_rayhit	ray_hit;
	t_vec		ray_dir;
	double		wall_height[game->img_a->width];
	int			x_img;

	debug_print_player(&game->player);
	// scale_cplane(&game->player.cplane, game->img_a->width, game->img_a->height);
	x_img = 0;
	while (x_img < game->img_a->width)
	{
		set_ray_dir(&ray_dir, x_img, game->img_a->width, &game->player);
		cast_ray(&ray_hit, game, ray_dir);
		wall_height[x_img] = game->img_a->height / ray_hit.dist;
		draw_ceiling(game, wall_height[x_img], x_img);
		draw_wall(game, wall_height[x_img], x_img, &ray_hit);
		draw_floor(game, wall_height[x_img], x_img);
		x_img++;
	}
	render_sprite(game, wall_height);
	return (SUCCESS);
}
