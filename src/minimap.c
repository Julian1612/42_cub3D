/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:37:20 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/09 21:27:17 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "../libraries/mlx/include/MLX42/MLX42.h" // mlx functions
#include "../libraries/libft/src/libft/libft.h" // ft_memset

#define PLAYER_SIZE 2
#define DIRECTION 2
#define WALL_BLOCK 60
#define WALL_IDENT '1'

static int	minimap_draw_walls(mlx_image_t *walls, mlx_t *mlx, char **map)
{
	int	i;
	int	j;
	int	map_width;
	int	map_height;

	i = 0;
	j = 0;
	// @todo replace with actual map width and height
	map_width = 16;
	map_height = 9;
	while ((i * WALL_BLOCK) < (map_height * WALL_BLOCK))
	{
		while ((j * WALL_BLOCK) < (map_width * WALL_BLOCK))
		{
			if (map[i][j] == WALL_IDENT)
				mlx_image_to_window(mlx, walls, i * WALL_BLOCK, j * WALL_BLOCK);
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int	minimap_initialize(t_minimap *minimap, mlx_t *mlx, char **map)
{
	minimap->player = mlx_new_image(mlx, PLAYER_SIZE, PLAYER_SIZE);
	minimap->view_dir = mlx_new_image(mlx, DIRECTION, DIRECTION);
	minimap->walls = mlx_new_image(mlx, WALL_BLOCK, WALL_BLOCK);
	if (!minimap->player || !minimap->view_dir || !minimap->walls)
		return (ERROR);
	minimap->player->pixels = ft_memset(minimap->player->pixels, 255,
			minimap->player->width * minimap->player->height * sizeof(int));
	minimap->view_dir->pixels = ft_memset(minimap->view_dir->pixels, 255,
			minimap->view_dir->width * minimap->view_dir->height * sizeof(int));
	minimap->walls->pixels = ft_memset(minimap->walls->pixels, 255,
			minimap->walls->width * minimap->walls->height * sizeof(int));
	if (!minimap->player->pixels || !minimap->view_dir->pixels
		|| !minimap->walls->pixels)
		return (ERROR);
	if (mlx_image_to_window(mlx, minimap->player, 60, 80) == ERROR)
		return (ERROR);
	if (mlx_image_to_window(mlx, minimap->view_dir, 0, 0) == ERROR)
		return (ERROR);
	if (minimap_draw_walls(minimap->walls, mlx, map) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
