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
#define ROT_SPEED 0.03

static void	switch_door_state(t_map *map, double x, double y)
{
	int	i;

	i = 0;
	while (i < map->door_count)
	{
		printf("dist x: %f, dist y: %f\n", fabs(map->doors[i].x - x), fabs(map->doors[i].y - y));
		if (fabs(map->doors[i].x - x) >= 1 && fabs(map->doors[i].y - y) >= 1
			&& fabs(map->doors[i].x - x) <= 2 && fabs(map->doors[i].y - y) <= 2
			&& mlx_get_time() - map->doors[i].last_action > 0.5)
		{
			map->doors[i].last_action = mlx_get_time();
			if (map->doors[i].open == true)
			{
				map->doors[i].open = false;
				map->arr[map->doors[i].y][map->doors[i].x] = DOOR;
			}
			else
			{
				map->doors[i].open = true;
				map->arr[map->doors[i].y][map->doors[i].x] = FLOOR;
			}
		}
		i++;
	}
}

static void	shoot(t_player *player, t_map *map, t_game *game)
{

	t_rayhit	hit;

	if (is_next_frame(&player->weapon->last_frame_time) == true)
	{
		player->weapon->curr_frame++;
		if (player->weapon->curr_frame > GUN6)
			player->weapon->curr_frame = GUN3;
	}
	cast_ray(&hit, game, player->dir, MODE_ENEMY);
	if (hit.enemy_index != -1)
	{
		if (map->enemies[hit.enemy_index].health > 0)
			map->enemies[hit.enemy_index].health -= 1;
	}
}

static void	move_player(t_vec *pos, t_map *map, double x_offset, double y_offset)
{
	if (!check_collision(pos->x + x_offset, pos->y, map, -1))
		pos->x += x_offset;
	if (!check_collision(pos->x, pos->y + y_offset, map, -1))
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

static void	keys(mlx_t *mlx, t_minimap *minimap, t_player *player, t_map *map, t_game *game)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		errexit_msg("Escape pressed. Exiting program.");
	}
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move_player(&player->pos, map, player->dir.x * MOV_SPEED, player->dir.y * MOV_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		move_player(&player->pos, map, -player->dir.x * MOV_SPEED, -player->dir.y * MOV_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_player(&player->pos, map, rotate_x(player->dir.x, player->dir.y, M_PI_2) * MOV_SPEED, rotate_y(player->dir.x, player->dir.y, M_PI_2) * MOV_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_player(&player->pos, map, -rotate_x(player->dir.x, player->dir.y, M_PI_2) * MOV_SPEED, -rotate_y(player->dir.x, player->dir.y, M_PI_2) * MOV_SPEED);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		rotate_player(player, true);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		rotate_player(player, false);
	if (mlx_is_key_down(mlx, MLX_KEY_SPACE))
		shoot(player, map, game);
	else
		player->weapon->curr_frame = GUN1;
	if (mlx_is_key_down(mlx, MLX_KEY_E))
		switch_door_state(map, player->pos.x, player->pos.y);
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
		keys(game->mlx, &game->minimap, &game->player, &game->map, game);
		enemies(game->map.enemies, &game->map, &game->player);
		render_all(game);
	}
	// @note all images have to be resized here
	mlx_resize_image(game->img_world, game->mlx->width, game->mlx->height);
	mlx_resize_image(game->img_hud, game->mlx->width, game->mlx->height);
	if (game->player.health <= 0)
		errexit_msg("You died. Exiting program.");
}
