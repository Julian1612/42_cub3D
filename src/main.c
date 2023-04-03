/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/01 18:52:56 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game, t_map, t_player, t_texture, t_weapon
#include "parser.h" // parser
#include "minimap.h"
#include "../libraries/mlx/include/MLX42/MLX42.h" // mlx functions
#include <stdlib.h> // malloc
#include <stdio.h> // @note remove, printf
#include <unistd.h> // @note remove, sleep
#include <stdbool.h> // bool
#include <math.h> // M_PI


// void play_music(void)
// {
// 	system("while :; do afplay sound_track/erika.mp3 && afplay sound_track/preussengloria.mp3 && afplay sound_track/march.mp3; done");
// }

// @todo implement player size so that player stops at wall
// @note fps engine correct like that?
// @todo fix resizing
// @note mlx_set_window_limit
// @todo fix camera plane
// @todo refactor raycaster to return hit coordinates instead of wall distance
// @todo implement doors
// @todo refactor hook functions for more readability (logic loop and render loop?)
// @todo go through code and refactor function parameters

int	main(int argc, char **argv)
{
	t_game	game;

	if (parser(&argc, argv, &game.map, &game.player))
		return (EXIT_FAILURE);
	if (initialize_mlx_data(&game) == ERROR)
		errexit_mlx_errno();
	if (mlx_loop_hook(game.mlx, &hook, &game) == false)
		errexit_mlx_errno();
	if (mlx_image_to_window(game.mlx, game.img_a, 0, 0) == ERROR)
		errexit_mlx_errno();
	if (initialize_minimap(&game) == ERROR)
		errexit_mlx_errno();
	if (initialize_map(&game) == ERROR)
		errexit_mlx_errno();
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
