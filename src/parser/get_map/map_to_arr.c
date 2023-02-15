/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 15:29:46 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/15 10:45:22 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include <stdio.h>

static int	get_map_width(char **raw_map, int i, int *map_width);
static int	get_map_height(char **raw_map, int i, int *map_height);
static int	fill_map(char **map, char **raw_map, int start_map);
static int	fill_line(char *map, char *raw_map);

int	map_to_arr(char **raw_map, t_map *map_data, int start_map)
{
	int		map_width;
	int		map_height;

	if (get_map_width(raw_map, start_map, &map_width))
		return (1);
	if (get_map_height(raw_map, start_map, &map_height))
		return (1);
	if (malloc_map(&map_data->map, map_height, map_width))
		return (1);
	if (fill_map(map_data->map, raw_map, start_map))
		return (1);
	return (0);
}

static int	get_map_width(char **raw_map, int i, int *map_width)
{
	*map_width = 0;
	while (raw_map[i] != NULL)
	{
		if ((int) ft_strlen(raw_map[i]) > (*map_width))
			(*map_width) = ft_strlen(raw_map[i]);
		i++;
	}
	return (0);
}

static int	get_map_height(char **raw_map, int i, int *map_height)
{
	(*map_height) = 0;
	while (raw_map[i] != NULL)
	{
		(*map_height)++;
		i++;
	}
	return (0);
}

static int	fill_map(char **map, char **raw_map, int start_map)
{
	int		i_map;
	int		i_raw_map;

	i_map = 0;
	i_raw_map = start_map;
	while (raw_map[i_raw_map] != NULL)
	{
		fill_line(map[i_map], raw_map[i_raw_map]);
		i_map++;
		i_raw_map++;
	}
	ft_free_arr(raw_map);
	return (0);
}

static int	fill_line(char *map, char *raw_map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i] != '\0')
	{
		if (raw_map[j] == '\0')
			map[i] = ' ';
		else
		{
			map[i] = raw_map[j];
			j++;
		}
		i++;
	}
	return (0);
}
