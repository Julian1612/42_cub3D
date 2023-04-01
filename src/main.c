/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/01 21:27:43 by lorbke           ###   ########.fr       */
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
	static char			*map[17] =
	{
		"1111111111111111",
		"1000100000000001",
		"1000100000000001",
		"1000100000000011",
		"1000000000000111",
		"1000100000001111",
		"1000100000011111",
		"1100100000111111",
		"1111111111111111"
	};
	static t_texture	objects[4] =
	{
		{"textures/north.png", NULL},
		{"textures/east.png", NULL},
		{"textures/south.png", NULL},
		{"textures/west.png", NULL}
	};

	game->map.map = map;
	game->map.objects = objects;
	game->map.ceiling_color = convert_to_hexcode(0, 0, 0, 0);
	game->map.floor_color = convert_to_hexcode(0, 0, 0, 150);
	game->player.x = 2;
	game->player.y = 2;
	game->player.view_dir = 0;
	game->player.size = 1;
	game->player.weapon = NULL;
	return (SUCCESS);
}

// @todo implement player size so that player stops at wall
// @todo implement fps engine
// @todo fix resizing
// @todo fix camera plane
// @todo refactor raycaster to return hit coordinates instead of wall distance
// @todo implement doors

int	main(int argc, char **argv)
{
	t_game	game;

	if (test_parse(&game))
		return (EXIT_FAILURE);
	if (initialize_mlx_data(&game) == ERROR)
		errexit_mlx_errno();
	if (mlx_loop_hook(game.mlx, &hook, &game) == false)
		errexit_mlx_errno();
	if (mlx_image_to_window(game.mlx, game.img_a, 0, 0) == ERROR)
		errexit_mlx_errno();
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
