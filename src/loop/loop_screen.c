/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:02:58 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 06:24:39 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_loop.h" // loop funcs
#include "../types.h" // tex id
#include "../render.h" // render funcs
#include "../cub3D.h" // t_game

static bool	is_button_clicked(mlx_t *mlx, int width, int height, t_coor *pos)
{
	int	x;
	int	y;

	mlx_get_mouse_pos(mlx, &x, &y);
	if (x > pos->x
		&& x < pos->x + width
		&& y < pos->y + height
		&& y > pos->y - height
		&& mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT))
		return (true);
	return (false);
}

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
	t_coor	button_pos;

	set_next_frame(&start->frame, START_BG1, 8);
	start_render_textures(start, mlx, textures);
	button_pos.x = mlx->width / 2 - textures[START_BUTTON].tex->width / 2 + 20;
	button_pos.y = mlx->height - 350;
	if (is_button_clicked(mlx, textures[START_BUTTON].tex->width,
			textures[START_BUTTON].tex->height, &button_pos))
	{
		start->img->enabled = false;
		start->active = false;
		mlx_set_cursor_mode(mlx, MLX_MOUSE_DISABLED);
	}
}

#include <stdio.h>
void	win_loop(t_screen *win, mlx_t *mlx, t_tex *textures)
{
	t_coor	pos;

	pos.x = mlx->width / 2 - textures[WIN].tex->width / 2;
	pos.y = mlx->height / 2 - textures[WIN].tex->height / 2;
	render_color_image(win->img, 0x0000FF);
	render_texture_transparent(win->img, &textures[WIN], pos, 1);
}
