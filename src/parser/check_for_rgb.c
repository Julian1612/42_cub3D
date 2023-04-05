/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:47:38 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/05 17:21:27 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include "../cub3D.h"

static int	get_rgb_values(t_map *map_data, char *line, int *error);
static int	check_rgb_values(t_map *map_data, char **line_content);
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

static int	get_rgb_values(t_map *map_data, char *line, int *error)
{
	char	**splitted_str;
	int		boundary;

	boundary = 0;
	splitted_str = ft_split(line, ',');
	if (splitted_str == NULL)
		return (error_message(4, map_data));
	if (ft_arrlen((void **)splitted_str) != 3)
		return (ft_free_arr((void **)splitted_str));
	boundary = remove_letter(splitted_str);
	if (check_rgb_values(map_data, splitted_str))
		return (0);
	init_struct(map_data, splitted_str, boundary, error);
	ft_free_arr((void **)splitted_str);
	return (0);
}

static int	check_rgb_values(t_map *map_data, char **line_content)
{
	if (ft_arrlen((void **)line_content) != 3)
		return (error_textures(5, map_data));
	if (ft_atoi(line_content[0]) > 255 || ft_atoi(line_content[1]) > 255
		|| ft_atoi(line_content[2]) > 255)
		return (error_textures(5, map_data));
	if (ft_atoi(line_content[0]) < 0 || ft_atoi(line_content[1]) < 0
		|| ft_atoi(line_content[2]) < 0)
		return (error_textures(5, map_data));
	return (0);
}

static void	init_struct(t_map *map_data, char **splitted_str, int boundary, int *error)
{
	if (boundary == 1)
	{
		if (map_data->ceiling_color != -1)
		{
			error_message(6, map_data);
			error = 1;
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
			error = 1;
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
