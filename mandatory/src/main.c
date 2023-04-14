/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/15 00:54:10 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game, t_map, t_player, t_texture, t_weapon
#include "loop.h" // loop
#include "parser.h" // parser
#include "../libraries/mlx42/include/MLX42/MLX42.h" // mlx functions
#include <stdlib.h> // malloc
#include <stdbool.h> // bool
#include <math.h> // M_PI

static int	free_textures(t_tex *textures)
{
	int	i;

	i = 0;
	while (i < LAST)
	{
		mlx_delete_texture(textures[i].tex);
		free(textures[i].path);
		i++;
	}
	return (ERROR);
}

static void	initialize_player_data(t_player *player)
{
	player->mov_speed = 0.1;
	player->rot_speed = 0.05;
}

static int	put_images_to_window(t_game *game)
{
	if (mlx_image_to_window(game->mlx, game->img_world, 0, 0) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

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
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_textures(game.map.textures);
	return (EXIT_SUCCESS);
}
