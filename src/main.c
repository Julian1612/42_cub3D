/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/11 20:12:11 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game, t_map, t_player, t_texture, t_weapon
#include "../libraries/mlx/include/MLX42/MLX42.h" // mlx functions
#include <stdlib.h> // malloc
#include <stdio.h> // @note remove, printf
#include <unistd.h> // @note remove, sleep
#include <stdbool.h> // bool
#include <math.h> // M_PI
#include <string.h> // @note remove, memcpy

#define OBJ_COUNT 0 // @note remove
#define ENEMY_COUNT 9 // @note remove
#define DOOR_COUNT 1 // @note remove

char			map[17][35] =
{
	"1111111111111111111111111111111",
	"1001000000000000000000000000001",
	"1001000000000000000000000000001",
	"1001000000000000000000000000011",
	"100D000000000000000000000000111",
	"1001000000000000000000000001111",
	"1001000000000000000000000011111",
	"1101000000000000000000000111111",
	"1111111111111111111111111111111",
};

char	**cpy_map(char map[17][35])
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = (char **)malloc(sizeof(char *) * 17);
	while (i < 17)
	{
		new_map[i] = (char *)malloc(sizeof(char) * 35);
		memcpy(new_map[i], map[i], 35);
		i++;
	}
	return (new_map);
}

