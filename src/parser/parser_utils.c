/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 09:59:24 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/09 10:22:05 by jschneid         ###   ########.fr       */
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

bool	contains_only_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			return (false);
		i++;
	}
	return (true);
}

int	check_for_new_line(char **splitted_str, int *error)
{
	if (splitted_str[0][0] == '\n' || splitted_str[1][0] == '\n'
	|| splitted_str[2][0] == '\n')
	{
		ft_free_arr((void **)splitted_str);
		*error = 1;
		return (1);
	}
	return (0);
}
