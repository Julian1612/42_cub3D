/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/21 18:25:35 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3D.h" // t_game, t_map, t_player, t_texture, t_weapon
// #include "parser.h" // parser
// #include "../libraries/mlx/include/MLX42/MLX42.h" // mlx functions
// #include <stdlib.h> // malloc
// #include <stdio.h> // printf
// #include <stdbool.h> // bool

// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>
// // #define WIDTH 512
// // #define HEIGHT 512
// // #include <math.h> // M_PI

// // void	play_music(void)
// // {
// // 	system("afplay ./sound_track/preussengloria.mp3 &");
// // }
// static void error(void)
// {
// 	puts(mlx_strerror(mlx_errno));
// 	exit(EXIT_FAILURE);
// }


// int	main(int argc, char **argv)
// {
// 	t_game	game;

// 	// if (parser(&argc, argv, &game.map, &game.player))
// 	// 	return (EXIT_FAILURE);
// 	if (initialize_mlx_all(&game) == ERROR)
// 		errexit_mlx_errno();
// 	if (render_minimap(&game.minimap, game.mlx, &game.map) == ERROR)
// 		errexit_mlx_errno();
// 	if (!(test = mlx_new_image(game.mlx, 128, 128)))
// 	{
// 		mlx_close_window(game.mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (mlx_image_to_window(game.mlx, test, 10, 10) == -1)
// 	{
// 		mlx_close_window(game.mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (mlx_loop_hook(game.mlx, &hook, &game) == false)
// 		errexit_mlx_errno();
// 	if (mlx_image_to_window(game.mlx, game.img_a, 0, 0) == ERROR)
// 		errexit_mlx_errno();
// 	mlx_loop_hook(game.mlx, draw_sqr, game.mlx);
// 	mlx_loop(game.mlx);
// 	mlx_terminate(game.mlx);
	// return (EXIT_SUCCESS);
// }



#include "cub3D.h" // t_game, t_map, t_player, t_texture, t_weapon
#include "parser.h" // parser
#include "../libraries/mlx/include/MLX42/MLX42.h" // mlx functions
#include <stdlib.h> // malloc
#include <stdio.h> // printf
#include <stdbool.h> // bool
#include <math.h> // M_PI

// static mlx_image_t *test;

// void draw_sqr(void* param)
// {
// 	t_game	*game;

// 	game = (t_game *)param;
// 	int j;
// 	int i;

// 	i = 0;
// 	while (i < 10)
// 	{
// 		j = 0;
// 		while(j < 10)
// 		{
// 			uint32_t color = convert_to_hexcode(255, 255, 255, 255);
// 			mlx_put_pixel(game->minimap.test, i, j, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	play_music(void)
// {
// 	system("afplay ./sound_track/preussengloria.mp3 &");
// }

int	main(int argc, char **argv)
{
	t_game	game;

	if (parser(&argc, argv, &game.map, &game.player))
		return (EXIT_FAILURE);
	if (initialize_mlx_all(&game) == ERROR)
		errexit_mlx_errno();
	if (mlx_loop_hook(game.mlx, &hook, &game) == false)
		errexit_mlx_errno();
	if (mlx_image_to_window(game.mlx, game.img_a, 0, 0) == ERROR)
		errexit_mlx_errno();
	if (!(game.minimap.test = mlx_new_image(game.mlx, 128, 128)))
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game.mlx, game.minimap.test, 10, 10) == -1)
	{
		mlx_close_window(game.mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
