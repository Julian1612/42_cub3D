/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:48:12 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/09 22:13:02 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game, t_map, t_player, t_texture, t_weapon
// #include "../libraries/mlx/include/MLX42/MLX42.h" // mlx functions

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

int	init_png_textures(t_start_screen *start_screen)
{
	start_screen->start_button = mlx_load_png
		("./textures/start_button.png");
	start_screen->soldier_down = mlx_load_png
		("./textures/soldier_down.png");
	if (start_screen->start_button == NULL
		|| start_screen->soldier_down == NULL)
		return (ERROR);
	return (SUCCESS);
}

int	initialize_start_screen(t_game *game)
{
	if (init_background(game) == ERROR)
		exit (EXIT_FAILURE);
	if (init_png_textures(game) == ERROR)
		exit (EXIT_FAILURE);
	game->start_screen.img_start_button = mlx_texture_to_image(game->mlx,
			game->start_screen.start_button);
	game->start_screen.img_soldier_down = mlx_texture_to_image(game->mlx,
			game->start_screen.soldier_down);
	if (mlx_texture_to_image(game->mlx,
			game->start_screen.soldier_down) == NULL)
		exit(EXIT_FAILURE);
	if (mlx_texture_to_image(game->mlx,
			game->start_screen.start_button) == NULL)
		exit(EXIT_FAILURE);
	if (mlx_image_to_window(game->mlx, game->start_screen.img_start_button,
			(WIDTH / 2) - 140, HEIGHT / 2) < 0)
		exit(EXIT_FAILURE);
	if (mlx_image_to_window(game->mlx, game->start_screen.img_soldier_down,
			(WIDTH / 2) - 140, 70) < 0)
		exit(EXIT_FAILURE);
	return (SUCCESS);
}

void	draw_background(t_start_screen *start_screen)
{
	int			k;
	int			l;
	uint32_t	color;

	color = convert_to_hexcode(0, 0, 0, 255);
	k = 0;
	while (k < HEIGHT)
	{
		l = 0;
		while (l < WIDTH)
		{
			mlx_put_pixel(start_screen->background, l, k, color);
			l++;
		}
		k++;
	}
}

void	draw_start_screen(mlx_t *mlx, t_start_screen *start_screen)
{
	int32_t	x;
	int32_t	y;

	mlx_get_mouse_pos(mlx, &x, &y);
	if (x > 289 && x < 517 && y < 512 && y > 420
		&& mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_delete_image(mlx, start_screen->background);
		mlx_delete_image(mlx, start_screen->img_soldier_down);
		mlx_delete_image(mlx, start_screen->img_start_button);
		start_screen->active = false;
		mlx_set_cursor_mode(mlx, MLX_MOUSE_DISABLED);
	}
}
