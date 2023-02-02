/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ea.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:46:07 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/02 14:10:01 by jschneid         ###   ########.fr       */
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

// check for correct data type
// check if file exists

static int	get_path_ea(t_map *map_data, char *raw_line)
{
	char	**line_content;

	line_content = ft_split(raw_line, ' ');
	if (ft_arrlen(line_content) < 2)
	{
		error_message(5);
		return (1);
	}
	map_data->ea = ft_strdup(line_content[1]);
	return (0);
}

int	get_ea(t_map *map_data, char **raw_map)
{
	int	i;

	i = 0;
	if (finde_line("EA", raw_map, &i))
		return (1);
	if (get_path_ea(map_data, raw_map[i]))
		return (1);
	return (0);
}
