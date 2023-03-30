/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:15:43 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/30 10:09:56 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_minimap.h"
#include <stdio.h>
#include <math.h>
# define WALL_SIZE 30

double  get_wall_size(t_minimap *minimap)
{
	// return ((double) fmin((WIDTH) / minimap->width, (HEIGHT) / minimap->height));
	return (WALL_SIZE);
}

void draw_player(t_minimap *minimap, int i, int j)
{
	int k;
	int l;
	int wall_size;
	uint32_t color;

	color = convert_to_hexcode(255, 0, 0, 255);
	wall_size = get_wall_size(minimap);
	k = i * wall_size;
	while (k < (i * wall_size) + wall_size) // 800 is the height of the window should be macro
	{
		l = j * wall_size;
		while(l < (j * wall_size) + wall_size)
		{
			mlx_put_pixel(minimap->smm_walls, l, k, color);
			l++;
		}
		k++;
	}
}

void draw_minimap_wall(t_minimap *minimap, int i, int j)
{
	int k;
	int l;
	double wall_size;
	uint32_t color;

	color = convert_to_hexcode(81, 86, 82, 255);
	wall_size = get_wall_size(minimap);
	k = i * wall_size;
	while (k < (i * wall_size) + wall_size) // 800 is the height of the window should be macro
	{
		l = j * wall_size;
		while(l < (j * wall_size) + wall_size)
		{
			mlx_put_pixel(minimap->smm_walls, l, k, color);
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
	while (k < (i * wall_size) + wall_size) // 800 is the height of the window should be macro
	{
		l = j * wall_size;
		while(l < (j * wall_size) + wall_size)
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
	int	test1 = 0;
	int	test2;
	int wall_size = get_wall_size(&game->minimap);

	i = (int) (game->player.y - 2);
	mlx_delete_image(game->mlx, game->minimap.smm_walls);
	if (!(game->minimap.smm_walls = mlx_new_image(game->mlx, wall_size * 5, wall_size * 5)))
	{
		mlx_close_window(game->mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	while (i <= game->player.y + 2 && game->map.map[i] != NULL)
	{
		j = (int) game->player.x - 2;
		test2 = 0;
		while (j <= game->player.x + 2 && game->map.map[i][j] != '\0')
		{
			if (i == (int) game->player.y && j == (int) game->player.x)
				draw_player(&game->minimap, test1, test2);
			else if (game->map.map[i][j] == '1')
				draw_minimap_wall(&game->minimap, test1, test2);
			else if (game->map.map[i][j] != ' ' && game->map.map[i][j] != '1')
				draw_minimap_floor(&game->minimap, test1, test2);
			// else if (game->map.map[i][j] == 'E')
			// 	draw_minimap_enemy(&game->minimap, i, j);
			j++;
			test2++;
		}
		i++;
		test1++;
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

double get_wall_size_i(t_minimap *minimap)
{
	double square_size_width = (WIDTH * 0.75) / minimap->width;
	double square_size_height = (HEIGHT * 0.75) / minimap->height;
	return fmin(square_size_width, square_size_height);
}


void draw_player_i(t_game *game)
{
	int			i;
	int			j;
	int			wall_size;
	uint32_t	color;

	i = 0;
	wall_size = get_wall_size_i(&game->minimap);
	color = convert_to_hexcode(255, 0, 0, 255);
	game->minimap.player->instances[0].x = (game->player.x * wall_size) + (WIDTH - (game->minimap.width * wall_size)) / 2;
	game->minimap.player->instances[0].y = (game->player.y * wall_size ) + (HEIGHT - (game->minimap.height * wall_size)) / 2;
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

void draw_minimap_wall_i(t_minimap *minimap, int i, int j)
{
	int k;
	int l;
	int wall_size;
	uint32_t color;

	color = convert_to_hexcode(81, 86, 82, 255);
	wall_size = get_wall_size_i(minimap);
	k = i * wall_size;
	while (k < (i * wall_size) + wall_size) // 800 is the height of the window should be macro
	{
		l = j * wall_size;
		while(l < (j * wall_size) + wall_size)
		{
			mlx_put_pixel(minimap->lmm_walls, l, k, color);
 			l++;
		}
		k++;
	}
}


void draw_minimap_floor_i(t_minimap *minimap, int i, int j)
{
	int k;
	int l;
	int wall_size;
	uint32_t color;

	color = convert_to_hexcode(200, 200, 200, 150);
	wall_size = get_wall_size_i(minimap);
	k = i * wall_size;
	while (k < (i * wall_size) + wall_size && k < 800) // 800 is the height of the window mshould be macro
	{
		l = j * wall_size;
		while(l < (j * wall_size) + wall_size)
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

