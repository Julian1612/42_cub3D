/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_floor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:22:00 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/07 13:00:01 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

static int	get_data_floor(t_map *map_data, char *raw_line)
{
	int		i;
	char	**line_content;

	i = 0;
	line_content = ft_split(raw_line, ',');
	if (line_content == NULL)
		return (1);
	while (line_content[0][i] != '\0')
	{
		if (line_content[0][i] == 'F')
			line_content[0][i] = ' ';
		i++;
	}
	if (ft_atoi(line_content[0]) > 255 || ft_atoi(line_content[1]) > 255
		|| ft_atoi(line_content[2]) > 255)
		return (1);
	if (ft_atoi(line_content[0]) < 0 || ft_atoi(line_content[1]) < 0
		|| ft_atoi(line_content[2]) < 0)
		return (1);
	map_data->floor_r = ft_atoi(line_content[0]);
	map_data->floor_g = ft_atoi(line_content[1]);
	map_data->floor_b = ft_atoi(line_content[2]);
	return (0);
}

int	get_floor(t_map *map_data, char **raw_map)
{
	int	i;

	i = 0;
	if (finde_line("F", raw_map, &i))
		return (1);
	if (get_data_floor(map_data, raw_map[i]))
		return (1);
	return (0);
}
