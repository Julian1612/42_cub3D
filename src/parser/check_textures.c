/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:49:00 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/10 18:35:31 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"
#include "private_parser.h"
#include <fcntl.h> // open
#include <unistd.h> // close

static int	check_char(t_map *map_data, char character);

int	check_textures_file(t_map *map_data, char *cub_file_path, char *data_type)
{
	int	fd;

	if (check_data_type(cub_file_path, data_type))
		return (error_message(9, map_data));
	fd = open(cub_file_path, O_RDONLY);
	if (fd < 0)
		return (error_message(10, map_data));
	close(fd);
	return (0);
}

int	check_mandatory_textures(t_map *map_data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (map_data->objects[i].tex->path == NULL)
			return (error_textures(6, map_data));
		else if (check_textures_file(map_data,
				map_data->objects[i].tex->path, "png"))
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
	while (map_data->arr[i] == NULL)
	{
		j = 0;
		while (map_data->arr[i][j])
		{
			if (check_char(map_data, map_data->arr[i][j]))
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
	// if (character == CHAR_DOOR && map_data->objects[DOOR_].path == NULL)
	// 	return (error_textures(7, map_data));
	return (0);
}
