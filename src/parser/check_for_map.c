/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:47:06 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/07 14:41:41 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <stdio.h>

static int	init_map(t_map *map_data, char *line, int fd);

int	check_for_map(t_map *map_data, char *line, int fd)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	if (line[i] == '1')
	{
		init_map(map_data, line, fd);
		return (1);
	}
	return (0);
}

static int	init_map(t_map *map_data, char *line, int fd)
{
	char	*map_str;

	map_str = ft_strdup(line);
	if (map_str == NULL)
		return (error_message(4, map_data));
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line != NULL)
			map_str = ft_strjoin_cub3d(map_str, line);
		if (line != NULL && line[0] == '\n')
			break ;
		free(line);
	}
	get_next_line(-1);
	map_data->map = ft_split(map_str, '\n');
	free(map_str);
	free(line);
	return (0);
}
