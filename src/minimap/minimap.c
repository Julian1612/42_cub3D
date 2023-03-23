/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:15:43 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/23 10:08:57 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_minimap.h"
#include <stdio.h>

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void draw_wall(t_minimap *minimap_data, int i, int j, int square_size)
{
	int k;
	int l;

	k = i * square_size;
	while (k < (i * square_size) + square_size)
	{
		l = j * square_size;
		// printf("\x1b[34mdraw square: i = %d\n\x1b[0m\n", k);
		while(l < (j * square_size) + square_size)
		{
			// printf("\x1b[34mdraw square: j = %d\n\x1b[0m\n", l);
			uint32_t color = convert_to_hexcode(169, 169, 169, 255);
			mlx_put_pixel(minimap_data->walls, l, k, color);
			l++;
		}
		k++;
	}
}

void draw_player(t_game *game)
{
	for (int32_t i = 0; i < game->minimap.player->width; ++i)
	{
		for (int32_t y = 0; y < game->minimap.player->height; ++y)
		{
			uint32_t color = ft_pixel(
				rand() % 0xFF, // R
				rand() % 0xFF, // G
				rand() % 0xFF, // B
				rand() % 0xFF  // A
			);
			mlx_put_pixel(game->minimap.player, i, y, color);
		}
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
		// printf("start-line--------------------\n");
		// printf("\x1b[31mdraw_minimap; i = %d\n\x1b[0m\n", i);
		while (game->map.map[i][j] != '\0')
		{
			// printf("\x1b[31mdraw_minimap; j = %d\n\x1b[0m\n", j);
			if (game->map.map[i][j] == '1')
				draw_wall(&game->minimap, i, j, 10);
			j++;
		}
		// printf("\x1b[0m\nend-line--------------------\n\x1b[0m\n");
		i++;
	}
	return (0);
}

// void	draw_player(void *param)
// {
// 	t_game* game = param;
// 	draw_square(&game->minimap, game->player.x, game->player.y, 10);
// }
