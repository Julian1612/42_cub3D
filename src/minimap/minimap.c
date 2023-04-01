/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:15:43 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/01 18:14:23 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_minimap.h"
#include <stdio.h>
#include <math.h>

static void	draw_square(t_minimap *minimap, int i, int j, char symbol);

int	draw_minimap(t_game *game)
{
	int	i;
	int	j;
	int	k;
	int	l;

	k = 0;
	i = (int) (game->player.y - 2);
	mlx_delete_image(game->mlx, game->minimap.smm_walls);
	if (!(game->minimap.smm_walls = mlx_new_image(game->mlx, MINIMAP_WALL_SIZE * 5, MINIMAP_WALL_SIZE * 5)))
	{
		mlx_close_window(game->mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	while (i <= game->player.y + 2 && game->map.map[i] != NULL)
	{
		j = (int) game->player.x - 2;
		l = 0;
		while (j <= game->player.x + 2 && game->map.map[i][j] != '\0')
		{
			if (i == (int) game->player.y && j == (int) game->player.x)
				draw_square(&game->minimap, k, l, 'P');
			else
				draw_square(&game->minimap, k, l, game->map.map[i][j]);
			j++;
			l++;
		}
		i++;
		k++;
	}
	if (mlx_image_to_window(game->mlx, game->minimap.smm_walls, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	return (0);
}

static void	draw_square(t_minimap *minimap, int i, int j, char symbol)
{
	int			k;
	int			l;
	uint32_t	color;

	if (symbol == '1')
		color = convert_to_hexcode(81, 86, 82, 255);
	else if (symbol == '0')
		color = convert_to_hexcode(200, 200, 200, 150);
	else if (symbol == 'P')
		color = convert_to_hexcode(0, 200, 200, 150);
	k = i * MINIMAP_WALL_SIZE;
	while (k < (i * MINIMAP_WALL_SIZE) + MINIMAP_WALL_SIZE)
	{
		l = j * MINIMAP_WALL_SIZE;
		while (l < (j * MINIMAP_WALL_SIZE) + MINIMAP_WALL_SIZE)
		{
			mlx_put_pixel(minimap->smm_walls, l, k, color);
			l++;
		}
		k++;
	}
}

void	get_map_measures(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.map[i] != NULL)
	{
		j = 0;
		while (game->map.map[i][j] != '\0')
		{
			if (j > game->map.width)
				game->map.width = j;
			j++;
		}
		i++;
	}
	game->map.width++;
	game->map.height = i;
	game->minimap.width = game->map.width;
	game->minimap.height = game->map.height;
}
