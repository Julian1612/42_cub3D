/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:48:12 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/12 19:29:52 by lorbke           ###   ########.fr       */
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

void	draw_start_screen(mlx_t *mlx, t_start_screen *start_screen)
{
	int32_t	x;
	int32_t	y;

	mlx_get_mouse_pos(mlx, &x, &y);
	if (x > 289 && x < 517 && y < 512 && y > 420
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
