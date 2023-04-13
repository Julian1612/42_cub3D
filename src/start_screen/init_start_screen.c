/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_start_screen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 11:18:35 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/13 13:49:04 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_start_screen.h"
#include <stdlib.h> // exit

static int	init_background(t_game *game);
static int	init_png_textures(t_start_screen *start_screen);
static int	init_images(t_game *game);
static int	textures_to_images(t_game *game);

int	initialize_start_screen(t_game *game)
{
	int	tex_width;

	if (init_background(game) == ERROR)
		exit (EXIT_FAILURE);
	if (init_png_textures(&game->start_screen) == ERROR)
		exit (EXIT_FAILURE);
	if (init_images(game) == ERROR)
		exit (EXIT_FAILURE);
	tex_width = game->start_screen.img_start_button->width;
	if (textures_to_images(game) == ERROR)
		exit (EXIT_FAILURE);
	if (mlx_image_to_window(game->mlx, game->start_screen.img_soldier_down,
			(WIDTH / 2) - 140, 95) < 0)
		exit(EXIT_FAILURE);
	if (mlx_image_to_window(game->mlx, game->start_screen.img_soldier_up,
			(WIDTH / 2) - 140, 70) < 0)
		exit(EXIT_FAILURE);
	if (mlx_image_to_window(game->mlx, game->start_screen.img_start_button,
			(WIDTH / 2) - tex_width / 2, HEIGHT / 2) < 0)
		exit(EXIT_FAILURE);
	return (SUCCESS);
}

static int	init_background(t_game *game)
{
	game->start_screen.active = true;
	game->start_screen.background = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (game->start_screen.background == NULL)
		return (ERROR);
	if (mlx_image_to_window(game->mlx, game->start_screen.background,
			0, 0) == -1)
		return (ERROR);
	return (SUCCESS);
}

static int	init_png_textures(t_start_screen *start_screen)
{
	start_screen->start_button = mlx_load_png
		("./textures/start_button.png");
	start_screen->soldier_down = mlx_load_png
		("./textures/soldier_down.png");
	start_screen->soldier_up = mlx_load_png
		("./textures/soldier_up.png");
	if (start_screen->start_button == NULL
		|| start_screen->soldier_down == NULL
		|| start_screen->soldier_up == NULL)
		return (ERROR);
	return (SUCCESS);
}

static int	init_images(t_game *game)
{
	game->start_screen.img_start_button = mlx_texture_to_image(game->mlx,
			game->start_screen.start_button);
	game->start_screen.img_soldier_down = mlx_texture_to_image(game->mlx,
			game->start_screen.soldier_down);
	game->start_screen.img_soldier_up = mlx_texture_to_image(game->mlx,
			game->start_screen.soldier_up);
	if (game->start_screen.img_start_button == NULL
		|| game->start_screen.img_soldier_down == NULL
		|| game->start_screen.img_soldier_up == NULL)
		return (ERROR);
	return (SUCCESS);
}

static int	textures_to_images(t_game *game)
{
	game->start_screen.img_start_button = mlx_texture_to_image(game->mlx,
			game->start_screen.start_button);
	game->start_screen.img_soldier_down = mlx_texture_to_image(game->mlx,
			game->start_screen.soldier_down);
	game->start_screen.img_soldier_up = mlx_texture_to_image(game->mlx,
			game->start_screen.soldier_up);
	if (game->start_screen.img_start_button == NULL
		|| game->start_screen.img_soldier_down == NULL
		|| game->start_screen.img_soldier_up == NULL)
		return (ERROR);
	return (SUCCESS);
}
