/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:46:52 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/24 18:40:33 by lorbke           ###   ########.fr       */
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

t_hexcolor	get_reflec_color(enum e_cardinals cardinal)
{
	t_hexcolor	reflec_color;

	if (cardinal == NORTH)
		reflec_color = convert_to_hexcode(0, 150, 0, 255);
	else if (cardinal == EAST)
		reflec_color = convert_to_hexcode(0, 0, 150, 255);
	else if (cardinal == SOUTH)
		reflec_color = convert_to_hexcode(150, 0, 0, 255);
	else if (cardinal == WEST)
		reflec_color = convert_to_hexcode(150, 150, 0, 255);
	return (reflec_color);
}

void	paint_reflection(enum e_cardinals cardinal, mlx_image_t *img, t_hexcolor ceil, t_hexcolor floor, double obj_dist, int x)
{
	t_hexcolor	reflec_color;
	int			reflec_height;
	int			y;

	reflec_color = get_reflec_color(cardinal);
	if (obj_dist < 1)
		obj_dist = 1;
	reflec_height = (int)(HEIGHT / obj_dist);
	y = 0;
	while (y < HEIGHT / 2 - reflec_height / 2)
	{
		mlx_put_pixel(img, x, y, ceil);
		y++;
	}
	while (y < HEIGHT / 2 + reflec_height / 2)
	{
		mlx_put_pixel(img, x, y, reflec_color);
		y++;
	}
	while (y < HEIGHT)
	{
		mlx_put_pixel(img, x, y, floor);
		y++;
	}
}

int	render_world(t_game *game)
{
	double	wall_dist;
	double	ray_dir;
	double	fov;
	int		i;

	debug_print_player(&game->player);
	fov = 1;
	ray_dir = game->player.view_dir - (fov / 2);
	i = 0;
	while (i < WIDTH)
	{
		ray_dir += fov / game->mlx->width;
		wall_dist = cast_ray(game, ray_dir);
		// @note prevent fisheye effect
		wall_dist *= cos(ray_dir - game->player.view_dir);
		paint_reflection(game->cardinal, game->img_a, game->map.ceiling_color, game->map.floor_color, wall_dist, i);
		i++;
	}
	return (SUCCESS);
}
