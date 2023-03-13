/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:47:06 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/13 09:59:50 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"

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
	{
		error_message(4);
		return (1);
	}
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (line != NULL)
			map_str = ft_strjoin(map_str, line);
	}
	map_data->map = ft_split(map_str, '\n');
	return (0);
}
