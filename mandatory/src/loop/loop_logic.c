/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:20:05 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 23:01:33 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_loop.h" // loop door funcs
#include "../cub3D.h"
#include "../raycast.h" // raycast funcs
#include "../debug.h" // debug_print_player
#include <math.h> // math funcs
#include <string.h> // NULL
#include <stdbool.h> // bool

void	loop_logic(t_game *game, double fps_mult)
{
	game->player.mov_speed = MOV_SPEED * fps_mult;
	game->player.rot_speed = ROT_SPEED * fps_mult;
	handle_movement_keys(game->mlx, &game->player, &game->map);
	debug_print_player(&game->player);
}
