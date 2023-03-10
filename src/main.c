/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/10 15:25:39 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game, t_map, t_player, t_texture, t_weapon
#include "../libraries/mlx/include/MLX42/MLX42.h" // mlx functions
#include <stdlib.h> // malloc
#include <stdio.h> // printf
#include <stdbool.h> // bool
#include <math.h> // M_PI

int	test_parse(t_game *game)
{
	static char	*map[17] = {"1111111111111111",
					"1000100000000001",
					"1000100000000001",
					"1000100000000011",
					"1000000000000111",
					"1000100000001111",
					"1000100000011111",
					"1100100000111111",
					"1111111111111111"};

	game->map.map = map;
	game->map.west.path = "textures/east.xpm42";
	game->map.east.path = "textures/east.xpm42";
	game->map.south.path = "textures/east.xpm42";
	game->map.north.path = "textures/east.xpm42";
	game->map.ceiling_color = 0x00FF0000;
	game->map.floor_color = 0x000000FF;
	game->player.x = 0;
	game->player.y = 0;
	game->player.view_dir = M_PI;
	game->player.weapon = NULL;
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (test_parse(&game))
		return (EXIT_FAILURE);
	if (initialize_mlx_all(&game) == ERROR)
		errexit_mlx_errno();
	// if (render_minimap(&game.minimap, game.mlx, game.map.map) == ERROR)
	// 	errexit_mlx_errno();
	if (mlx_loop_hook(game.mlx, &hook, &game) == false)
		errexit_mlx_errno();
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
