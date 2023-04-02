/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:49:00 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/02 17:51:20 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
#include "private_parser.h"
#include <stdio.h>

static int	check_char(t_map *map_data, char character);

int	check_mandatory_textures(t_map *map_data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (map_data->objects[i].path == NULL)
			return (error_textures(6, map_data));
		i++;
	}
	if (map_data->floor_color == -1)
		return (error_textures(4, map_data));
	else if (map_data->ceiling_color == -1)
		return (error_textures(4, map_data));
	return (0);
}

int	check_bonus_textures(t_map *map_data)
{
	int			i;
	int			j;

	i = 0;
	while (map_data->map[i] == NULL)
	{
		j = 0;
		while (map_data->map[i][j])
		{
			if (check_char(map_data, map_data->map[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	check_char(t_map *map_data, char character)
{
	if (character == CHAR_DOOR && map_data->objects[DOOR].path == NULL)
		return (error_textures(7, map_data));
	else if (character == CHAR_BARREL && map_data->objects[BARREL].path == NULL)
		return (error_textures(7, map_data));
	// else if (character == CHAR_ENEMY && map_data->enemy.path == NULL)
	// 	return (error_textures(7, map_data));
	return (0);
}
