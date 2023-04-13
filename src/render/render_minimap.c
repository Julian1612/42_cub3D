/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:15:43 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/14 00:10:31 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h" // t_game
#include <string.h> // NULL

static void	draw_square(t_minimap *minimap, int i, int j, char symbol);
static void	draw_minimap(t_game *game);

void	minimap_render(t_game *game)
{
	draw_minimap(game);
}

static void	draw_minimap(t_game *game)
{
	int	i;
	int	j;
	int	k;
	int	l;

	k = 0;
	i = (int)(game->player.pos.y - 2);
	while (i <= game->player.pos.y + 2 && game->map.arr[i] != NULL)
	{
		j = (int) game->player.pos.x - 2;
		if (j < 0)
			j++;
		l = 0;
		while (j <= game->player.pos.x + 2 && game->map.arr[i][j] != '\0')
		{
			if (i == (int) game->player.pos.y && j == (int) game->player.pos.x)
				draw_square(&game->minimap, k, l, 'P');
			else
				draw_square(&game->minimap, k, l, game->map.arr[i][j]);
			j++;
			l++;
		}
		i++;
		k++;
	}
}

static void	draw_square(t_minimap *minimap, int i, int j, char symbol)
{
	int			k;
	int			l;
	t_hexcolor	color;

	if (symbol == ' ')
		return ;
	else if (symbol == '1')
		color = convert_to_hexcode(44, 44, 44, 255);
	else if (symbol == 'P')
		color = convert_to_hexcode(29, 126, 13, 255);
	else
		color = convert_to_hexcode(200, 200, 200, 150);
	k = i * MINIMAP_WALL_SIZE;
	while (k < (i * MINIMAP_WALL_SIZE) + MINIMAP_WALL_SIZE)
	{
		l = j * MINIMAP_WALL_SIZE;
		while (l < (j * MINIMAP_WALL_SIZE) + MINIMAP_WALL_SIZE)
		{
			mlx_put_pixel(minimap->minimap_walls, l, k, color);
			l++;
		}
		k++;
	}
}
