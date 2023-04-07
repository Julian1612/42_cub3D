/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:47:38 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/07 16:16:07 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include "../cub3D.h"
#include <stdio.h>

static int	get_rgb_values(t_map *map_data, char *line, int *error);
static int	check_rgb_values(t_map *map_data, char **line_content, int *error);
static void	init_struct(t_map *map_data, char **splitted_str, int boundary, int *error);
static int	remove_letter(char **line_content);

int	check_for_rgb(t_map *map_data, char *line, int *error)
{
	if (ft_strnstr(line, "C", ft_strlen(line)) != NULL
		|| ft_strnstr(line, "F", ft_strlen(line)) != NULL)
	{
		if (get_rgb_values(map_data, line, error))
			return (1);
	}
	return (0);
}

int	is_all_digit(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] != NULL)
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			if ((str[i][j] < '0' || str[i][j] > '9') && str[i][j] != ' ' && str[i][j] != '\n')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	get_rgb_values(t_map *map_data, char *line, int *error)
{
	char	**splitted_str;
	int		boundary;

	boundary = 0;
	splitted_str = ft_split(line, ',');
	if (splitted_str == NULL)
		return (error_message(4, map_data));
	boundary = remove_letter(splitted_str);
	if (ft_arrlen((void **)splitted_str) != 3)
	{
		ft_free_arr((void **)splitted_str);
		*error = 1;
		return (error_textures(5, map_data));
	}
	if (is_all_digit(splitted_str))
	{
		ft_free_arr((void **)splitted_str);
		*error = 1;
		return (error_textures(5, map_data));
	}
	if (splitted_str[0][0] == '\n' || splitted_str[1][0] == '\n' || splitted_str[2][0] == '\n')
		return(1);
	if (check_rgb_values(map_data, splitted_str, error))
		return (1);
	init_struct(map_data, splitted_str, boundary, error);
	ft_free_arr((void **)splitted_str);
	return (0);
}

static int	check_rgb_values(t_map *map_data, char **line_content, int *error)
{
	if (ft_arrlen((void **)line_content) != 3)
	{
		*error = 1;
		return (error_textures(5, map_data));
	}
	if (ft_atoi(line_content[0]) > 255 || ft_atoi(line_content[1]) > 255
		|| ft_atoi(line_content[2]) > 255)
	{
		*error = 1;
		return (error_textures(5, map_data));
	}
	if (ft_atoi(line_content[0]) < 0 || ft_atoi(line_content[1]) < 0
		|| ft_atoi(line_content[2]) < 0)
	{
		*error = 1;
		return (error_textures(5, map_data));
	}
	return (0);
}

static void	init_struct(t_map *map_data, char **splitted_str, int boundary, int *error)
{
	if (boundary == 1)
	{
		if (map_data->ceiling_color != -1)
		{
			error_message(6, map_data);
			*error = 1;
			return ;
		}
		map_data->ceiling_color = convert_to_hexcode(ft_atoi(splitted_str[0]),
				ft_atoi(splitted_str[1]), ft_atoi(splitted_str[2]), 255);
	}
	else if (boundary == 2)
	{
		if (map_data->floor_color != -1)
		{
			error_message(6, map_data);
			*error = 1;
			return ;
		}
		map_data->floor_color = convert_to_hexcode(ft_atoi(splitted_str[0]),
				ft_atoi(splitted_str[1]), ft_atoi(splitted_str[2]), 255);
	}
}

static int	remove_letter(char **line_content)
{
	int	i;

	i = 0;
	while (line_content[0][i] != '\0')
	{
		if (line_content[0][i] == 'F')
		{
			line_content[0][i] = ' ';
			return (1);
		}
		else if (line_content[0][i] == 'C')
		{
			line_content[0][i] = ' ';
			return (2);
		}
		i++;
	}
	return (0);
}
