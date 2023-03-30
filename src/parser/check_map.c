/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:43:55 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/24 10:36:54 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <stdio.h>

static int	check_first_line(t_map *map_data);
static int	check_last_line(t_map *map_data);
static int	check_if_map_is_closed(t_map *map_data);
static int	check_line(t_map *map_data, int i, int j);

int	check_map(t_map *map_data)
{
	if (map_data->map == NULL)
		return (error_get_map(2, map_data));
	if (check_first_line(map_data))
		return (ERROR);
	if (check_last_line(map_data))
		return (ERROR);
	if (check_if_map_is_closed(map_data))
		return (ERROR);
	return (SUCCSES);
}

static int	check_first_line(t_map *map_data)
{
	int	i;

	i = 0;
	while (map_data->map[0][i] != '\0')
	{
		if (map_data->map[0][i] != '1'
			&& map_data->map[0][i] != ' ')
		{
			error_get_map(1, map_data);
			return (ERROR);
		}
		i++;
	}
	return (SUCCSES);
}

static int	check_last_line(t_map *map_data)
{
	int	i;
	int	map_len;

	i = 0;
	map_len = ft_arrlen((void **)map_data->map) - 1;
	while (map_data->map[map_len][i] != '\0')
	{
		if (map_data->map[map_len][i] != '1'
			&& map_data->map[map_len][i] != ' ')
		{
			error_get_map(1, map_data);
			return (ERROR);
		}
		i++;
	}
	return (SUCCSES);
}

static int	check_if_map_is_closed(t_map *map_data)
{
	int	i;
	int	j;

	i = 1;
	while (map_data->map[i + 1] != NULL)
	{
		j = 0;
		while (map_data->map[i][j] == ' ')
			j++;
		if (map_data->map[i][j] == '0')
			return (error_get_map(1, map_data));
		if (check_line(map_data, i, j))
			return (ERROR);
		i++;
	}
	return (SUCCSES);
}

static int	check_line(t_map *map_data, int i, int j)
{
	while (map_data->map[i][j] != '\0')
	{
		if (map_data->map[i][j] == '0')
		{
			if (j > 0 && map_data->map[i][j - 1] == ' ')
				return (error_get_map(1, map_data));
			else if (map_data->map[i][j + 1] == '\0'
				|| map_data->map[i][j + 1] == ' ')
				return (error_get_map(1, map_data));
			else if ((ft_strlen(map_data->map[i + 1]) >= j
					&& map_data->map[i + 1][j] == ' ')
				|| (ft_strlen(map_data->map[i - 1]) >= j
					&& map_data->map[i - 1][j] == ' '))
				return (error_get_map(1, map_data));
			else if (ft_strlen(map_data->map[i + 1]) <= j
				|| ft_strlen(map_data->map[i - 1]) <= j)
				return (error_get_map(1, map_data));
		}
		j++;
	}
	return (SUCCSES);
}