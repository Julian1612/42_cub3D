/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 09:49:00 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/17 15:25:08 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include "stdio.h"

static int	check_char(t_map *map_data, char character);

int	check_mandatory_textures(t_map *map_data)
{
	if (map_data->north == NULL)
		return (error_textures(6, map_data));
	else if (map_data->south == NULL)
		return (error_textures(6, map_data));
	else if (map_data->west == NULL)
		return (error_textures(6, map_data));
	else if (map_data->east == NULL)
		return (error_textures(6, map_data));
	else if (map_data->floor_rgb_arr[0] == -1
		|| map_data->floor_rgb_arr[1] == -1
		|| map_data->floor_rgb_arr[2] == -1)
		return (error_textures(4, map_data));
	else if (map_data->ceiling_rgb_arr[0] == -1
		|| map_data->ceiling_rgb_arr[1] == -1
		|| map_data->ceiling_rgb_arr[2] == -1)
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
	// if (character == 'D' && map_data->door == NULL)
	// 	return (error_textures(7));
	// else if (character == 'B' && map_data->barrel == NULL)
	// 	return (error_textures(7));
	// else if (character == 'E' && map_data->enemy == NULL)
	// 	return (error_textures(7));
	return (0);
}
