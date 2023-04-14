/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_for_texture.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:47:45 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/14 02:00:37 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libraries/libft/src/libft/libft.h" // ft_* functions
#include "private_parser.h"
#include <stdio.h>

static int	get_texture_file_path(t_map *map_data, char **line,
				int i, int *error);

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] < s2[i])
			return (-1);
		if (s1[i] > s2[i])
			return (1);
		i++;
	}
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	else if (s1[i] == '\0')
		return (-1);
	return (1);
}

int	check_for_texture(t_map *map_data, char *line, int *error)
{
	int			i;
	static char	*definitions[4] = {"NO", "SO", "WE", "EA"};
	char		**splitted_str;

	i = 0;
	splitted_str = ft_split(line, ' ');
	if (splitted_str == NULL)
	{
		ft_free_arr((void **)splitted_str);
		*error = 1;
		return (error_message(8, map_data));
	}
	while (i < 4)
	{
		if (ft_strcmp(splitted_str[0], definitions[i]) == 0)
		{
			get_texture_file_path(map_data, splitted_str, i, error);
			return (1);
		}
		i++;
	}
	ft_free_arr((void **)splitted_str);
	return (0);
}

static int	get_texture_file_path(t_map *map_data, char **line,
	int i, int *error)
{
	if (ft_arrlen((void **)line) != 2)
	{
		ft_free_arr((void **)line);
		*error = 1;
		return (error_message(8, map_data));
	}
	if (map_data->textures[i].path != NULL)
	{
		ft_free_arr((void **)line);
		*error = 1;
		return (error_message(5, map_data));
	}
	cpy_line(&map_data->textures[i].path,
		line[1], ft_strlen(line[1]));
	ft_free_arr((void **)line);
	return (0);
}

char	*cpy_line(char **des, char *src, int len)
{
	int	i;

	i = 0;
	*des = malloc(sizeof(char) * (len + 1));
	if (*des == NULL)
	{
		error_message(4, NULL);
		return (NULL);
	}
	while (i < len - 1)
	{
		(*des)[i] = src[i];
		i++;
	}
	(*des)[i] = '\0';
	return (*des);
}
