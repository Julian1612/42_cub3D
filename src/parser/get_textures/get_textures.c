/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:58:13 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/26 17:31:53 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_get_textures.h"
#include <stdio.h>

int	get_textures(t_map *map_data, char **raw_map)
{

	if (get_path(raw_map, "WE", &map_data->west))
		return (1);
	if (get_path(raw_map, "EA", &map_data->east))
		return (1);
	if (get_path(raw_map, "SO", &map_data->south))
		return (1);
	if (get_path(raw_map, "NO", &map_data->north))
		return (1);
	if (get_map_color(map_data->floor_rgb_arr, raw_map, "F"))
		return (1);
	if (get_map_color(map_data->ceiling_rgb_arr, raw_map, "C"))
		return (1);
	return (0);
}
