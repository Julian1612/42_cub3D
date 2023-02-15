/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall_vertical.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 14:13:37 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/15 10:53:18 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include <stdio.h>

static int	check_top_to_bottom(char **raw_map, int i, int j);
static int	check_bottom_to_top(char **raw_map, int i, int j);
static int	get_map_len(char **raw_map, int i);

int	check_wall_vertical(char **raw_map)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (raw_map[i][j] != '\0')
	{
		if (check_top_to_bottom(raw_map, i, j))
		{
			error_message(6);
			return (1);
		}
		if (check_bottom_to_top(raw_map, i, j))
		{
			error_message(6);
			return (1);
		}
		j++;
	}
	return (0);
}

static int	check_top_to_bottom(char **raw_map, int i, int j)
{
	while (raw_map[i] != NULL)
	{
		if (raw_map[i][j] == '1')
		{
			while (raw_map[i] != NULL && raw_map[i][j] != ' ')
				i++;
			if (raw_map[i - 1][j] != '1')
				return (1);
		}
		i++;
	}
	return (0);
}

static int	check_bottom_to_top(char **raw_map, int i, int j)
{
	int		map_len;
	int		map_start;

	map_len = get_map_len(raw_map, i);
	map_start = i - 1;
	i += (map_len - 1);
	while (i > map_start)
	{
		if (raw_map[i][j] == '1')
		{
			while (i > map_start && raw_map[i][j] != ' ')
				i--;
			if (raw_map[i + 1][j] != '1')
				return (1);
		}
		i--;
	}
	return (0);
}

static int	get_map_len(char **raw_map, int i)
{
	int		map_len;

	map_len = 0;
	while (raw_map[i] != NULL)
	{
		map_len++;
		i++;
	}
	return (map_len);
}
