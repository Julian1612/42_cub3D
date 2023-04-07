/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:46:50 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/07 18:52:01 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // m_t, t_player
#include "../libraries/mlx/include/MLX42/MLX42.h" // MLX_functions
#include <math.h> // M_PI

void	mouse_movements(mlx_t *mlx, t_player *player)
{
	int32_t			x;
	int32_t			y;

	mlx_get_mouse_pos(mlx, &x, &y);
	if (x < 400 && x > 2)
		player->view_dir += M_PI / 90 / 1;
	else if (x > 400 && x < 800)
		player->view_dir -= M_PI / 90 / 1;
	mlx_set_mouse_pos(mlx, 400, 400);
}
