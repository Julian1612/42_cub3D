/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:51:13 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/23 18:07:40 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game
#include "../libraries/mlx/include/MLX42/MLX42.h" // MLX_functions
#include <stdio.h> // @note remove
#include <math.h> // cos, sin

#define MOV_SPEED 10 // @note the higher, the slower
#define ROT_SPEED 1 // @note the higher, the slower

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
		player->y += cos(player->view_dir) / MOV_SPEED;
		player->x += sin(player->view_dir) / MOV_SPEED;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		// @note offset = unit circle value of view_dir * speed
		player->y -= cos(player->view_dir) / MOV_SPEED;
		player->x -= sin(player->view_dir) / MOV_SPEED;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		player->y += cos(player->view_dir - M_PI_2) / MOV_SPEED;
		player->x += sin(player->view_dir - M_PI_2) / MOV_SPEED;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		// @note radian rotated by 90 degrees to offset movement
		player->y += cos(player->view_dir + M_PI_2) / MOV_SPEED;
		player->x += sin(player->view_dir + M_PI_2) / MOV_SPEED;
	}
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->view_dir += M_PI / 180 / ROT_SPEED; // @note radian rotated by 5 degrees (1pi = 180 degrees)
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->view_dir -= M_PI / 180 / ROT_SPEED;
	if (mlx_is_key_down(mlx, MLX_KEY_1))
		player->view_dir = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_2))
		player->view_dir = M_PI / 2;
	if (mlx_is_key_down(mlx, MLX_KEY_3))
		player->view_dir = M_PI;
	if (mlx_is_key_down(mlx, MLX_KEY_4))
		player->view_dir = M_PI * 1.5;
}

// void	keys(mlx_t *mlx, t_minimap *minimap, t_player *player)
// {
// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 	{
// 		mlx_close_window(mlx);
// 		errexit_msg("Escape pressed. Exiting program.");
// 	}
// 	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(mlx);
// 	if (mlx_is_key_down(mlx, MLX_KEY_W))
// 	{
// 		player->y += cos(player->view_dir) * SPEED;
// 		player->x += sin(player->view_dir) * SPEED;
// 	}
// 	if (mlx_is_key_down(mlx, MLX_KEY_S))
// 	{
// 		// @note offset = unit circle value of view_dir * speed
// 		player->y -= cos(player->view_dir) * SPEED;
// 		player->x -= sin(player->view_dir) * SPEED;
// 	}
// 	if (mlx_is_key_down(mlx, MLX_KEY_D))
// 	{
// 		player->y += cos(player->view_dir - M_PI_2) * SPEED;
// 		player->x += sin(player->view_dir - M_PI_2) * SPEED;
// 	}
// 	if (mlx_is_key_down(mlx, MLX_KEY_A))
// 	{
// 		// @note radian rotated by 90 degrees to offset movement
// 		player->y += cos(player->view_dir + M_PI_2) * SPEED;
// 		player->x += sin(player->view_dir + M_PI_2) * SPEED;
// 	}
// 	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
// 		player->view_dir += M_PI / 180 * SPEED; // @note radian rotated by 5 degrees (1pi = 180 degrees)
// 	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
// 		player->view_dir -= M_PI / 180 * SPEED;
// 		if (mlx_is_key_down(mlx, MLX_KEY_1))
// 		player->view_dir = 0;
// 	if (mlx_is_key_down(mlx, MLX_KEY_2))
// 		player->view_dir = M_PI / 2;
// 	if (mlx_is_key_down(mlx, MLX_KEY_3))
// 		player->view_dir = M_PI;
// 	if (mlx_is_key_down(mlx, MLX_KEY_4))
// 		player->view_dir = M_PI * 1.5;
// }

void	hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	// mouse handling
	// minimap
	// collision
	// enemy
	keys(game->mlx, &game->minimap, &game->player);
	render_world(game);
}
