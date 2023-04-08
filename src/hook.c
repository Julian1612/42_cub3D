/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/04/03 14:29:05 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game
#include "../libraries/mlx/include/MLX42/MLX42.h" // MLX_functions
#include <stdio.h> // @note remove
#include <math.h> // cos, sin
#include <stdbool.h> // bool

#define MOV_SPEED 0.05
#define ENEMY_SPEED 0.005
#define ROT_SPEED 0.03

static void	move(t_vec *pos, t_map *map, double x_offset, double y_offset)
{
	if (!check_collision(pos->x + x_offset, pos->y, map))
		pos->x += x_offset;
	if (!check_collision(pos->x, pos->y + y_offset, map))
		pos->y += y_offset;
}

static void	rotate_player(t_player *player, bool left)
{
	double	temp;
	double	rot_speed;

	if (left)
		rot_speed = -ROT_SPEED;
	else
		rot_speed = ROT_SPEED;
	temp = player->dir.x;
	player->dir.x = temp * cos(rot_speed) - player->dir.y * sin(rot_speed);
	player->dir.y = temp * sin(rot_speed) + player->dir.y * cos(rot_speed);
	temp = player->cplane.x;
	player->cplane.x = temp * cos(rot_speed) - player->cplane.y * sin(rot_speed);
	player->cplane.y = temp * sin(rot_speed) + player->cplane.y * cos(rot_speed);
}

static void	keys(mlx_t *mlx, t_minimap *minimap, t_player *player, t_map *map)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		errexit_msg("Escape pressed. Exiting program.");
	}
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move(&player->pos, map, player->dir.x * MOV_SPEED, player->dir.y * MOV_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		move(&player->pos, map, -player->dir.x * MOV_SPEED, -player->dir.y * MOV_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move(&player->pos, map, rotate_x(player->dir.x, player->dir.y, M_PI_2) * MOV_SPEED, rotate_y(player->dir.x, player->dir.y, M_PI_2) * MOV_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move(&player->pos, map, -rotate_x(player->dir.x, player->dir.y, M_PI_2) * MOV_SPEED, -rotate_y(player->dir.x, player->dir.y, M_PI_2) * MOV_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		rotate_player(player, true);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		rotate_player(player, false);
}

int	get_frame(void)
{
	static int	delta_time = 0;

	if (delta_time == 0)
		delta_time = mlx_get_time();
	if (mlx_get_time() - delta_time > 1)
	{
		delta_time = mlx_get_time();
		return (0);
	}
	if (mlx_get_time() - delta_time > 0.7)
		return (3);
	if (mlx_get_time() - delta_time > 0.4)
		return (2);
	if (mlx_get_time() - delta_time > 0.1)
		return (1);
	return (0);
}

void	enemies(t_enemy *enemies, t_map *map, t_player *player)
{
	t_vec	dir;
	double	angle;
	int		i;

	i = 0;
	while (i < map->enemy_count)
	{
		angle = atan2(player->pos.y - enemies[i].pos.y, player->pos.x - enemies[i].pos.x);
		dir.x = cos(angle);
		dir.y = sin(angle);
		move(&enemies[i].pos, map, dir.x * ENEMY_SPEED, dir.y * ENEMY_SPEED);
		enemies[i].tex = &map->textures[ZOMBIE_RUN1 + get_frame()];
		printf("%d\n", get_frame());
		i++;
	}
}

void	hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	// mouse handling
	// minimap
	// collision
	// enemy
	if (skip_frame(game->mlx, FPS) == false)
	{
		keys(game->mlx, &game->minimap, &game->player, &game->map);
		enemies(game->map.enemies, &game->map, &game->player);
		render_all(game);
	}
	// @note all images have to be resized here
	mlx_resize_image(game->img_a, game->mlx->width, game->mlx->height);
}
