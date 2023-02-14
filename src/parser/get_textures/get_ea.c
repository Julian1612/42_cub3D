/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ea.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:46:07 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/14 15:18:23 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include <stdio.h>

static int	get_path_ea(t_map *map_data, char **line_content)
{
	map_data->ea = malloc(sizeof(char) * ft_strlen(line_content[1]));
	if (map_data->ea == NULL)
	{
		return (1);
	}
	if (cpy_line(map_data->ea, line_content[1],
			ft_strlen(line_content[1]) - 1) == NULL)
	{
		error_message(4);
		return (1);
	}
	if (map_data->ea == NULL)
	{
		error_message(4);
		return (1);
	}
	return (0);
}

static int	get_data_ea(t_map *map_data, char *raw_line)
{
	char	**line_content;

	line_content = get_line_content(raw_line);
	if (line_content == NULL)
	{
		ft_free_arr(line_content);
		error_message(4);
		return (1);
	}
	if (get_path_ea(map_data, line_content))
	{
		ft_free_arr(line_content);
		return (1);
	}
	if (check_file(map_data->ea, "xpm"))
	{
		ft_free_arr(line_content);
		return (1);
	}
	ft_free_arr(line_content);
	return (0);
}

int	get_ea(t_map *map_data, char **raw_map)
{
	int	i;

	i = 0;
	if (finde_line("EA", raw_map, &i))
		return (1);
	if (get_data_ea(map_data, raw_map[i]))
		return (1);
	return (0);
}
