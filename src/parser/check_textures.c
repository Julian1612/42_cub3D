/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:49:00 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/21 10:57:29 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <stdio.h>

static int	check_char(t_map *map_data, char character);

int	check_mandatory_textures(t_map *map_data)
{
	if (map_data->north.path == NULL
		|| check_data_type(map_data->north.path, "xpm"))
		return (error_textures(6, map_data));
	else if (map_data->south.path == NULL
		|| check_data_type(map_data->south.path, "xpm"))
		return (error_textures(6, map_data));
	else if (map_data->west.path == NULL
		|| check_data_type(map_data->west.path, "xpm"))
		return (error_textures(6, map_data));
	else if (map_data->east.path == NULL
		|| check_data_type(map_data->east.path, "xpm"))
		return (error_textures(6, map_data));
	else if (map_data->floor_color == -1)
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
	if (character == 'D' && (map_data->door.path == NULL
		|| check_data_type(map_data->door.path, "xpm")))
		return (error_textures(7, map_data));
	else if (character == 'B' && (map_data->door.path == NULL
		|| check_data_type(map_data->door.path, "xpm")))
		return (error_textures(7, map_data));
	else if (character == 'E' && (map_data->door.path == NULL
		|| check_data_type(map_data->door.path, "xpm")))
		return (error_textures(7, map_data));
	return (0);
}
