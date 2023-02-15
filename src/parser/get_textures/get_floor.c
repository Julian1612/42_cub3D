/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_floor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:22:00 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/15 14:56:34 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include <stdio.h>

static int	get_data_floor(t_map *map_data, char *raw_line);

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

static int	get_data_floor(t_map *map_data, char *raw_line)
{
	char	**line_content;

	line_content = ft_split(raw_line, ',');
	if (line_content == NULL)
	{
		error_message(4);
		free_textures(map_data);
		return (1);
	}
	remove_letter(line_content, 'F');
	if (ft_atoi(line_content[0]) > 255 || ft_atoi(line_content[1]) > 255
		|| ft_atoi(line_content[2]) > 255)
		return (1);
	if (ft_atoi(line_content[0]) < 0 || ft_atoi(line_content[1]) < 0
		|| ft_atoi(line_content[2]) < 0)
		return (1);
	map_data->floor_r = ft_atoi(line_content[0]);
	map_data->floor_g = ft_atoi(line_content[1]);
	map_data->floor_b = ft_atoi(line_content[2]);
	ft_free_arr(line_content);
	return (0);
}
