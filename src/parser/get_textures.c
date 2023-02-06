/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:58:13 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/06 14:15:47 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

int	get_textures(t_map *map_data, char **raw_map)
{
	if (get_we(map_data, raw_map))
		return (1);
	printf("get_we: %s\n", map_data->we);
	if (get_ea(map_data, raw_map))
		return (1);
	printf("get_ea: %s\n", map_data->ea);
	if (get_so(map_data, raw_map))
		return (1);
	printf("get_so: %s\n", map_data->so);
	if (get_no(map_data, raw_map))
		return (1);
	printf("get_no: %s\n", map_data->no);
	// if (get_s(map_dara, raw_map))
	// 	return (1);
	// if (get_f(map_dara, raw_map))
	// 	return (1);
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
		error_message(4);
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

// int	get_data(t_map *map_data, char *raw_line)
// {
// 	char	**line_content;

// 	line_content = get_line_content(raw_line);
// 	if (line_content == NULL)
// 	{
// 		error_message(4);
// 		return (1);
// 	}
// 	if (get_path(map_data, line_content))
// 	{
// 		ft_free_arr(line_content);
// 		return (1);
// 	}
// 	if (check_file(map_data->we, "xpm"))
// 	{
// 		ft_free_arr(line_content);
// 		return (1);
// 	}
// 	ft_free_arr(line_content);
// 	return (0);
// }
