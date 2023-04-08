/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:49:00 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/08 13:14:25 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
#include "private_parser.h"
#include <stdio.h>

static int	check_char(t_map *map_data, char character);

int	check_textures_file(t_map *map_data, char *cub_file_path, char *data_type)
{
	int	fd;

	if (check_data_type(cub_file_path, data_type))
	{
		return (error_message(9, map_data));
	}
	fd = open(cub_file_path, O_RDONLY);
	if (fd < 0)
	{
		////////// heir muss richtig gefreed werden
		return (error_message(10, map_data));
	}
	close(fd);
	return (0);
}

int	check_mandatory_textures(t_map *map_data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (map_data->objects[i].path == NULL)
			return (error_textures(6, map_data));
		else if (check_textures_file(map_data, map_data->objects[i].path, "png"))
			return (1);
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

// add the check for the other bonus textures
// else if (character == CHAR_ENEMY && map_data->enemy.path == NULL)
// 	return (error_textures(7, map_data));
static int	check_char(t_map *map_data, char character)
{
	if (character == CHAR_DOOR && map_data->objects[DOOR].path == NULL)
		return (error_textures(7, map_data));
	else if (character == CHAR_BARREL && map_data->objects[BARREL].path == NULL)
		return (error_textures(7, map_data));
	return (0);
}
