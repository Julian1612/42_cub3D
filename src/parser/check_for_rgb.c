/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:47:38 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/24 10:36:47 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
// #include "../cub3D.h"

static int	get_rgb_values(t_map *map_data, char *line);
static int	check_rgb_values(t_map *map_data, char **line_content);
static void	init_struct(t_map *map_data, char **splitted_str, int boundary);
static int	remove_letter(char **line_content);

int	check_for_rgb(t_map *map_data, char *line)
{
	if (ft_strnstr(line, "C", ft_strlen(line)) != NULL
		|| ft_strnstr(line, "F", ft_strlen(line)) != NULL)
	{
		if (get_rgb_values(map_data, line))
			return (ERROR);
	}
	return (SUCCSES);
}

static int	get_rgb_values(t_map *map_data, char *line)
{
	char	**splitted_str;
	int		boundary;

	boundary = 0;
	splitted_str = ft_split(line, ',');
	if (splitted_str == NULL)
		return (error_message(4, map_data));
	if (ft_arrlen((void **)splitted_str) != 3)
	{
		ft_free_arr((void **)splitted_str);
		return (SUCCSES);
	}
	boundary = remove_letter(splitted_str);
	if (check_rgb_values(map_data, splitted_str))
		return (SUCCSES);
	init_struct(map_data, splitted_str, boundary);
	ft_free_arr((void **)splitted_str);
	return (SUCCSES);
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
	return (SUCCSES);
}

static void	init_struct(t_map *map_data, char **splitted_str, int boundary)
{
	if (boundary == 1)
		map_data->ceiling_color = convert_to_hexcode(ft_atoi(splitted_str[0]),
				ft_atoi(splitted_str[1]), ft_atoi(splitted_str[2]), 255);
	else if (boundary == 2)
		map_data->floor_color = convert_to_hexcode(ft_atoi(splitted_str[0]),
				ft_atoi(splitted_str[1]), ft_atoi(splitted_str[2]), 255);
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
			return (ERROR);
		}
		else if (line_content[0][i] == 'C')
		{
			line_content[0][i] = ' ';
			return (2);
		}
		i++;
	}
	return (SUCCSES);
}
