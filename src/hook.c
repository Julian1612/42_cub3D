/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:51:13 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/07 14:56:37 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game
#include "../libraries/mlx/include/MLX42/MLX42.h" // MLX_functions
#include "minimap.h" // t_minimap
#include <stdio.h> // @note remove
#include <math.h> // cos, sin
#include <stdbool.h> // bool

#define MOV_SPEED 10 // @note the higher, the slower
#define ROT_SPEED 0.5 // @note the higher, the slower
#define PLAYER_SIZE 0.2 // @todo size of player, switch to actual player size

// @todo drifting collision
// @note collision problem: if speed is too high, player can move through walls
// @note function usable for enemies?
static bool	check_collision(double x, double y, char **map)
{
	if (map[(int)(y + PLAYER_SIZE)][(int)(x)] == WALL)
		return (true);
	if (map[(int)(y - PLAYER_SIZE)][(int)(x)] == WALL)
		return (true);
	if (map[(int)(y)][(int)(x + PLAYER_SIZE)] == WALL)
		return (true);
	if (map[(int)(y)][(int)(x - PLAYER_SIZE)] == WALL)
		return (true);
	return (false);
}

static void	move_player(t_player *player, char **map, double x_offset, double y_offset)
{
	if (!check_collision(player->x + x_offset, player->y, map))
		player->x += x_offset;
	if (!check_collision(player->x, player->y + y_offset, map))
		player->y += y_offset;
}

void	change_maps(mlx_key_data_t keydata, void *param)
{
	t_minimap	*minimap;

	minimap = (t_minimap *)param;
	if (keydata.key == MLX_KEY_F && keydata.action == 0
		&& minimap->visible == 0)
	{
		minimap->smm_walls->instances[0].enabled = false;
		minimap->lmm_walls->instances[0].enabled = true;
		minimap->visible = 1;
	}
	else if (keydata.key == MLX_KEY_F && keydata.action == 0
		&& minimap->visible == 1)
	{
		minimap->smm_walls->instances[0].enabled = true;
		minimap->lmm_walls->instances[0].enabled = false;
		minimap->visible = 0;
	}
}

void	mouse_movements(mlx_t *mlx, t_player *player)
{
	int32_t			x;
	int32_t			y;

	mlx_get_mouse_pos(mlx, &x, &y);
	if (x < 400 && x > 2)
		player->view_dir += M_PI / 90 / 1;
	else if (x > 400 && x < 800)
		player->view_dir -= M_PI / 90 / 1;
	mlx_set_mouse_pos(mlx, 400, 400);
}

static void	keys(mlx_t *mlx, t_minimap *minimap, t_player *player, char **map)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		errexit_msg("Escape pressed. Exiting program.");
	}
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move_player(player, map, sin(player->view_dir) / MOV_SPEED, cos(player->view_dir) / MOV_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		move_player(player, map, -sin(player->view_dir) / MOV_SPEED, -cos(player->view_dir) / MOV_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_player(player, map, sin(player->view_dir - M_PI_2) / MOV_SPEED, cos(player->view_dir - M_PI_2) / MOV_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_player(player, map, -sin(player->view_dir - M_PI_2) / MOV_SPEED, -cos(player->view_dir - M_PI_2) / MOV_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		player->view_dir += M_PI / 90 / ROT_SPEED; // @note radian rotated by 5 degrees (1pi = 180 degrees)
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		player->view_dir -= M_PI / 90 / ROT_SPEED;
	if (mlx_is_key_down(mlx, MLX_KEY_1))
		player->view_dir = 0;
	if (mlx_is_key_down(mlx, MLX_KEY_2))
		player->view_dir = M_PI / 2;
	if (mlx_is_key_down(mlx, MLX_KEY_3))
		player->view_dir = M_PI;
	if (mlx_is_key_down(mlx, MLX_KEY_4))
		player->view_dir = M_PI * 1.5;
	mlx_key_hook(mlx, change_maps, minimap);
	mouse_movements(mlx, player);
}

static bool	skip_frame(mlx_t *mlx, int fps)
{
	if (mlx->delta_time * fps > 1.1)
		return (true);
	return (false);
}

void	hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	keys(game->mlx, &game->minimap, &game->player, game->map.map);
	if (game->minimap.visible == 0)
		render_minimap(game);
	if (skip_frame(game->mlx, FPS) == false)
		render_world(game);
	// @note all images have to be resized here
	mlx_resize_image(game->img_a, game->mlx->width, game->mlx->height);
}
