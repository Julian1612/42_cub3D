/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ceiling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:22:15 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/17 18:03:19 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include <stdio.h>

static int	get_data_ceiling(t_map *map_data, char *raw_line);

int	get_ceiling(t_map *map_data, char **raw_map)
{
	int	i;

	i = 0;
	if (finde_line(raw_map, "C", &i))
		return (1);
	if (get_data_ceiling(map_data, raw_map[i]))
		return (1);
	return (0);
}

static int	get_data_ceiling(t_map *map_data, char *raw_line)
{
	char	**line_content;

	line_content = ft_split(raw_line, ',');
	if (line_content == NULL)
	{
		error_message(4);
		free_textures(map_data);
		return (1);
	}
	if (ft_arrlen(line_content) != 3)
	{
		error_message(14);
		free_textures(map_data);
		return (1);
	}
	remove_letter(line_content, 'C');
	if (check_rgb_values(line_content))
		return (1);
	map_data->ceiling_r = ft_atoi(line_content[0]);
	map_data->ceiling_g = ft_atoi(line_content[1]);
	map_data->ceiling_b = ft_atoi(line_content[2]);
	ft_free_arr(line_content);
	return (0);
}

int	check_rgb_values(char **line_content)
{
	if (ft_atoi(line_content[0]) > 255 || ft_atoi(line_content[1]) > 255
		|| ft_atoi(line_content[2]) > 255)
		return (1);
	if (ft_atoi(line_content[0]) < 0 || ft_atoi(line_content[1]) < 0
		|| ft_atoi(line_content[2]) < 0)
		return (1);
	return (0);
}
