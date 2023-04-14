/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 19:04:23 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/15 00:40:53 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libraries/mlx42/include/MLX42/MLX42.h" // MLX_functions
#include "types.h" // t_frame
#include <stdbool.h> // bool

bool	is_cooldown(void)
{
	static int	cooldown = 0;

	if (cooldown == 0)
		cooldown = mlx_get_time();
	if (mlx_get_time() - cooldown > 0.2)
	{
		cooldown = mlx_get_time();
		return (false);
	}
	return (true);
}

bool	is_next_frame(double *time_of_last)
{
	if (mlx_get_time() - *time_of_last > 0.125)
	{
		*time_of_last = mlx_get_time();
		return (true);
	}
	return (false);
}

void	set_next_frame(t_frame *frame, enum e_tex_id start, int frame_count)
{
	if (is_next_frame(&frame->time_of_last) == true)
	{
		frame->curr++;
		if (frame->curr > start + frame_count - 1)
			frame->curr = start;
	}
}

double	get_fps_mult(double delta_time, int fps)
{
	return (delta_time * fps);
}
