/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:06:51 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 23:02:21 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_loop.h" // loop funcs
#include "../render.h" // render funcs
#include "../cub3D.h" // t_game
#include <stdbool.h> // bool

static void	handle_esc(mlx_t *mlx)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		errexit_msg("Escape pressed. Exiting program.");
	}
}

static void	game_loop(t_game *game, double fps_mult)
{
	loop_logic(game, fps_mult);
	loop_graphic(game);
}

void	loop(void *param)
{
	t_game	*game;
	double	fps_mult;

	game = (t_game *)param;
	fps_mult = get_fps_mult(game->mlx->delta_time, FPS);
	handle_esc(game->mlx);
	game_loop(game, fps_mult);
}
