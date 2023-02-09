/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 14:08:23 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/08 11:24:36 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

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
			{
				(*i)++;
				return (0);
			}
			j++;
		}
		j = 0;
		(*i)++;
	}
	return (1);
}

int	get_map(t_map *map_data, char **raw_map)
{
	int	i;

	i = 0;
	(void)map_data;
	if (finde_map_in_file(raw_map, &i))
		return (1);
	printf("i: %d\n", i);
	return (0);
}
