/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/03 14:25:48 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game, t_map, t_player, t_texture, t_weapon
#include "../libraries/mlx/include/MLX42/MLX42.h" // mlx functions
#include <stdlib.h> // malloc
#include <stdio.h> // @note remove, printf
#include <unistd.h> // @note remove, sleep
#include <stdbool.h> // bool
#include <math.h> // M_PI

#define OBJ_COUNT 0 // @note remove
#define ENEMY_COUNT 1 // @note remove

int	test_parse(t_game *game)
{
	static char			*map[17] =
	{
		"1111111111111111",
		"1000100000000001",
		"1000100000000001",
		"1000100000000011",
		"1000000000000111",
		"1000100000001111",
		"1000100000011111",
		"1100100000111111",
		"1111111111111111"
	};
	static t_tex	textures[12] =
	{
		{"textures/north.png", NULL},
		{"textures/east.png", NULL},
		{"textures/south.png", NULL},
		{"textures/west.png", NULL},
		{"textures/knight.png", NULL},
		{"textures/lamp.png", NULL},
		{"textures/table.png", NULL},
		{"textures/gun.png", NULL},
		{"textures/zombie/zombie_run1.png", NULL},
		{"textures/zombie/zombie_run2.png", NULL},
		{"textures/zombie/zombie_run3.png", NULL},
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
		{.pos = {7.5, 4.5}, .tex = &textures[ZOMBIE_RUN1], .health = 100, .speed = 0.1},
	};
	static t_weapon	gun =
	{
		.tex = &textures[GUN],
		.damage = 10,
		.range = 10,
		.reload_time = 1,
	};

	game->map.arr = map;
	game->map.textures = textures;
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
	game->player.weapon = &gun;
	return (SUCCESS);
}

// @note fps engine correct like that?
// @todo fix resizing
// @note mlx_set_window_limit
// @todo implement doors
// @todo refactor hook functions for more readability (logic loop and render loop?)
// @todo go through code and refactor function parameters
// @todo fix the mlx compiling shit
// @todo for the doors: the whole block moves
// @todo split up into sensible modules (render module etc.)
// @todo rename object to sprite and sprite struct to sprite_helper or something?

void	put_weapon(mlx_t *mlx, t_weapon *weapon)
{
	mlx_image_t	*weapon_img;

	weapon_img = mlx_texture_to_image(mlx, weapon->tex->tex);
	if (mlx_image_to_window(mlx, weapon_img, WIDTH / 2 - weapon_img->width / 2, HEIGHT - weapon_img->height) == ERROR)
		errexit_mlx_errno();
}

int	main(int argc, char **argv)
{
	t_game		game;

	if (test_parse(&game))
		return (EXIT_FAILURE);
	if (initialize_mlx_data(&game) == ERROR)
		errexit_mlx_errno();
	if (mlx_loop_hook(game.mlx, &hook, &game) == false)
		errexit_mlx_errno();
	if (mlx_image_to_window(game.mlx, game.img_a, 0, 0) == ERROR)
		errexit_mlx_errno();
	put_weapon(game.mlx, game.player.weapon);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
