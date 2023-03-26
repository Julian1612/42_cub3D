/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:15:43 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/26 18:40:11 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_minimap.h"
#include <stdio.h>
# define WALL_SIZE 30

double	get_wall_size(t_minimap *minimap)
{
	if (minimap->width > 35)
		return (10);
	else if (minimap->height > 30)
		return (20);
	// printf("hifasdfasfasdf\n");
	// else if (minimap->width > 30)
	// 	return (10);
	// else if (minimap->width > 20)
	// 	return (20);
	// return (30);
	return (30);
}

void draw_player(t_game *game)
{
	int			i;
	int			j;
	int			wall_size;
	uint32_t	color;

	i = 0;
	wall_size = get_wall_size(&game->minimap);
	color = convert_to_hexcode(255, 0, 0, 255);
	game->minimap.player->instances[0].x = game->player.x * wall_size + (WIDTH / 2) - ((game->map.width * wall_size) / 2);
	game->minimap.player->instances[0].y = game->player.y * wall_size + (HEIGHT / 2) - ((game->map.height * wall_size) / 2);
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
	int wall_size;
	uint32_t color;

	color = convert_to_hexcode(81, 86, 82, 255);
	wall_size = get_wall_size(minimap);
	k = i * wall_size;
	while (k < (i * wall_size) + wall_size) // 800 is the height of the window should be macro
	{
		l = j * wall_size;
		while(l < (j * wall_size) + wall_size)
		{
			mlx_put_pixel(minimap->walls, l, k, color);
			l++;
		}
		k++;
	}
}


void draw_minimap_floor(t_minimap *minimap, int i, int j)
{
	int k;
	int l;
	int wall_size;
	uint32_t color;

	color = convert_to_hexcode(200, 200, 200, 150);
	wall_size = get_wall_size(minimap);
	k = i * wall_size;
	while (k < (i * wall_size) + wall_size && k < 800) // 800 is the height of the window mshould be macro
	{
		l = j * wall_size;
		while(l < (j * wall_size) + wall_size)
		{
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
			else if (game->map.map[i][j] != ' ' && game->map.map[i][j] != '1')
				draw_minimap_floor(&game->minimap, i, j);
			// else if (game->map.map[i][j] == 'E')
			// 	draw_minimap_enemy(&game->minimap, i, j);
			j++;
		}
		i++;
	}
	return (0);
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

