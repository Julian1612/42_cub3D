/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:24:25 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/14 06:40:53 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game, t_map, t_player, t_texture, t_weapon
#include "../libraries/mlx/include/MLX42/MLX42.h" // mlx functions
#include "../libraries/libft/src/libft/libft.h" // ft_strlen, ft_memset
#include <stdlib.h> // NULL
#include <stdbool.h> // bool
#include <math.h> // M_PI

#define PLAYER_SIZE 2
#define DIRECTION 2

static int	initialize_minimap(t_game *game)
{
	game->minimap.minimap_walls = mlx_new_image(game->mlx,
			MINIMAP_WALL_SIZE * 5, MINIMAP_WALL_SIZE * 5);
	if (game->minimap.minimap_walls == NULL)
		return (ERROR);
	game->minimap.visible = 0;
	return (SUCCESS);
}

static int	initialize_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < LAST)
	{
		game->map.textures[i].tex = mlx_load_png(game->map.textures[i].path);
		if (game->map.textures[i].tex == NULL)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static int	initialize_screens(t_game *game)
{
	game->start.img = mlx_new_image(game->mlx, WIDTH, HEIGHT + 2);
	game->game_over.img = mlx_new_image(game->mlx, WIDTH, HEIGHT + 2);
	game->win.img = mlx_new_image(game->mlx, WIDTH, HEIGHT + 2);
	if (game->start.img == NULL || game->game_over.img == NULL
		|| game->win.img == NULL)
		return (ERROR);
	game->start.frame.curr = START_BG1;
	game->game_over.frame.curr = START_BG1;
	game->win.frame.curr = START_BG1;
	game->start.active = true;
	game->game_over.active = false;
	game->win.active = false;
	game->start.frame.time_of_last = 0;
	game->game_over.frame.time_of_last = 0;
	game->win.frame.time_of_last = 0;
	return (SUCCESS);
}

static int	initialize_environ(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3=====D", false);
	game->img_world = mlx_new_image(game->mlx,
			game->mlx->width, game->mlx->height + 2);
	game->hud.img = mlx_new_image(game->mlx,
			game->mlx->width, game->mlx->height + 2);
	if (game->mlx == NULL || game->img_world == NULL || game->hud.img == NULL)
		return (ERROR);
	return (SUCCESS);
}

int	initialize_mlx_data(t_game *game)
{
	if (initialize_environ(game) == ERROR)
		return (ERROR);
	if (initialize_textures(game) == ERROR)
		return (ERROR);
	if (initialize_minimap(game) == ERROR)
		return (ERROR);
	if (initialize_screens(game) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
