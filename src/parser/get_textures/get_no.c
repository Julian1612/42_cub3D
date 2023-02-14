/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_no.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:46:14 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/14 15:18:30 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include <stdio.h>

static int	get_path_ea(t_map *map_data, char **line_content)
{
	map_data->no = malloc(sizeof(char) * ft_strlen(line_content[1]));
	if (map_data->no == NULL)
	{
		return (1);
	}
	if (cpy_line(map_data->no, line_content[1],
			ft_strlen(line_content[1]) - 1) == NULL)
	{
		error_message(4);
		return (1);
	}
	if (map_data->no == NULL)
	{
		error_message(4);
		return (1);
	}
	return (0);
}

static int	get_data_no(t_map *map_data, char *raw_line)
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
	if (check_file(map_data->no, "xpm"))
	{
		ft_free_arr(line_content);
		return (1);
	}
	ft_free_arr(line_content);
	return (0);
}

int	get_no(t_map *map_data, char **raw_map)
{
	int	i;

	i = 0;
	if (finde_line("NO", raw_map, &i))
		return (1);
	if (get_data_no(map_data, raw_map[i]))
		return (1);
	return (0);
}
