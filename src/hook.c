/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/04/11 14:40:07 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game
#include "../libraries/mlx/include/MLX42/MLX42.h" // MLX_functions
#include <stdio.h> // @note remove
#include <math.h> // cos, sin
#include <stdbool.h> // bool

#define MOV_SPEED 0.1
#define ROT_SPEED 0.05
#define DOOR_COOLDOWN 0.2
#define PLAYER_REACH 2.0

static void	switch_door_state(t_game *game, t_player *player)
{
	t_rayhit	hit;
	char		target;
	int			i;

	i = 0;
	while (i < game->map.door_count)
	{
		if (mlx_get_time() - game->map.doors[i].last_action > DOOR_COOLDOWN)
		{
			if (game->map.doors[i].open == false)
				target = DOOR_CLOSED;
			else
				target = DOOR_OPEN;
			cast_ray(&hit, game, player->dir, target);
			if (hit.hit == target && hit.dist <= PLAYER_REACH && hit.dist > 0.5)
			{
				if (game->map.doors[i].open == false)
					game->map.arr[game->map.doors[i].y][game->map.doors[i].x] = DOOR_OPEN;
				else
					game->map.arr[game->map.doors[i].y][game->map.doors[i].x] = DOOR_CLOSED;
				game->map.doors[i].open = switch_bool(game->map.doors[i].open);
			}
			game->map.doors[i].last_action = mlx_get_time();
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
	cast_ray(&hit, game, player->dir, ENEMY);
	if (hit.enemy_index != -1)
	{
		if (map->enemies[hit.enemy_index].health > 0)
			map->enemies[hit.enemy_index].health -= player->weapon->damage;
	}
}

static void	move_player(t_vec *pos, t_map *map, double x_offset, double y_offset)
{
	if (!check_collision(pos->x + x_offset, pos->y, map, -1))
		pos->x += x_offset;
	if (!check_collision(pos->x, pos->y + y_offset, map, -1))
		pos->y += y_offset;
}

static void	rotate_player(t_player *player, double rot_speed, bool left)
{
	double	temp;

	if (left)
		rot_speed = -rot_speed;
	temp = player->dir.x;
	player->dir.x = temp * cos(rot_speed) - player->dir.y * sin(rot_speed);
	player->dir.y = temp * sin(rot_speed) + player->dir.y * cos(rot_speed);
	temp = player->cplane.x;
	player->cplane.x = temp * cos(rot_speed) - player->cplane.y * sin(rot_speed);
	player->cplane.y = temp * sin(rot_speed) + player->cplane.y * cos(rot_speed);
}

static void	keys(mlx_t *mlx, t_minimap *minimap, t_player *player, t_map *map, t_game *game, double fps_mult)
{
	double	mov_speed;
	double	rot_speed;

	mov_speed = MOV_SPEED * fps_mult;
	rot_speed = ROT_SPEED * fps_mult;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		errexit_msg("Escape pressed. Exiting program.");
	}
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_W))
		move_player(&player->pos, map, player->dir.x * mov_speed, player->dir.y * mov_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_S))
		move_player(&player->pos, map, -player->dir.x * mov_speed, -player->dir.y * mov_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_D))
		move_player(&player->pos, map, rotate_x(player->dir.x, player->dir.y, M_PI_2) * mov_speed, rotate_y(player->dir.x, player->dir.y, M_PI_2) * mov_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_A))
		move_player(&player->pos, map, -rotate_x(player->dir.x, player->dir.y, M_PI_2) * mov_speed, -rotate_y(player->dir.x, player->dir.y, M_PI_2) * mov_speed);
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		rotate_player(player, rot_speed, true);
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		rotate_player(player, rot_speed, false);
	if (mlx_is_key_down(mlx, MLX_KEY_SPACE))
		shoot(player, map, game);
	else
		player->weapon->curr_frame = GUN1;
	if (mlx_is_key_down(mlx, MLX_KEY_E))
		switch_door_state(game, player);
}

void	resize_camera(t_player *player, int width, int height)
{
	double	temp;

	temp = (double)width / height / 2;
	player->cplane.x = 0;
	player->cplane.y = temp;
	player->dir.x = -1;
	player->dir.y = 0;
}

void	resize(t_game *game)
{
	static int	last_width = WIDTH;
	static int	last_height = HEIGHT;

	if (last_width == game->mlx->width && last_height == game->mlx->height)
		return ;
	if ((double)game->mlx->width / game->mlx->height < 1
		|| (double)game->mlx->width / game->mlx->height > 2)
	{
		errexit_msg("Window height to width ratio cannot be smaller than 1 or greater than 2.");
		return ;
	}
	last_width = game->mlx->width;
	last_height = game->mlx->height;
	mlx_resize_image(game->img_world, game->mlx->width, game->mlx->height);
	mlx_resize_image(game->img_hud, game->mlx->width, game->mlx->height);
	resize_camera(&game->player, game->mlx->width, game->mlx->height);
}

void	hook(void *param)
{
	t_game	*game;
	double	fps_mult;

	game = (t_game *)param;
	fps_mult = get_fps_mult(game->mlx->delta_time, FPS);
	keys(game->mlx, &game->minimap, &game->player, &game->map, game, fps_mult);
	enemies(game->map.enemies, &game->map, &game->player, fps_mult);
	render_all(game);
	resize(game);
	if (game->player.health <= 0)
		errexit_msg("You died. Exiting program.");
}
