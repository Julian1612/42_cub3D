/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:46:52 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/10 15:20:16 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // cub3D structs

#define WALL_BLOCK 60
#define WALL_IDENT '1'

int	render_minimap(t_minimap *minimap, mlx_t *mlx, char **map)
{
	int	i;
	int	j;
	int	map_width;
	int	map_height;

	if (mlx_image_to_window(mlx, minimap->player, 60, 80) == ERROR)
		return (ERROR);
	if (mlx_image_to_window(mlx, minimap->view_dir, 0, 0) == ERROR)
		return (ERROR);
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
			{
				if (mlx_image_to_window(mlx, minimap->walls, i * WALL_BLOCK, j * WALL_BLOCK) == ERROR)
					return (ERROR);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (SUCCESS);
}

int	render_world(t_game *game)
{
	debug_print_game(game);
	cast_ray(game, game->player.view_dir);
	return (SUCCESS);
}
