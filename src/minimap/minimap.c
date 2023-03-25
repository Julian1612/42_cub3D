/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:15:43 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/25 10:50:55 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_minimap.h"
#include <stdio.h>
# define WALL_SIZE 5


void draw_player(t_game *game)
{
	int			i;
	int			j;
	uint32_t	color;

	i = 0;
	if (game->minimap.visible == 0)
		color = convert_to_hexcode(255, 0, 0, 255);
	else
		color = convert_to_hexcode(0, 0, 0, 0);
	game->minimap.player->instances[0].x = game->player.x * 5;
	game->minimap.player->instances[0].y = game->player.y * 5;
	while (i < game->minimap.player->height)
	{
		j = 0;
		while (j < game->minimap.player->width)
		{
			mlx_put_pixel(game->minimap.player, j, i, color);
			j++;
		}
		i++;
	}
}

void draw_minimap_wall(t_minimap *minimap, int i, int j)
{
	int k;
	int l;
	uint32_t color;

	printf("minimap->visible = %d\n", minimap->visible);
	if (minimap->visible == 0)
	{
		color = convert_to_hexcode(255, 255, 255, 255);
		printf("mini visible\n");
	}
	else
	{
		color = convert_to_hexcode(0, 0, 0, 0);
		printf("mini invisible\n");
	}
	k = i * WALL_SIZE;
	while (k < (i * WALL_SIZE) + WALL_SIZE)
	{
		l = j * WALL_SIZE;
		while(l < (j * WALL_SIZE) + WALL_SIZE)
		{
			// color = convert_to_hexcode(255, 255, 255, 255);
			mlx_put_pixel(minimap->walls, l, k, color);
			l++;
		}
		k++;
	}
}


int	draw_minimap(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.map[i] != NULL)
	{
		j = 0;
		while (game->map.map[i][j] != '\0')
		{
			if (game->map.map[i][j] == '1')
				draw_minimap_wall(&game->minimap, i, j);
			j++;
		}
		i++;
	}
	return (0);
}

