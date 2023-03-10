/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:51:13 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/09 21:27:17 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game
#include "minimap.h" // t_minimap
#include "../libraries/mlx/include/MLX42/MLX42.h" // MLX_functions
#include <stdio.h> // @note remove
#include <math.h> // cos, sin

void	keys(mlx_t *mlx, t_minimap *minimap, t_player *player)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		errexit_msg("Escape pressed. Exiting program.");
	}
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		minimap->player->instances[0].y += cos(player->player_angle) * 5;
		minimap->player->instances[0].x += sin(player->player_angle) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		minimap->player->instances[0].y -= cos(player->player_angle) * 5;
		minimap->player->instances[0].x -= sin(player->player_angle) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		minimap->player->instances[0].y += cos(player->player_angle - M_PI_2) * 5;
		minimap->player->instances[0].x += sin(player->player_angle - M_PI_2) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		minimap->player->instances[0].y += cos(player->player_angle + M_PI_2) * 5;
		minimap->player->instances[0].x += sin(player->player_angle + M_PI_2) * 5;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->player_angle += M_PI / 180 * 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->player_angle -= M_PI / 180 * 5;
	minimap->view_dir->instances[0].y = minimap->player->instances[0].y + 10 * cos(player->player_angle);
	minimap->view_dir->instances[0].x = minimap->player->instances[0].x + 10 * sin(player->player_angle);
}

void	game_loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	// mouse handling
	// minimap
	// collision
	// enemy
	keys(game->mlx, &game->minimap, &game->player);
}
