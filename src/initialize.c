/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:24:25 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/01 18:38:45 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game, t_map, t_player, t_texture, t_weapon
#include "../libraries/mlx/include/MLX42/MLX42.h" // mlx functions
#include "../libraries/libft/src/libft/libft.h" // ft_strlen
#include <stdlib.h> // NULL
#include <stdbool.h> // bool
#include <math.h> // M_PI
#include "minimap.h"
#include <stdio.h> // printf

#define DIRECTION 2

int	initialize_minimap(t_game *game)
{
	get_map_measures(game);
	game->minimap.smm_walls = mlx_new_image(game->mlx,
			MINIMAP_WALL_SIZE * 5, MINIMAP_WALL_SIZE * 5);
	if (game->minimap.smm_walls == NULL)
		return (ERROR);
	if (mlx_image_to_window(game->mlx, game->minimap.smm_walls, 0, 0) == -1)
		return (ERROR);
	return (SUCCESS);
}

int	initialize_map(t_game *game)
{
	double	wall_size;
	int		height_square;
	int		width_square;

	get_map_measures(game);
	wall_size = get_wall_size_map(&game->minimap);
	height_square = (WIDTH - (game->minimap.width * wall_size)) / 2;
	width_square = (HEIGHT - (game->minimap.height * wall_size)) / 2;
	game->minimap.player = mlx_new_image(game->mlx, wall_size / 2, wall_size / 2);
	game->minimap.lmm_walls = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (game->minimap.player == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(game->mlx, game->minimap.player,height_square, width_square) == -1)
		return (EXIT_FAILURE);
	if (game->minimap.lmm_walls == NULL)
		return (EXIT_FAILURE);
	if (mlx_image_to_window(game->mlx, game->minimap.lmm_walls, height_square, width_square) == -1)
		return (EXIT_FAILURE);
	return (SUCCESS);
}

static int	initialize_textures(t_game *game)
{
	game->map.east.xpm = mlx_load_xpm42(game->map.east.path);
	game->map.west.xpm = mlx_load_xpm42(game->map.west.path);
	game->map.south.xpm = mlx_load_xpm42(game->map.south.path);
	game->map.north.xpm = mlx_load_xpm42(game->map.north.path);
	if (game->map.west.xpm == NULL || game->map.east.xpm == NULL
		|| game->map.south.xpm == NULL || game->map.north.xpm == NULL)
		return (ERROR);
	game->map.west.texture = &game->map.west.xpm->texture;
	game->map.east.texture = &game->map.east.xpm->texture;
	game->map.south.texture = &game->map.south.xpm->texture;
	game->map.north.texture = &game->map.north.xpm->texture;
	// @todo sprite initialization
	return (SUCCESS);
}

int	initialize_mlx_all(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	game->img_a = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (game->mlx == NULL || game->img_a == NULL)
		return (ERROR);
	// if (initialize_textures(game) == ERROR)
	// 	return (ERROR);
	// if (initialize_minimap(&game->minimap, game->mlx, game->map.map) == ERROR)
	// 	return (ERROR);
	return (SUCCESS);
}

