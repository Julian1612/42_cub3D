/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/09 20:02:36 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game, t_map, t_player, t_texture, t_weapon
#include "../libraries/mlx/include/MLX42/MLX42.h" // mlx functions
#include <stdlib.h> // malloc
#include <stdio.h> // printf
#include <stdbool.h> // bool

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
	game->player.x = 1.5;
	game->player.y = 1.5;
	game->player.player_angle = 0;
	game->player.weapon = NULL;
	return (SUCCESS);
}

int	initialize_mlx_data(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	game->img_a = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (game->mlx == NULL || game->img_a == NULL)
		return (ERROR);
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

int	main(int argc, char **argv)
{
	t_game	game;

	if (test_parse(&game))
		return (EXIT_FAILURE);
	if (initialize_mlx_data(&game) == ERROR)
		errexit_mlx_errno();
	if (mlx_loop_hook(game.mlx, &game_loop, &game) == false)
		errexit_mlx_errno();
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
