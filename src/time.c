/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:04:23 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 23:06:20 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/mlx/include/MLX42/MLX42.h" // MLX_functions
#include "types.h" // t_frame
#include <stdbool.h> // bool

bool	is_next_frame(double *time_of_last)
{
	if (mlx_get_time() - *time_of_last > 0.125)
	{
		*time_of_last = mlx_get_time();
		return (true);
	}
	return (false);
}

double	get_fps_mult(double delta_time, int fps)
{
	return (delta_time * fps);
}
