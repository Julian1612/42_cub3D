/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 09:59:24 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/07 16:40:49 by jschneid         ###   ########.fr       */
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
	map_data->ceiling_color = -1;
	map_data->floor_color = -1;
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
	if (i > 297 || j > 297)
		return (error_get_map(3, map_data));
	return (0);
}

int	is_all_digit(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != NULL)
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			if ((str[i][j] < '0' || str[i][j] > '9')
			&& str[i][j] != ' ' && str[i][j] != '\n')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	get_obj_nbr(int i)
{
	if (i == 0)
		return (NORTH);
	else if (i == 1)
		return (SOUTH);
	else if (i == 2)
		return (WEST);
	else if (i == 3)
		return (EAST);
	return (0);
}
