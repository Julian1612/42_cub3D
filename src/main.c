/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/12 01:24:01 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game, t_map, t_player, t_texture, t_weapon
#include "parser.h" // parser
#include "../libraries/mlx/include/MLX42/MLX42.h" // mlx functions
#include <stdlib.h> // malloc
#include <stdio.h> // @note remove, printf
#include <unistd.h> // @note remove, sleep
#include <stdbool.h> // bool
#include <math.h> // M_PI
#include <string.h> // @note remove, memcpy

void	play_music(void)
{
	system("afplay ./sound_track/preussengloria.mp3 &");
}

int	free_data(t_map *map_data)
{
	int	i;

	i = 0;
	while (i < map_data->obj_count)
	{
		free(map_data->objects[i].tex->path);
		i++;
	}
	i = 0;
	while (map_data->arr[i] != NULL)
	{
		free(map_data->arr[i]);
		i++;
	}
	free(map_data->arr);
	return (EXIT_SUCCESS);
}

// we need to free the struct form the parser at the end of main
int	main(int argc, char **argv)
{
	t_game		game;

	if (parser(&argc, argv, &game))
		return (EXIT_FAILURE);
	// if (initialize_mlx_data(&game) == ERROR)
	// 	errexit_mlx_errno();
	// if (mlx_loop_hook(game.mlx, &hook, &game) == false)
	// 	errexit_mlx_errno();
	// if (mlx_image_to_window(game.mlx, game.img_world, 0, 0) == ERROR)
	// 	errexit_mlx_errno();
	// if (mlx_image_to_window(game.mlx, game.img_hud, 0, 0) == ERROR)
	// 	errexit_mlx_errno();
	// if (initialize_minimap(&game) == ERROR)
	// 	errexit_mlx_errno();
	// if (initialize_start_screen(&game) == ERROR)
	// 	errexit_mlx_errno();
	// draw_background(&game.start_screen);
	// mlx_loop(game.mlx);
	// mlx_loop(game.mlx);
	// mlx_terminate(game.mlx);
	// int i = 0;
	// while (i < 4)
	// {
	// 	printf("%s\n", game.map.textures[i]->path);
	// 	i++;
	// }
	// i = 0;
	// printf("--------------------------------------------\n");
	// printf("--------------------------------------------\n");
	// printf("game.map.enemy_count = %d\n", game.map.enemy_count);
	// printf("--------------------------------------------\n");
	// printf("--------------------------------------------\n");
	// while (i < game.map.enemy_count)
	// {
	// 	printf("--------------------------------------------\n");
	// 	printf("game.map.enemies[i].alive = %d\n", game.map.enemies[i].alive);
	// 	printf("game.map.enemies[i].pos.x = %f\n", game.map.enemies[i].pos.x);
	// 	printf("game.map.enemies[i].pos.y = %f\n", game.map.enemies[i].pos.y);
	// 	printf("game.map.enemies[i].health = %d\n", game.map.enemies[i].health);
	// 	printf("game.map.enemies[i].last_frame_time = %f\n", game.map.enemies[i].last_frame_time);
	// 	printf("game.map.enemies[i].curr_frame = %d\n", game.map.enemies[i].curr_frame);
	// 	printf("game.map.enemies[i].speed = %f\n", game.map.enemies[i].speed);
	// 	printf("game.map.enemies[i].damage = %d\n", game.map.enemies[i].damage);
	// 	i++;
	// }
	// i = 0;
	// printf("--------------------------------------------\n");
	// printf("--------------------------------------------\n");
	// printf("game.map.door_count = %d\n", game.map.door_count);
	// printf("--------------------------------------------\n");
	// printf("--------------------------------------------\n");
	// while (i < game.map.door_count)
	// {
	// 	printf("--------------------------------------------\n");
	// 	printf("game->map.doors[count_doors].x = %d\n", game.map.doors[i].x);
	// 	printf("game->map.doors[count_doors].y = %d\n", game.map.doors[i].y);
	// 	printf("game->map.doors[count_doors].open = %d\n", game.map.doors[i].open);
	// 	printf("game->map.doors[count_doors].last_action = %f\n", game.map.doors[i].last_action);
	// 	i++;
	// }
	free_data(&game.map);
	return (EXIT_SUCCESS);
}
