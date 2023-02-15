/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:08:23 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/14 18:01:57 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include <stdio.h>

static int	finde_map_in_file(char **raw_map, int *i);
static int	remove_newline_from_arr(char **raw_map, int i);

int	get_map(t_map *map_data, char **raw_map)
{
	int	start_map;

	start_map = 0;
	if (finde_map_in_file(raw_map, &start_map))
		return (1);
	if (remove_newline_from_arr(raw_map, start_map))
		return (1);
	if (map_to_arr(raw_map, map_data, start_map))
		return (1);
	if (check_map(map_data->map))
		return (1);
	return (0);
}

static int	finde_map_in_file(char **raw_map, int *i)
{
	int		j;
	int		row_len;

	j = 0;
	while (raw_map[*i] != NULL)
	{
		row_len = ft_strlen(raw_map[*i]);
		while (j < row_len)
		{
			if (raw_map[*i][j] == 'S' || raw_map[*i][j] == 'N'
				|| raw_map[*i][j] == 'W' || raw_map[*i][j] == 'E'
				|| raw_map[*i][j] == 'C' || raw_map[*i][j] == 'F')
				break ;
			else if (raw_map[*i][j] == '1')
				return (0);
			j++;
		}
		j = 0;
		(*i)++;
	}
	return (1);
}

int static	remove_newline_from_arr(char **raw_map, int i)
{
	int		j;

	while (raw_map[i] != NULL)
	{
		j = 0;
		while (raw_map[i][j] != '\0')
		{
			if (raw_map[i][j] == '\n')
				raw_map[i][j] = ' ';
			j++;
		}
		i++;
	}
	return (0);
}
