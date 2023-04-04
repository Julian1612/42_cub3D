/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:24:25 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/30 18:18:01 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game, t_map, t_player, t_texture, t_weapon
#include "../libraries/mlx/include/MLX42/MLX42.h" // mlx functions
#include "../libraries/libft/src/libft/libft.h" // ft_strlen
#include <stdlib.h> // NULL
#include <stdbool.h> // bool
#include <math.h> // M_PI

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

// @note what if a texture is missing and has to be skipped?
static int	initialize_textures(t_game *game)
{
	game->map.textures[NORTH].tex = mlx_load_png(game->map.textures[NORTH].path);
	game->map.textures[EAST].tex = mlx_load_png(game->map.textures[EAST].path);
	game->map.textures[SOUTH].tex = mlx_load_png(game->map.textures[SOUTH].path);
	game->map.textures[WEST].tex = mlx_load_png(game->map.textures[WEST].path);
	game->map.textures[SPRITE].tex = mlx_load_png(game->map.textures[SPRITE].path);
	if (!game->map.textures[NORTH].tex || !game->map.textures[EAST].tex
		|| !game->map.textures[SOUTH].tex || !game->map.textures[WEST].tex)
		return (ERROR);
	// @todo sprite initialization
	return (SUCCESS);
}

static int	initialize_environ(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	game->img_a = mlx_new_image(game->mlx, game->mlx->width, game->mlx->height);
	if (game->mlx == NULL || game->img_a == NULL)
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
