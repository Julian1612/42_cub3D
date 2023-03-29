/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/29 23:53:33 by lorbke           ###   ########.fr       */
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
	game->map.width = 16;
	game->map.height = 9;
	game->map.west.path = "textures/west.png";
	game->map.east.path = "textures/east.png";
	game->map.south.path = "textures/south.png";
	game->map.north.path = "textures/north.png";
	game->map.ceiling_color = convert_to_hexcode(0, 0, 0, 0);
	game->map.floor_color = convert_to_hexcode(0, 0, 0, 150);
	game->player.x = 2;
	game->player.y = 2;
	game->player.view_dir = 0;
	game->player.weapon = NULL;
	return (SUCCESS);
}

// @todo implement player size so that player stops at wall
// @todo implement fps engine
// @todo resizing still buggy
// @todo refactor raycaster to return hit coordinates instead of wall distance

int	main(int argc, char **argv)
{
	t_game	game;

	if (test_parse(&game))
		return (EXIT_FAILURE);
	if (initialize_mlx_all(&game) == ERROR)
		errexit_mlx_errno();
	if (mlx_loop_hook(game.mlx, &hook, &game) == false)
		errexit_mlx_errno();
	if (mlx_image_to_window(game.mlx, game.img_a, 0, 0) == ERROR)
		errexit_mlx_errno();
	// uint32_t xy[2] = {1, 1};
	// u_int32_t wh[2] = {10, 10};
	// mlx_image_t *test = mlx_texture_area_to_image(game.mlx, game.map.north.texture, xy, xy);
	// mlx_image_to_window(game.mlx, test, 0, 0);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
