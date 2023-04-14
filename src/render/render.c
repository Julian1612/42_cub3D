/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:46:52 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 22:59:26 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_render.h" // render funcs
#include "../cub3D.h" // cub3D structs
#include <stdlib.h> // malloc, free

void	render_game(t_game *game)
{
	int	*wall_height;

	wall_height = malloc(sizeof(int) * game->img_world->width);
	walls_render(game, wall_height);
	free(wall_height);
}

bool	is_transparent(t_hexcolor color)
{
	if (color == 0x00000000)
		return (true);
	return (false);
}
