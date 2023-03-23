/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:46:52 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/22 18:39:43 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include <stdio.h> // @note remove
#include <math.h> // PI

#define FOV 60

int	render_minimap(t_minimap *minimap, mlx_t *mlx, t_map *map)
{
	int	i;
	int	j;
	int	map_width;
	int	map_height;

	i = 0;
	j = 0;
	while ((i * MM_BLOCK_SIZE) < (map->height * MM_BLOCK_SIZE))
	{
		while ((j * MM_BLOCK_SIZE) < (map->width * MM_BLOCK_SIZE))
		{
			if (map->map[i][j] == WALL)
			{
				if (mlx_image_to_window(mlx, minimap->walls, j * MM_BLOCK_SIZE, i * MM_BLOCK_SIZE) == ERROR)
					return (ERROR);
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (mlx_image_to_window(mlx, minimap->player, 0, 0) == ERROR)
		return (ERROR);
	if (mlx_image_to_window(mlx, minimap->view_dir, 0, 0) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void	color_image(mlx_t *mlx, mlx_image_t *img, unsigned int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < img->height)
	{
		while (j < img->width)
		{
			mlx_put_pixel(img, j, i, color);
			j++;
		}
		j = 0;
		i++;
	}
}

void	paint_reflection(mlx_image_t *img, double obj_dist, int x)
{
	t_hexcolor	reflec_color;
	int			reflec_height;
	int			y;

	reflec_color = convert_to_hexcode(0, 150, 0, 255);
	if (obj_dist < 1)
		obj_dist = 1;
	reflec_height = (int)(HEIGHT / obj_dist);
	y = HEIGHT / 2 - reflec_height / 2;
	while (y < HEIGHT / 2 + reflec_height / 2)
	{
		mlx_put_pixel(img, x, y, reflec_color);
		y++;
	}
}

void	paint_ceilfloor(mlx_t *mlx, mlx_image_t *img, t_hexcolor ceil, t_hexcolor floor)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < HEIGHT)
	{
		while (j < WIDTH)
		{
			if (i < HEIGHT / 2)
				mlx_put_pixel(img, j, i, ceil);
			else
				mlx_put_pixel(img, j, i, floor);
			j++;
		}
		j = 0;
		i++;
	}
}

// @todo render ceilfloor and reflection together to avoid double paints
int	render_world(t_game *game)
{
	double	wall_dist;
	double	ray_dir;
	double	fov;
	int		i;

	debug_print_player(&game->player);
	paint_ceilfloor(game->mlx, game->img_a, game->map.ceiling_color, game->map.floor_color);
	fov = M_2_PI;
	ray_dir = game->player.view_dir - (fov / 2);
	i = 0;
	while (i < WIDTH)
	{
		ray_dir += fov / game->mlx->width;
		wall_dist = cast_ray(game, ray_dir);
		paint_reflection(game->img_a, wall_dist, i);
		i++;
	}
	return (SUCCESS);
}
