/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:15:43 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/12 21:05:33 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h" // t_game
#include <string.h> // NULL
#include <math.h>

static void	draw_square(t_minimap *minimap, int i, int j, char symbol);
static void	draw_minimap(t_game *game);

int	minimap_render(t_game *game)
{
	if (game->minimap.visible == false)
		return (0);
	mlx_delete_image(game->mlx, game->minimap.minimap_walls);
	game->minimap.minimap_walls = mlx_new_image(game->mlx,
			MINIMAP_WALL_SIZE * 5, MINIMAP_WALL_SIZE * 5);
	if (game->minimap.minimap_walls == NULL)
		mlx_close_window(game->mlx);
	draw_minimap(game);
	if (mlx_image_to_window(game->mlx, game->minimap.minimap_walls, 0, 0) == -1)
		mlx_close_window(game->mlx);
	return (0);
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
	uint32_t	color;

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

void	get_map_measures(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.arr[i] != NULL)
	{
		j = 0;
		while (game->map.arr[i][j] != '\0')
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

// lmm aus dem struct entfernen
void	change_maps(mlx_key_data_t keydata, void *param)
{
	t_minimap	*minimap;

	minimap = (t_minimap *)param;
	if (keydata.key == MLX_KEY_F && keydata.action == 0
		&& minimap->visible == 1)
	{
		minimap->minimap_walls->instances[0].enabled = false;
		minimap->visible = 0;
	}
	else if (keydata.key == MLX_KEY_F && keydata.action == 0
		&& minimap->visible == 0)
	{
		minimap->minimap_walls->instances[0].enabled = true;
		minimap->visible = 1;
	}
}
