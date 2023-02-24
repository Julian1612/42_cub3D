/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/23 21:09:10 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parser.h"
#include "player_position.h"
#include <stdio.h>

#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* img;

void hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		img->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		img->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		img->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		img->instances[0].x += 5;
}

int	main(int argc, char **argv)
{
	t_map		map_data;
	t_player	player_pos;
	double		fovAngle = 60;
	// mlx_t*		mlx;

	map_data.map = NULL;
	if (parser(&argc, argv, &map_data))
		return (1);
	if (init_player_position(&map_data, &player_pos))
		return (1);
	printf("Player position: x = %f, y = %f, direction = %c\n",
		player_pos.x, player_pos.y, player_pos.direction);

	// if (!(mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true)))
	// 	return(EXIT_FAILURE);
	// img = mlx_new_image(mlx, 128, 128);
	// memset(img->pixels, 255, img->width * img->height * sizeof(int));
	// mlx_image_to_window(mlx, img, 0, 0);

	// mlx_loop_hook(mlx, &hook, mlx);
	// mlx_loop(mlx);

	// mlx_terminate(mlx);
	return (0);
}
