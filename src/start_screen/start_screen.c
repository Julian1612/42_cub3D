/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 18:48:12 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/10 11:32:35 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_start_screen.h"

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
		mlx_delete_image(mlx, start_screen->img_start_button);
		mlx_delete_image(mlx, start_screen->img_soldier_down);
		mlx_delete_image(mlx, start_screen->img_soldier_up);
		start_screen->active = false;
		mlx_set_cursor_mode(mlx, MLX_MOUSE_DISABLED);
	}
}
