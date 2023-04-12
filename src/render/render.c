/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:46:52 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/12 15:25:02 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_render.h" // render funcs
#include "../cub3D.h" // cub3D structs
#include <stdlib.h> // malloc, free

void	render_all(t_game *game)
{
	int	*wall_height;

	wall_height = malloc(sizeof(int) * game->img_world->width);
	walls_render(game, wall_height);
	enemies_render(game, game->map.objects, game->map.enemies, wall_height);
	hud_render(game);
	free(wall_height);
}