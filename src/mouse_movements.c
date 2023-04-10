/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:46:50 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/10 18:20:44 by lorbke           ###   ########.fr       */
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
		rotate_player(player, false);
	else if (x > 400 && x < 800)
		rotate_player(player, true);
	mlx_set_mouse_pos(mlx, 400, 400);
}
