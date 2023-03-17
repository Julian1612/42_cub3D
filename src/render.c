/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:46:52 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/17 13:14:39 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs
#include <stdio.h> // @note remove

#define WALL_IDENT '1'
#define FOV 60

int	render_minimap(t_minimap *minimap, mlx_t *mlx, t_map *map)
{
	int	i;
	int	j;
	int	map_width;
	int	map_height;

	i = 0;
	j = 0;
	// @todo replace with actual map width and height
	while ((i * MM_BLOCK_SIZE) < (map->height * MM_BLOCK_SIZE))
	{
		while ((j * MM_BLOCK_SIZE) < (map->width * MM_BLOCK_SIZE))
		{
			if (map->map[i][j] == WALL_IDENT)
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

// int	render_minimap(t_minimap *minimap, mlx_t *mlx, char **map)
// {
// 	int	i;
// 	int	j;
// 	int	map_width;
// 	int	map_height;

// 	i = 0;
// 	j = 0;
// 	// @todo replace with actual map width and height
// 	map_width = 16;
// 	map_height = 9;
// 	while ((i * BLOCK_SIZE) < (map_height * BLOCK_SIZE))
// 	{
// 		while ((j * BLOCK_SIZE) < (map_width * BLOCK_SIZE))
// 		{
// 			if (i % 2 == 0 && j % 2 == 0)
// 			{
// 				if (mlx_image_to_window(mlx, minimap->walls, i * BLOCK_SIZE, j * BLOCK_SIZE) == ERROR)
// 					return (ERROR);
// 			}
// 			if (i % 2 != 0 && j % 2 != 0)
// 			{
// 				if (mlx_image_to_window(mlx, minimap->walls, i * BLOCK_SIZE, j * BLOCK_SIZE) == ERROR)
// 					return (ERROR);
// 			}
// 			j++;
// 		}
// 		j = 0;
// 		i++;
// 	}
// 	if (mlx_image_to_window(mlx, minimap->player, 0, 0) == ERROR)
// 		return (ERROR);
// 	if (mlx_image_to_window(mlx, minimap->view_dir, 0, 0) == ERROR)
// 		return (ERROR);
// 	return (SUCCESS);
// }

int	render_world(t_game *game)
{
	debug_print_player(&game->player);
	printf("ray length: %f\n", cast_ray(game, game->player.view_dir));
	return (SUCCESS);
}
