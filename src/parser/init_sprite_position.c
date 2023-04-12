/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite_position.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:12:10 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/12 01:58:38 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include "../../libraries/libft/src/libft/libft.h" // ft_* functions
#include "../cub3D.h" // t_vec
#include <math.h>
#include <stdio.h>

static int		search_for_sprites(t_game *game, int i,
					char *line);
static int		get_sprites_count(t_map *map_data);
static void		init_enemy(t_map *map_data, int i, int j, int count_enemies);
static void		init_door(t_map *map_data, int i, int j, int count_doors);

int	init_sprite_position(t_game *game)
{
	int	i;

	i = 0;
	if (get_sprites_count(&game->map))
		return (0);
	if (game->map.enemy_count > 0)
	{
		game->map.enemies = malloc(sizeof(t_enemy) * game->map.enemy_count);
		if (game->map.enemies == NULL)
			return (error_message(4, &game->map));
	}
	if (game->map.door_count > 0)
	{
		game->map.doors = malloc(sizeof(t_door) * game->map.door_count);
		if (game->map.doors == NULL)
			return (error_message(4, &game->map));
	}
	game->map.height = ft_arrlen((void **)game->map.arr);
	while (game->map.arr[i] != NULL)
	{
		if (search_for_sprites(game, i, game->map.arr[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	get_sprites_count(t_map *map_data)
{
	int	i;
	int	j;
	int	line_len;

	i = 0;
	map_data->enemy_count = 0;
	map_data->door_count = 0;
	while (map_data->arr[i])
	{
		j = 0;
		line_len = ft_strlen(map_data->arr[i]);
		while (map_data->arr[i][j])
		{
			if (map_data->arr[i][j] == 'F')
				map_data->enemy_count++;
			else if (map_data->arr[i][j] == 'D')
				map_data->door_count++;
			j++;
		}
		i++;
	}
	return (0);
}

int	check_door_position(t_map *map, int i, int j, int line_len)
{
	if ((j == 0 || j == line_len - 1)
		|| (j < line_len && map->arr[i][j + 1] == ' ')
		|| (j > 0 && map->arr[i][j - 1] == ' '))
		return (error_get_map(10, map));
	return (0);
}

static int	search_for_sprites(t_game *game, int i,
			char *line)
{
	int			j;
	int			line_len;
	static int	count_enemies = 0;
	static int	count_doors = 0;

	j = 0;
	while (line[j] != '\0')
	{
		line_len = ft_strlen(line);
		if (line[j] == 'F' && count_enemies < game->map.enemy_count)
		{
			if ((j == 0 || j == line_len - 1)
				|| (j < line_len && line[j + 1] == ' ')
				|| (j > 0 && line[j - 1] == ' ')
				|| (i > 0 && i < game->map.height - 1
					&& (game->map.arr[i + 1][j] == ' '
					|| game->map.arr[i - 1][j] == ' ')))
				return (error_get_map(9, &game->map));
			init_enemy(&game->map, i, j, count_enemies++);
		}
		if (line[j] == 'D' && count_doors < game->map.door_count)
		{
			if ((j == 0 || j == line_len - 1)
				|| (j < line_len && game->map.arr[i][j + 1] == ' ')
				|| (j > 0 && game->map.arr[i][j - 1] == ' ')
				|| (i > 0 && i < game->map.height - 1
					&& (game->map.arr[i + 1][j] == ' '
					|| game->map.arr[i - 1][j] == ' ')))
				return (error_get_map(10, &game->map));
			init_door(&game->map, i, j, count_doors++);
		}
		j++;
	}
	return (0);
}

static void	init_enemy(t_map *map_data, int i, int j, int count_enemies)
{
	map_data->enemies[count_enemies].alive = true;
	map_data->enemies[count_enemies].pos.x = j + 0.5;
	map_data->enemies[count_enemies].pos.y = i + 0.5;
	map_data->enemies[count_enemies].health = 100;
	map_data->enemies[count_enemies].last_frame_time = 0;
	map_data->enemies[count_enemies].curr_frame = ZOMBIE_RUN1;
	map_data->enemies[count_enemies].speed = 0.1;
	map_data->enemies[count_enemies].damage = 10;
}

static void	init_door(t_map *map_data, int i, int j, int count_doors)
{
	map_data->doors[count_doors].x = j + 0.5;
	map_data->doors[count_doors].y = i + 0.5;
	map_data->doors[count_doors].open = false;
	map_data->doors[count_doors].last_action = 0;
}
