/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:44:25 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/02 18:41:22 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_minimap.h"
#include "../minimap.h"
#include <math.h>
#include <stdio.h>

void	render_surface(t_minimap *minimap, int i, int j, char symbol);

// int	draw_map(t_game *game)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (game->map.map[i] != NULL)
// 	{
// 		j = 0;
// 		while (game->map.map[i][j] != '\0')
// 		{
// 			render_surface(&game->minimap, i, j, game->map.map[i][j]);
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int draw_map(t_game *game)
{
	int	i_min, i_max, j_min, j_max;
	int	i, j, k, l;
	int	player_i, player_j;
	int	display_range = 5; // change this value to adjust the display range

	player_i = game->player.y;
	player_j = game->player.x;

	// calculate the range of cells to display
	l
	 // render each cell within the display range
	if (game->minimap.lmm_walls != NULL)
		mlx_delete_image(game->mlx, game->minimap.lmm_walls);
	game->minimap.lmm_walls = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	i = i_min;
	k = 0;
	while (i <= i_max)
	{
		j = j_min;
		l = 0;
		while (j <= j_max)
		{
			if (k == display_range && l == display_range)
			{
				render_surface(&game->minimap, k, l, 'P');
			}
			else
				render_surface(&game->minimap, k, l, game->map.map[i][j]);
			j++;
			l++;
		}
		i++;
		k++;
	}

	if (mlx_image_to_window(game->mlx, game->minimap.lmm_walls, 0, 0) == -1)
		mlx_close_window(game->mlx);
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
	else if (symbol == 'P')
		color = convert_to_hexcode(255, 0, 0, 255);
	else
		color = convert_to_hexcode(0, 0, 0, 0);
	wall_size = get_wall_size_map(minimap);
	k = i * wall_size;
	l = j * wall_size;
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
	return (fmin((WIDTH / 2) / minimap->width,
			(HEIGHT / 2) / minimap->height));
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
