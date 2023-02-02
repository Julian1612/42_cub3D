/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_we.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:46:22 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/02 15:49:10 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

static int	finde_line(char *direction, char **raw_map, int *i)
{
	int	count;
	int	i_save;
	int	line_len;

	count = 0;
	i_save = *i;
	line_len = ft_strlen(raw_map[*i]);
	while (raw_map[*i])
	{
		if (line_len >= 2
			&& ft_strnstr(raw_map[*i], direction, line_len) != NULL)
		{
			i_save = *i;
			count++;
		}
		(*i)++;
	}
	if (count > 1)
	{
		error_message(5);
		return (1);
	}
	*i = i_save;
	return (0);
}

// arr line content must all be freed before return
static int	get_path_we(t_map *map_data, char *raw_line)
{
	char	**line_content;

	line_content = ft_split(raw_line, ' ');
	if (line_content == NULL)
	{
		error_message(4);
		return (4);
	}
	if (ft_arrlen(line_content) < 2)
	{
		error_message(5);
		return (1);
	}

	map_data->we = ft_strdup(line_content[1]);
	if (map_data->we == NULL)
	{
		error_message(4);
		return (1);
	}
	ft_free_arr(line_content);
	return (0);
}

int	get_we(t_map *map_data, char **raw_map)
{
	int	i;

	i = 0;
	if (finde_line("WE", raw_map, &i))
		return (1);
	if (get_path_we(map_data, raw_map[i]))
		return (1);
	printf("WE: %s", map_data->we);
	return (0);
}
