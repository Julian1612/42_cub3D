/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/03/31 09:39:15 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3D.h" // t_game
#include "minimap.h"
#include "../libraries/mlx/include/MLX42/MLX42.h" // MLX_functions
#include <stdio.h> // @note remove
#include <math.h> // cos, sin

#define SPEED 1
#define DIVIDE 10 // @note why is this needed? fuck this shit

///////////////////////

// erstes und zweites if bewegt jetzt den spieler an sich und loscht die lezten bilder
// muss noch alles angepasst werden so das w a s d passen und die pfeiltasten auch

void on_keypress(mlx_key_data_t keydata, void* param)
{
	t_game	*game;

	game = (t_game *)param;
	printf("visible: %d\n", game->minimap.visible);
	if (keydata.key == MLX_KEY_F && keydata.action == 0 && game->minimap.visible == 0)
	{
		printf("li\n");
		game->minimap.smm_walls->instances[0].enabled = false;
		game->minimap.lmm_walls->instances[0].enabled = true;
		game->minimap.player->instances[0].enabled = true;
		game->minimap.visible = 1;
	}
	else if (keydata.key == MLX_KEY_F && keydata.action == 0 && game->minimap.visible == 1)
	{
		printf("la\n");
		game->minimap.smm_walls->instances[0].enabled = true;
		game->minimap.lmm_walls->instances[0].enabled = false;
		game->minimap.player->instances[0].enabled = false;
		game->minimap.visible = 0;
	}
}

void	keys(t_game *game, t_minimap *minimap, t_player *player)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE) || mlx_is_key_down(game->mlx, MLX_KEY_Q))
	{
		mlx_close_window(game->mlx);
		errexit_msg("Escape pressed. Exiting program.");
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		player->y += cos(player->view_dir) * SPEED / DIVIDE;
		player->x += sin(player->view_dir) * SPEED / DIVIDE;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		player->y -= cos(player->view_dir) * SPEED / DIVIDE;
		player->x -= sin(player->view_dir) * SPEED / DIVIDE;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		// @note radian rotated by 90 degrees to offset movement
		player->y += cos(player->view_dir + M_PI_2) * SPEED / DIVIDE;
		player->x += sin(player->view_dir + M_PI_2) * SPEED / DIVIDE;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		player->y += cos(player->view_dir - M_PI_2) * SPEED / DIVIDE;
		player->x += sin(player->view_dir - M_PI_2) * SPEED / DIVIDE;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		player->view_dir += M_PI / 180 * SPEED; // @note radian rotated by 5 degrees (1pi = 180 degrees)
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		player->view_dir -= M_PI / 180 * SPEED;
	if (mlx_is_key_down(game->mlx, MLX_KEY_1))
		player->view_dir = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_2))
		player->view_dir = M_PI / 2;
	if (mlx_is_key_down(game->mlx, MLX_KEY_3))
		player->view_dir = M_PI;
	if (mlx_is_key_down(game->mlx, MLX_KEY_4))
		player->view_dir = M_PI * 1.5;
	mlx_key_hook(game->mlx, on_keypress, game);
}

void	hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	// mouse handling
	// minimap
	// collision
	// enemy
	keys(game, &game->minimap, &game->player);
	render_world(game);
	draw_minimap_i(game);
	draw_player_i(game);
	if (game->minimap.visible == 0)
		draw_minimap(game);
	// draw_player(game);
}
