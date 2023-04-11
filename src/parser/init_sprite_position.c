/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite_position.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 13:12:10 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/11 16:24:55 by jschneid         ###   ########.fr       */
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

// checken dass richtig gefreed wird !!!!!!!!!!
int	init_sprite_position(t_game *game)
{
	int	i;

	i = 0;
	get_sprites_count(&game->map);
	printf("enemy_count: %d\n", game->map.enemy_count);
	printf("door_count: %d\n", game->map.door_count);
	game->map.enemies = malloc(sizeof(t_enemy) * game->map.enemy_count);
	if (game->map.enemies == NULL)
		return (error_message(4, &game->map));
	game->map.doors = malloc(sizeof(t_door) * game->map.door_count);
	if (game->map.doors == NULL)
		return (error_message(4, &game->map));
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
		if (line[j] == 'F')
		{
			game->map.enemies[count_enemies].alive = true;
			game->map.enemies[count_enemies].pos.x = j + 0.5;
			game->map.enemies[count_enemies].pos.y = i + 0.5;
			game->map.enemies[count_enemies].health = 100;
			game->map.enemies[count_enemies].last_frame_time = 0;
			game->map.enemies[count_enemies].curr_frame = ZOMBIE_RUN1;
			game->map.enemies[count_enemies].speed = 0.1;
			game->map.enemies[count_enemies].damage = 10;
			count_enemies++;
		}
		else if (line[j] == 'D')
		{
			game->map.doors[count_doors].x = j + 0.5;
			game->map.doors[count_doors].y = i + 0.5;
			game->map.doors[count_doors].open = false;
			game->map.doors[count_doors].last_action = 0;
			count_doors++;
		}
		j++;
	}
	return (0);
}
