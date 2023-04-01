/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:15:43 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/01 17:54:51 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_minimap.h"
#include <stdio.h>
#include <math.h>

void	draw_square(t_minimap *minimap, int i, int j, char symbol)
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

double	get_wall_size_i(t_minimap *minimap)
{
	return (fmin((WIDTH * 0.75) / minimap->width,
			(HEIGHT * 0.75) / minimap->height));
}

void	draw_player_i(t_game *game)
{
	int			i;
	int			j;
	int			wall_size;
	uint32_t	color;

	i = 0;
	wall_size = get_wall_size_i(&game->minimap);
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

void	draw_minimap_wall_i(t_minimap *minimap, int i, int j)
{
	int			k;
	int			l;
	int			wall_size;
	uint32_t	color;

	color = convert_to_hexcode(81, 86, 82, 255);
	wall_size = get_wall_size_i(minimap);
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

void	draw_minimap_floor_i(t_minimap *minimap, int i, int j)
{
	int			k;
	int			l;
	int			wall_size;
	uint32_t	color;

	color = convert_to_hexcode(200, 200, 200, 150);
	wall_size = get_wall_size_i(minimap);
	k = i * wall_size;
	while (k < (i * wall_size) + wall_size && k < 800)
	{
		l = j * wall_size;
		while (l < (j * wall_size) + wall_size)
		{
			mlx_put_pixel(minimap->lmm_walls, l, k, color);
			l++;
		}
		k++;
	}
}

int	draw_minimap_i(t_game *game)
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
				draw_minimap_wall_i(&game->minimap, i, j);
			else if (game->map.map[i][j] != ' ' && game->map.map[i][j] != '1')
				draw_minimap_floor_i(&game->minimap, i, j);
			// else if (game->map.map[i][j] == 'E')
			// 	draw_minimap_enemy(&game->minimap, i, j);
			j++;
		}
		i++;
	}
	return (0);
}
