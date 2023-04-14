/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/14 20:31:32 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game, t_map, t_player, t_texture, t_weapon
#include "enemy.h" // t_enemy
#include "loop.h" // loop
#include "parser.h" // parser
#include "../libraries/mlx/include/MLX42/MLX42.h" // mlx functions
#include <stdlib.h> // malloc
#include <stdbool.h> // bool
#include <math.h> // M_PI

// static int	free_data(t_map *map_data)
// {
// 	int	i;

// 	i = 0;
// 	while (map_data->arr[i] != NULL)
// 	{
// 		free(map_data->arr[i]);
// 		i++;
// 	}
// 	free(map_data->arr);
// 	return (EXIT_SUCCESS);
// }

static void	initialize_player_data(t_player *player)
{
	static t_weapon	gun = {
		.damage = 10,
		.range = 10,
		.reload_time = 1,
		.frame.time_of_last = 0,
		.frame.curr = HUD_GUN1,
	};

	player->health = 100;
	player->mov_speed = 0.1;
	player->rot_speed = 0.05;
	player->weapon = &gun;
}

static void	initialize_sound_ids(int *sound_id)
{
	int	i;

	i = 0;
	while (i < SOUND_MAX)
	{
		sound_id[i] = 0;
		i++;
	}
}

static int	put_images_to_window(t_game *game)
{
	if (mlx_image_to_window(game->mlx, game->img_world, 0, 0) == ERROR)
		return (ERROR);
	if (mlx_image_to_window(game->mlx, game->hud.img, 0, 0) == ERROR)
		return (ERROR);
	if (mlx_image_to_window(game->mlx, game->start.img, 0, 0) == ERROR)
		return (ERROR);
	if (mlx_image_to_window(game->mlx, game->lose.img, 0, 0) == ERROR)
		return (ERROR);
	if (mlx_image_to_window(game->mlx, game->win.img, 0, 0) == ERROR)
		return (ERROR);
	if (mlx_image_to_window(game->mlx, game->minimap.minimap_walls, 0, 0)
		== ERROR)
		return (ERROR);
	return (SUCCESS);
}

// @todo check leaks (especially texture leaks)
// @todo refactor mandatory
// @todo enemy cooldown

int	main(int argc, char **argv)
{
	t_game		game;

	if (parser(&argc, argv, &game))
		return (EXIT_FAILURE);
	if (initialize_mlx_data(&game) == ERROR)
		errexit_mlx_errno();
	if (mlx_loop_hook(game.mlx, &loop, &game) == false)
		errexit_mlx_errno();
	if (put_images_to_window(&game) == ERROR)
		errexit_mlx_errno();
	initialize_player_data(&game.player);
	initialize_sound_ids(game.sound_id);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
