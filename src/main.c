/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/10 17:44:00 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game, t_map, t_player, t_texture, t_weapon
#include "../libraries/mlx/include/MLX42/MLX42.h" // mlx functions
#include <stdlib.h> // malloc
#include <stdio.h> // @note remove, printf
#include <unistd.h> // @note remove, sleep
#include <stdbool.h> // bool
#include <math.h> // M_PI
#include <string.h> // @note remove, memcpy

void	play_music(void)
{
	system("afplay ./sound_track/preussengloria.mp3 &");
}

int	free_parser(t_map *map_data)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		free(map_data->objects[i].path);
		i++;
	}
	i = 0;
	while (map_data->map[i] != NULL)
	{
		free(map_data->map[i]);
		i++;
	}
	free(map_data->map);
	return (EXIT_SUCCESS);
}

// we need to free the struct form the parser at the end of main
int	main(int argc, char **argv)
{
	t_game		game;

	if (parser(&argc, argv, &game))
		return (EXIT_FAILURE);
	if (initialize_mlx_data(&game) == ERROR)
		errexit_mlx_errno();
	if (mlx_loop_hook(game.mlx, &hook, &game) == false)
		errexit_mlx_errno();
	if (mlx_image_to_window(game.mlx, game.img_world, 0, 0) == ERROR)
		errexit_mlx_errno();
	if (mlx_image_to_window(game.mlx, game.img_hud, 0, 0) == ERROR)
		errexit_mlx_errno();
	if (initialize_minimap(&game) == ERROR)
		errexit_mlx_errno();
	if (initialize_start_screen(&game) == ERROR)
		errexit_mlx_errno();
	draw_background(&game.start_screen);
	mlx_loop(game.mlx);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_parser(&game.map);
	return (EXIT_SUCCESS);
}
