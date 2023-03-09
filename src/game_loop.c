/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:51:13 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/09 19:46:09 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game
#include "../libraries/mlx/include/MLX42/MLX42.h" // mlx_functions
#include <stdio.h> // @note remove

void	draw(t_game *game)
{
	game->img_a = mlx_texture_to_image(game->mlx, game->map.west.texture);
	mlx_image_to_window(game->mlx, game->img_a, 0, 0);
}

void	keys(t_game *game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(game->mlx);
		errexit_msg("Escape pressed. Exiting program.");
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		game->img_a->instances[0].y -= 3;
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		game->img_a->instances[0].y += 3;
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->img_a->instances[0].x -= 3;
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->img_a->instances[0].x += 3;
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	draw(game);
	// mouse handling
	// minimap
	// collision
	// enemy
	keys(game);
}
