/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/21 16:07:27 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game, t_map, t_player, t_texture, t_weapon
#include "parser.h" // parser
#include "../libraries/mlx/include/MLX42/MLX42.h" // mlx functions
#include <stdlib.h> // malloc
#include <stdio.h> // printf
#include <stdbool.h> // bool

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// #define WIDTH 512
// #define HEIGHT 512
// #include <math.h> // M_PI

// void	play_music(void)
// {
// 	system("afplay ./sound_track/preussengloria.mp3 &");
// }
static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static mlx_image_t *test;

void draw_sqr(void* param)
{
	int j;
	int i;

	i = 0;
	while (i < 10)
	{
		j = 0;
		while(j < 10)
		{
			uint32_t color = convert_to_hexcode(255, 255, 255, 255);
			mlx_put_pixel(test, i, j, color);
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_game	game;

	// if (parser(&argc, argv, &game.map, &game.player))
	// 	return (EXIT_FAILURE);
	if (initialize_mlx_all(&game) == ERROR)
		errexit_mlx_errno();
	if (render_minimap(&game.minimap, game.mlx, &game.map) == ERROR)
		errexit_mlx_errno();
	if (!(test = mlx_new_image(game.mlx, 128, 128)))
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game.mlx, test, 10, 10) == -1)
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_loop_hook(game.mlx, &hook, &game) == false)
		errexit_mlx_errno();
	if (mlx_image_to_window(game.mlx, game.img_a, 0, 0) == ERROR)
		errexit_mlx_errno();
	mlx_loop_hook(game.mlx, draw_sqr, game.mlx);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}



// static void error(void)
// {
// 	puts(mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }

// int32_t	main(void)
// {
// 	// Start mlx
// 	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Test", true);
// 	if (!mlx)
//         error();

// 	// Try to load the file
// 	mlx_texture_t* texture = mlx_load_png("./textures/example.png");
// 	if (!texture)
//         error();

// 	// Convert texture to a displayable image
// 	mlx_image_t* img = mlx_texture_to_image(mlx, texture);
// 	if (!img)
//         error();

// 	// Display the image
// 	if (mlx_image_to_window(mlx, img, 0, 0) < 0)
//         error();

// 	mlx_loop(mlx);

// 	// Optional, terminate will clean up any leftovers, this is just to demonstrate.
// 	mlx_delete_image(mlx, img);
// 	mlx_delete_texture(texture);
// 	mlx_terminate(mlx);
// 	return (EXIT_SUCCESS);
// }