int	test_parse(t_game *game)
{
	static t_tex	textures[ZOMBIE_DEAD8 + 1] =
	{
		{"textures/north.png", NULL},
		{"textures/east.png", NULL},
		{"textures/south.png", NULL},
		{"textures/west.png", NULL},
		{"textures/knight.png", NULL},
		{"textures/lamp.png", NULL},
		{"textures/table.png", NULL},
		{"textures/door/door_front.png", NULL},
		{"textures/door/door_side.png", NULL},
		{"textures/gun/gun1.png", NULL},
		{"textures/gun/gun2.png", NULL},
		{"textures/gun/gun3.png", NULL},
		{"textures/gun/gun4.png", NULL},
		{"textures/gun/gun5.png", NULL},
		{"textures/gun/gun6.png", NULL},
		{"textures/zombie/zombie_run1.png", NULL},
		{"textures/zombie/zombie_run2.png", NULL},
		{"textures/zombie/zombie_run3.png", NULL},
		{"textures/zombie/zombie_left1.png", NULL},
		{"textures/zombie/zombie_left2.png", NULL},
		{"textures/zombie/zombie_left3.png", NULL},
		{"textures/zombie/zombie_right1.png", NULL},
		{"textures/zombie/zombie_right2.png", NULL},
		{"textures/zombie/zombie_right3.png", NULL},
		{"textures/zombie/zombie_dead1.png", NULL},
		{"textures/zombie/zombie_dead2.png", NULL},
		{"textures/zombie/zombie_dead3.png", NULL},
		{"textures/zombie/zombie_dead4.png", NULL},
		{"textures/zombie/zombie_dead5.png", NULL},
		{"textures/zombie/zombie_dead6.png", NULL},
		{"textures/zombie/zombie_dead7.png", NULL},
		{"textures/zombie/zombie_dead8.png", NULL},
	};
	static t_door	doors[DOOR_COUNT] =
	{
		{.x = 3, .y = 4, .open = false, .last_action = 0},
	};
	static t_object	objects[OBJ_COUNT] =
	{
		// {.pos = {6.5, 4.5}, .type = DECOR_NON_PERM, .tex = &textures[KNIGHT]},
		// {.pos = {9.5, 4.5}, .type = DECOR_NON_PERM, .tex = &textures[KNIGHT]},
		// {.pos = {12.5, 4.5}, .type = DECOR_PERM, .tex = &textures[LAMP]},
		// {.pos = {14.5, 1.5}, .type = DECOR_PERM, .tex = &textures[LAMP]},
		// {.pos = {5.5, 7.5}, .type = DECOR_NON_PERM, .tex = &textures[TABLE]},
	};
	static t_enemy	enemies[ENEMY_COUNT] =
	{
		{.alive = true, .pos = {7.5, 4.5}, .last_frame_time = 0, .curr_frame = ZOMBIE_RUN1, .health = 100, .speed = 0.1, .damage = 10},
		{.alive = true, .pos = {11.5, 4.5}, .last_frame_time = 0, .curr_frame = ZOMBIE_RUN1, .health = 100, .speed = 0.1, .damage = 10},
		{.alive = true, .pos = {10.5, 4.5}, .last_frame_time = 0, .curr_frame = ZOMBIE_RUN1, .health = 100, .speed = 0.1, .damage = 10},
		{.alive = true, .pos = {8.5, 4.5}, .last_frame_time = 0, .curr_frame = ZOMBIE_RUN1, .health = 100, .speed = 0.1, .damage = 10},
		{.alive = true, .pos = {10.5, 6.5}, .last_frame_time = 0, .curr_frame = ZOMBIE_RUN1, .health = 100, .speed = 0.1, .damage = 10},
		{.alive = true, .pos = {9.5, 7.5}, .last_frame_time = 0, .curr_frame = ZOMBIE_RUN1, .health = 100, .speed = 0.1, .damage = 20},
		{.alive = true, .pos = {9.5, 6.5}, .last_frame_time = 0, .curr_frame = ZOMBIE_RUN1, .health = 100, .speed = 0.1, .damage = 20},
		{.alive = true, .pos = {5.5, 7.5}, .last_frame_time = 0, .curr_frame = ZOMBIE_RUN1, .health = 100, .speed = 0.1, .damage = 20},
		{.alive = true, .pos = {8.5, 7.5}, .last_frame_time = 0, .curr_frame = ZOMBIE_RUN1, .health = 100, .speed = 0.1, .damage = 20},
	};
	static t_weapon	gun =
	{
		.damage = 10,
		.range = 10,
		.reload_time = 1,
		.last_frame_time = 0,
		.curr_frame = GUN1,
	};
	
	game->map.arr = cpy_map(map);
	game->map.textures = textures;
	game->map.doors = doors;
	game->map.door_count = DOOR_COUNT;
	game->map.objects = objects;
	game->map.obj_count = OBJ_COUNT;
	game->map.enemies = enemies;
	game->map.enemy_count = ENEMY_COUNT;
	game->map.ceiling_color = convert_to_hexcode(0, 0, 0, 0);
	game->map.floor_color = convert_to_hexcode(0, 0, 0, 150);
	game->player.pos.x = 2;
	game->player.pos.y = 2;
	game->player.cplane.x = 0;
	// @note fov = half of aspect ratio of screen (why half?)
	game->player.cplane.y = (double)WIDTH / HEIGHT / 2;
	game->player.dir.x = -1;
	game->player.dir.y = 0;
	game->player.health = 100;
	game->player.weapon = &gun;
	return (SUCCESS);
}

// @todo resizing segfault when shooting because of weapon texture
// @todo refactor hook functions for more readability (logic loop and render loop?)
// @todo go through code and refactor function parameters
// @todo fix the mlx compiling shit
// @todo split up into sensible modules (render module etc.)
// @todo rename object to sprite and sprite struct to sprite_helper or something?
// @todo make struct out of frame variables
// @todo scale gun textures to 64x64
// @todo remove cooldown function
// @todo make re not working correctly
// @todo add cooldown for enemy
// @todo add coins
// @todo add health bar
// @todo add sounds
// @todo make weapon pickupable

int	main(int argc, char **argv)
{
	t_game		game;

	if (test_parse(&game))
		return (EXIT_FAILURE);
	if (initialize_mlx_data(&game) == ERROR)
		errexit_mlx_errno();
	if (mlx_loop_hook(game.mlx, &hook, &game) == false)
		errexit_mlx_errno();
	if (mlx_image_to_window(game.mlx, game.img_world, 0, 0) == ERROR)
		errexit_mlx_errno();
	if (mlx_image_to_window(game.mlx, game.img_hud, 0, 0) == ERROR)
		errexit_mlx_errno();
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
