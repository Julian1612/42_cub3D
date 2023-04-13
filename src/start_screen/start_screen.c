/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:48:12 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/13 15:34:15 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_start_screen.h"

void	draw_background(t_start_screen *start_screen)
{
	int			k;
	int			l;

	k = 0;
	while (k < HEIGHT)
	{
		l = 0;
		while (l < WIDTH)
		{
			mlx_put_pixel(start_screen->background, l, k, 0xFF000000);
			l++;
		}
		k++;
	}
}

void	startscreen_wait_for_click(mlx_t *mlx, t_start_screen *start_screen)
{
	int32_t	x;
	int32_t	y;
	int		button_width;
	int		button_height;

	button_width = start_screen->img_start_button->width;
	button_height = start_screen->img_start_button->height;
	mlx_get_mouse_pos(mlx, &x, &y);
	if (x > mlx->width / 2 - button_width / 2
		&& x < mlx->width / 2 + button_width / 2
		&& y < mlx->height / 2 + button_height / 2 + 50
		&& y > mlx->height / 2 - button_height / 2 + 50
		&& mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		mlx_delete_image(mlx, start_screen->background);
		mlx_delete_image(mlx, start_screen->img_start_button);
		mlx_delete_image(mlx, start_screen->img_soldier_down);
		mlx_delete_image(mlx, start_screen->img_soldier_up);
		start_screen->active = false;
		mlx_set_cursor_mode(mlx, MLX_MOUSE_DISABLED);
	}
}
