/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:58:13 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/15 14:30:01 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include <stdio.h>

int	get_textures(t_map *map_data, char **raw_map)
{
	if (get_we(map_data, raw_map)) // checked
		return (1);
	if (get_ea(map_data, raw_map)) // checked
		return (1);
	if (get_so(map_data, raw_map)) // checked
		return (1);
	if (get_no(map_data, raw_map)) // checked
		return (1);
	if (get_ceiling(map_data, raw_map))
		return (1);
	if (get_floor(map_data, raw_map))
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

char	**get_line_content(char *raw_line)
{
	char	**line_content;

	line_content = ft_split(raw_line, ' ');
	if (line_content == NULL)
	{
		error_message(4);
		return (NULL);
	}
	if (ft_arrlen(line_content) < 2)
	{
		ft_free_arr(line_content);
		error_message(4); // is die nachricht richtig?
		return (NULL);
	}
	return (line_content);
}

int	finde_line(char *direction, char **raw_map, int *i)
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
	if (count > 1)
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
