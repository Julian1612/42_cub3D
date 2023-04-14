/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:02:58 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 04:33:25 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_loop.h" // loop funcs
#include "../types.h" // tex id
#include "../render.h" // render funcs
#include "../cub3D.h" // t_game

static void	start_render_textures(t_screen *start, mlx_t *mlx, t_tex *textures)
{
	t_coor	pos;

	pos.x = mlx->width / 2 - textures[START_BG1].tex->width / 2;
	pos.y = 0;
	render_texture(start->img, &textures[start->frame.curr], pos, 1);
	pos.x = mlx->width / 2 - textures[START_CUB].tex->width / 2 + 20;
	pos.y = 50;
	render_texture_transparent(start->img, &textures[START_CUB], pos, 1);
	pos.x = mlx->width / 2 - textures[START_BUTTON].tex->width / 2 + 20;
	pos.y = mlx->height - 350;
	render_texture_transparent(start->img, &textures[START_BUTTON], pos, 1);
}

void	start_loop(t_screen *start, mlx_t *mlx, t_tex *textures)
{
	int32_t	x;
	int32_t	y;
	int		button_width;
	int		button_height;
	t_coor	pos;

	pos.x = mlx->width / 2 - start->img->width / 2;
	pos.y = 0;
	set_next_frame(&start->frame, START_BG1, 8);
	start_render_textures(start, mlx, textures);
	button_width = (int)&textures[START_BUTTON].tex->width;
	button_height = (int)&textures[START_BUTTON].tex->height;
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
