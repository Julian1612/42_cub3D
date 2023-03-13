/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:43:55 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/13 22:08:17 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <stdio.h>

static int	check_first_line(t_map *map_data);

int	check_map(t_map *map_data)
{
	if (check_first_line(map_data))
		return (1);
	if (check_last_line(map_data))
		return (1);
	// if (check_if_map_is_closed(map_data))
	// 	return (1);
	// if (check_for_invalid_chars(map_data))
	// 	return (1);
	return (0);
}

static int	check_first_line(t_map *map_data)
{
	int	i;

	i = 0;
	while (map_data->map[0][i] != '\0')
	{
		if (map_data->map[0][i] != '1'
			|| map_data->map[0][i] != ' ')
		{
			error_get_mpa(1);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_last_line(t_map *map_data)
{
	int	i;
	int	map_len;

	i = 0;
	map_len = ft_arrlen(map_data->map) - 1;
	while (map_data->map[map_len][i] != '\0')
	{
		if (map_data->map[map_len][i] != '1'
			|| map_data->map[map_len][i] != ' ')
		{
			error_get_mpa(1);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	map_is_closed(t_map *map_data)
{
	int	i;
	int	j;

	i = 0;
	while (map_data->map[i + 1] != NULL)
	{
		j = 0;
		while (map_data->map[i][j] != NULL)
		{
			if (map_data->map[i][j] == '0')
			{
				if (map_data->map[i][j + 1] == '\0')
					return (1);
				else if (map_data->map[i][j + 1] == ' ')
					return (1);
				else if (ft_strlen(map_data->map[i - 1]) >= j
					&& map_data->map[i - 1][j] == ' ')
				{
					printf("map is not closed\n");
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

// static int	check_if
static int	check_for_invalid_chars(t_map *map_data)
{
	int	i;
	int	j;

	i = 0;
	while (map_data->map[i] != '\0')
	{
		j = 0;
		while (map_data->map[i][j] != '\0')
		{
			if (map_data->map[i][j] != '0' || map_data->map[i][j] != '1'
				|| map_data->map[i][j] != 'C' || map_data->map[i][j] != 'F'
				|| map_data->map[i][j] != 'D' || map_data->map[i][j] != 'B'
				|| map_data->map[i][j] != 'E')
			{
				error_get_mpa(5);
				return (1);
			}
			j++;
		}
		i++;
	}
}
