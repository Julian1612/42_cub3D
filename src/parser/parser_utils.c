/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 09:59:24 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/04 13:22:40 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include "string.h" // NULL
#include <stdio.h>

void	init_struct_null(t_map *map_data)
{
	int	i;

	i = 0;
	while (i < OBJ_COUNT)
	{
		map_data->objects[i].path = NULL;
		i++;
	}
	map_data->ceiling_color = -1;
	map_data->floor_color = -1;
	map_data->map = NULL;
}

int	get_map_size(t_map *map_data)
{
	int	i;
	int	j;

	i = 0;
	while (map_data->map[i] != NULL)
	{
		j = 0;
		while (map_data->map[i][j] != '\0')
			j++;
		i++;
	}
	printf("Map size: %d x %d\n", i, j);
	if (i > 297 || j > 297)
		return (error_get_map(3, map_data));
	return (0);
}
