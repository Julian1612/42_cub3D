/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/04/12 16:42:25 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_loop.h" // loop funcs
#include "../cub3D.h" // t_game

void	loop(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	loop_logic(game);
	loop_graphic(game);
}
