/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:24:25 by lorbke            #+#    #+#             */
/*   Updated: 2023/04/07 19:14:31 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game, t_map, t_player, t_texture, t_weapon
#include "../libraries/mlx/include/MLX42/MLX42.h" // mlx functions
#include "../libraries/libft/src/libft/libft.h" // ft_strlen
#include <stdlib.h> // NULL
#include <stdbool.h> // bool
#include <math.h> // M_PI
#include <stdio.h> // printf

#define PLAYER_SIZE 2
#define DIRECTION 2

// static int	initialize_minimap(t_minimap *minimap, mlx_t *mlx, char **map)
// {
// 	minimap->player = mlx_new_image(mlx, PLAYER_SIZE, PLAYER_SIZE);
// 	minimap->view_dir = mlx_new_image(mlx, DIRECTION, DIRECTION);
// 	minimap->walls = mlx_new_image(mlx, MM_BLOCK_SIZE, MM_BLOCK_SIZE);
// 	if (!minimap->player || !minimap->view_dir || !minimap->walls)
// 		return (ERROR);
// 	minimap->player->pixels = ft_memset(minimap->player->pixels, 150,
// 			minimap->player->width * minimap->player->height * sizeof(int));
// 	minimap->view_dir->pixels = ft_memset(minimap->view_dir->pixels, 150,
// 			minimap->view_dir->width * minimap->view_dir->height * sizeof(int));
// 	minimap->walls->pixels = ft_memset(minimap->walls->pixels, 255,
// 			minimap->walls->width * minimap->walls->height * sizeof(int));
// 	if (!minimap->player->pixels || !minimap->view_dir->pixels
// 		|| !minimap->walls->pixels)
// 		return (ERROR);
// 	return (SUCCESS);
// }

int	initialize_minimap(t_game *game)
{
	get_map_measures(game);
	game->minimap.smm_walls = mlx_new_image(game->mlx,
			MINIMAP_WALL_SIZE * 5, MINIMAP_WALL_SIZE * 5);
	if (game->minimap.smm_walls == NULL)
		return (ERROR);
	if (mlx_image_to_window(game->mlx, game->minimap.smm_walls, 0, 0) == -1)
		return (ERROR);
	game->minimap.visible = 0;
	return (SUCCESS);
}

// int	initialize_map(t_game *game)
// {
// 	double	wall_size;
// 	int		height_square;
// 	int		width_square;

// 	get_map_measures(game);
// 	wall_size = get_wall_size_map(&game->minimap);
// 	height_square = (WIDTH - (game->minimap.width * wall_size)) / 2;
// 	width_square = (HEIGHT - (game->minimap.height * wall_size)) / 2;
// 	game->minimap.lmm_walls = mlx_new_image(game->mlx, WIDTH, HEIGHT);
// 	if (game->minimap.lmm_walls == NULL)
// 		return (EXIT_FAILURE);
// 	if (mlx_image_to_window(game->mlx, game->minimap.lmm_walls, height_square, width_square) == -1)
// 		return (EXIT_FAILURE);
// 	// game->minimap.visible = 0;
// 	return (SUCCESS);
// }

// @note what if a texture is missing and has to be skipped?
static int	initialize_textures(t_game *game)
{
	game->map.objects[NORTH].tex = mlx_load_png(game->map.objects[NORTH].path);
	game->map.objects[EAST].tex = mlx_load_png(game->map.objects[EAST].path);
	game->map.objects[SOUTH].tex = mlx_load_png(game->map.objects[SOUTH].path);
	game->map.objects[WEST].tex = mlx_load_png(game->map.objects[WEST].path);
	if (!game->map.objects[NORTH].tex || !game->map.objects[EAST].tex
		|| !game->map.objects[SOUTH].tex || !game->map.objects[WEST].tex)
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
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_HIDDEN);
	return (SUCCESS);
}

int	initialize_mlx_data(t_game *game)
{
	if (initialize_environ(game) == ERROR)
		return (ERROR);
	if (initialize_textures(game) == ERROR)
		return (ERROR);
	// if (initialize_minimap(&game->minimap, game->mlx, game->map.map) == ERROR)
	// 	return (ERROR);
	game->player.turn_to_the_curser = false; /// wo anders initzialisieren
	return (SUCCESS);
}
