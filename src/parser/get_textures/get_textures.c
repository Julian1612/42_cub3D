/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:58:13 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/08 13:12:32 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_get_textures.h"
#include <stdio.h>

// @todo add defines for we and ea etxc 

int	get_textures(t_map *map_data, char *path)
{
	if (get_path("WE", &map_data->west, path))
		return (1);
	if (get_path("EA", &map_data->east, path))
		return (1);
	if (get_path("SO", &map_data->south, path))
		return (1);
	if (get_path("NO", &map_data->north, path))
		return (1);
	if (get_map_color("F", map_data->floor_rgb_arr, path))
		return (1);
	if (get_map_color("C", map_data->ceiling_rgb_arr, path))
		return (1);
	return (0);
}
