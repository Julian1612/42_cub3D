/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 18:33:29 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/22 14:22:04 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_get_map.h"

static void	init_line(char *line, int map_width);

int	malloc_map(char ***map, int map_height, int map_width)
{
	int	i;

	i = 0;
	*map = (char **)malloc(sizeof(char *) * (map_height + 1));
	if (*map == NULL)
	{
		error_get_map(4);
		return (1);
	}
	(*map)[map_height] = NULL;
	while (i < map_height)
	{
		(*map)[i] = (char *)malloc(sizeof(char) * (map_width + 1));
		if ((*map)[i] == NULL)
		{
			error_get_map(4);
			return (1);
		}
		init_line((*map)[i], map_width);
		i++;
	}
	return (0);
}

static void	init_line(char *line, int map_width)
{
	int	i;

	i = 0;
	while (i < map_width)
	{
		line[i] = ' ';
		i++;
	}
	line[i] = '\0';
}
