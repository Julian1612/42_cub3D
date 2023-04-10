/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:24:25 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/10 22:56:54 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game, t_map, t_player, t_texture, t_weapon
#include "../libraries/mlx/include/MLX42/MLX42.h" // mlx functions
#include "../libraries/libft/src/libft/libft.h" // ft_strlen
#include <stdlib.h> // NULL
#include <stdbool.h> // bool
#include <math.h> // M_PI
#include <stdio.h> // @note remove, printf

#define PLAYER_SIZE 2
#define DIRECTION 2

static int	initialize_minimap(t_minimap *minimap, mlx_t *mlx, char **map)
{
	minimap->player = mlx_new_image(mlx, PLAYER_SIZE, PLAYER_SIZE);
	minimap->view_dir = mlx_new_image(mlx, DIRECTION, DIRECTION);
	minimap->walls = mlx_new_image(mlx, MM_BLOCK_SIZE, MM_BLOCK_SIZE);
	if (!minimap->player || !minimap->view_dir || !minimap->walls)
		return (ERROR);
	minimap->player->pixels = ft_memset(minimap->player->pixels, 150,
			minimap->player->width * minimap->player->height * sizeof(int));
	minimap->view_dir->pixels = ft_memset(minimap->view_dir->pixels, 150,
			minimap->view_dir->width * minimap->view_dir->height * sizeof(int));
	minimap->walls->pixels = ft_memset(minimap->walls->pixels, 255,
			minimap->walls->width * minimap->walls->height * sizeof(int));
	if (!minimap->player->pixels || !minimap->view_dir->pixels
		|| !minimap->walls->pixels)
		return (ERROR);
	return (SUCCESS);
}

// @note every texture is loaded at all times
// @note better way of getting texture count?
static int	initialize_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i <= ZOMBIE_DEAD8)
	{
		game->map.textures[i].tex = mlx_load_png(game->map.textures[i].path);
		if (game->map.textures[i].tex == NULL)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static int	initialize_environ(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	game->img_world = mlx_new_image(game->mlx, game->mlx->width, game->mlx->height);
	game->img_hud = mlx_new_image(game->mlx, game->mlx->width, game->mlx->height);
	if (game->mlx == NULL || game->img_world == NULL || game->img_hud == NULL)
		return (ERROR);
	return (SUCCESS);
}

int	initialize_mlx_data(t_game *game)
{
	if (initialize_environ(game) == ERROR)
		return (ERROR);
	if (initialize_textures(game) == ERROR)
		return (ERROR);
	if (initialize_minimap(&game->minimap, game->mlx, game->map.arr) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
