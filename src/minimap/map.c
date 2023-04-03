/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:44:25 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/03 15:58:36 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "private_minimap.h"
#include "../minimap.h"
#include <math.h>
#include <stdio.h>

void	render_surface(t_minimap *minimap, int i, int j, char symbol);

int	draw_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.map[i] != NULL)
	{
		j = 0;
		while (game->map.map[i][j] != '\0')
		{
			render_surface(&game->minimap, i, j, game->map.map[i][j]);
			j++;
		}
		i++;
	}
	return (0);
}

void	render_surface(t_minimap *minimap, int i, int j, char symbol)
{
	int			k;
	int			l;
	int			wall_size;
	uint32_t	color;

	if (symbol == '1')
		color = convert_to_hexcode(81, 86, 82, 255);
	else if (symbol == '0')
		color = convert_to_hexcode(200, 200, 200, 150);
	wall_size = get_wall_size_map(minimap);
	k = i * wall_size;
	while (k < (i * wall_size) + wall_size)
	{
		l = j * wall_size;
		while (l < (j * wall_size) + wall_size)
		{
			mlx_put_pixel (minimap->lmm_walls, l, k, color);
			l++;
		}
		k++;
	}
}

double	get_wall_size_map(t_minimap *minimap)
{
	return (fmin((WIDTH * 0.75) / minimap->width,
			(HEIGHT * 0.75) / minimap->height));
}

void	draw_player_map(t_game *game)
{
	int			i;
	int			j;
	int			wall_size;
	uint32_t	color;

	i = 0;
	wall_size = get_wall_size_map(&game->minimap);
	color = convert_to_hexcode(255, 0, 0, 255);
	game->minimap.player->instances[0].x = (game->player.x * wall_size)
		+ (WIDTH - (game->minimap.width * wall_size)) / 2;
	game->minimap.player->instances[0].y = (game->player.y * wall_size)
		+ (HEIGHT - (game->minimap.height * wall_size)) / 2;
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
