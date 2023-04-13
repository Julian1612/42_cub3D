/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:06:51 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/13 13:43:19 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_loop.h" // loop funcs
#include "../cub3D.h" // t_game

static void	handle_esc(mlx_t *mlx)
{
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		errexit_msg("Escape pressed. Exiting program.");
	}
}

void	loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	handle_esc(game->mlx);
	if (game->start_screen.active == true)
		startscreen_wait_for_click(game->mlx, &game->start_screen);
	else
	{
		loop_logic(game);
		loop_graphic(game);
	}
}
