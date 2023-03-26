/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:24:25 by lorbke            #+#    #+#             */
/*   Updated: 2023/03/26 22:13:49 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h" // t_game, t_map, t_player, t_texture, t_weapon
#include "../libraries/mlx/include/MLX42/MLX42.h" // mlx functions
#include "../libraries/libft/src/libft/libft.h" // ft_strlen
#include <stdlib.h> // NULL
#include <stdbool.h> // bool
#include <math.h> // M_PI
#include "minimap.h"
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
	double wall_size;

	if (!(game->minimap.player = mlx_new_image(game->mlx, 5, 5)))
	{
		mlx_close_window(game->mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(game->mlx, game->minimap.player, 0, 0git) == -1)
	{
		mlx_close_window(game->mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	// create game->minimap.get_map_measures();
	// if (!(game->minimap.walls = mlx_new_image(game->mlx, (WIDTH - game->minimap.width / 2) - game->minimap.width * 30 / 2, (HEIGHT - game->minimap.height / 2) - game->minimap.height * 30 / 2)))
	// {
	// 	mlx_close_window(game->mlx);
	// 	// puts(mlx_strerror(mlx_errno));
	// 	return(EXIT_FAILURE);
	// }
	// if (mlx_image_to_window(game->mlx, game->minimap.walls, (WIDTH / 2 - 50) - game->minimap.width * 30 / 2, (HEIGHT / 2 - 50)- game->minimap.height * 30 / 2) == -1)
	// {
	// 	mlx_close_window(game->mlx);
	// 	// puts(mlx_strerror(mlx_errno));
	// 	return(EXIT_FAILURE);
	// }
	// create game->minimap.get_map_measures();
	if (!(game->minimap.walls = mlx_new_image(game->mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(game->mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	get_map_measures(game);
	wall_size = get_wall_size(&game->minimap);
	if (mlx_image_to_window(game->mlx, game->minimap.walls, 10, 10) == -1)
	{
		mlx_close_window(game->mlx);
		// puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	game->minimap.visible = 0;
	game->minimap.walls->instances[0].z = 0;
	game->minimap.player->instances[0].z = 0;
	return (SUCCESS);
}

static int	initialize_textures(t_game *game)
{
	game->map.east.xpm = mlx_load_xpm42(game->map.east.path);
	game->map.west.xpm = mlx_load_xpm42(game->map.west.path);
	game->map.south.xpm = mlx_load_xpm42(game->map.south.path);
	game->map.north.xpm = mlx_load_xpm42(game->map.north.path);
	if (game->map.west.xpm == NULL || game->map.east.xpm == NULL
		|| game->map.south.xpm == NULL || game->map.north.xpm == NULL)
		return (ERROR);
	game->map.west.texture = &game->map.west.xpm->texture;
	game->map.east.texture = &game->map.east.xpm->texture;
	game->map.south.texture = &game->map.south.xpm->texture;
	game->map.north.texture = &game->map.north.xpm->texture;
	// @todo sprite initialization
	return (SUCCESS);
}

int	initialize_mlx_all(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	game->img_a = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (game->mlx == NULL || game->img_a == NULL)
		return (ERROR);
	// if (initialize_textures(game) == ERROR)
	// 	return (ERROR);
	// if (initialize_minimap(&game->minimap, game->mlx, game->map.map) == ERROR)
	// 	return (ERROR);
	return (SUCCESS);
}
