/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:02:58 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 02:03:20 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_loop.h" // loop funcs
#include "../render.h" // render funcs
#include "../cub3D.h" // t_game

void	start_loop(t_screen *start, mlx_t *mlx)
{
	int32_t	x;
	int32_t	y;
	int		button_width;
	int		button_height;
	t_coor	pos;

	pos.x = mlx->width / 2 - start->img->width / 2;
	pos.y = mlx->height / 2 - start->img->height / 2 + 50;
	render_texture(start->img, start->tex, pos, 1);
	button_width = start->img->width;
	button_height = start->img->height;
	mlx_get_mouse_pos(mlx, &x, &y);
	if (x > mlx->width / 2 - button_width / 2
		&& x < mlx->width / 2 + button_width / 2
		&& y < mlx->height / 2 + button_height / 2 + 50
		&& y > mlx->height / 2 - button_height / 2 + 50
		&& mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		start->img->enabled = false;
		start->active = false;
		mlx_set_cursor_mode(mlx, MLX_MOUSE_DISABLED);
	}
}
