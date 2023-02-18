/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:58:13 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/18 10:18:03 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include <stdio.h>

int	get_textures(t_map *map_data, char **raw_map)
{
	if (get_path(raw_map, "WE", &map_data->west))
		return (1);
	if (get_path(raw_map, "EA", &map_data->east))
		return (1);
	if (get_path(raw_map, "SO", &map_data->south))
		return (1);
	if (get_path(raw_map, "NO", &map_data->north))
		return (1);
	if (get_map_color(map_data->floor_rgb_arr, raw_map, "F"))
		return (1);
	if (get_map_color(map_data->ceiling_rgb_arr, raw_map, "C"))
		return (1);
	return (0);
}

char	*cpy_line(char *dest, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// hier muss gecheckt ob fiel wirklich empty oder malloc error !!!
char	**get_line_content(char *raw_line)
{
	char	**line_content;

	line_content = ft_split(raw_line, ' ');
	if (line_content == NULL)
	{
		error_message(8);
		return (NULL);
	}
	return (line_content);
}

int	finde_line(char **raw_map, char *direction, int *i)
{
	int	count;
	int	i_save;
	int	line_len;

	count = 0;
	i_save = *i;
	while (raw_map[*i])
	{
		line_len = ft_strlen(raw_map[*i]);
		if (line_len >= 2
			&& ft_strnstr(raw_map[*i], direction, line_len) != NULL)
		{
			i_save = *i;
			count++;
		}
		(*i)++;
	}
	if (count == 0 && ft_arrlen(raw_map) > 1 && direction[0] == 'F')
	{
		ft_free_arr(raw_map);
		error_message(11);
		return (1);
	}
	else if (count == 0 && ft_arrlen(raw_map) > 1 && direction[0] == 'C')
	{
		ft_free_arr(raw_map);
		error_message(12);
		return (1);
	}
	else if (count == 0 && ft_arrlen(raw_map) > 1)
	{
		ft_free_arr(raw_map);
		error_message(10);
		return (1);
	}
	else if (count > 1)
	{
		ft_free_arr(raw_map);
		error_message(5);
		return (1);
	}
	*i = i_save;
	return (0);
}

void	remove_letter(char **line_content, char letter)
{
	int	i;

	i = 0;
	while (line_content[0][i] != '\0')
	{
		if (line_content[0][i] == letter)
			line_content[0][i] = ' ';
		i++;
	}
}
