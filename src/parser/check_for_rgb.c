/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 14:47:38 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/12 16:08:08 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"

static int	get_rgb_values(t_map *map_data, char *line);
static int	check_rgb_values(char **line_content);
static void	init_struct(t_map *map_data, char **splitted_str, int boundary);
static int	remove_letter(char **line_content);

int	check_for_rgb(t_map *map_data, char *line)
{
	if (ft_strnstr(line, "C", ft_strlen(line)) != NULL
		|| ft_strnstr(line, "F", ft_strlen(line)) != NULL)
	{
		get_rgb_values(map_data, line);
		return (1);
	}
	return (0);
}

static int	get_rgb_values(t_map *map_data, char *line)
{
	char	**splitted_str;
	int		boundary;

	boundary = 0;
	splitted_str = ft_split(line, ',');
	if (splitted_str == NULL)
	{
		error_textures(4);
		return (1);
	}
	if (ft_arrlen(splitted_str) != 3)
	{
		error_textures(14);
		return (1);
	}
	boundary = remove_letter(splitted_str);
	if (check_rgb_values(&line))
		return (1);
	init_struct(map_data, splitted_str, boundary);
	ft_free_arr(splitted_str);
	return (0);
}

static int	check_rgb_values(char **line_content)
{
	if (ft_atoi(line_content[0]) > 255 || ft_atoi(line_content[1]) > 255
		|| ft_atoi(line_content[2]) > 255)
	{
		error_textures(17);
		return (1);
	}
	if (ft_atoi(line_content[0]) < 0 || ft_atoi(line_content[1]) < 0
		|| ft_atoi(line_content[2]) < 0)
	{
		error_textures(17);
		return (1);
	}
	return (0);
}

static void	init_struct(t_map *map_data, char **splitted_str, int boundary)
{
	if (boundary == 1)
	{
		map_data->ceiling_rgb_arr[0] = ft_atoi(splitted_str[0]);
		map_data->ceiling_rgb_arr[1] = ft_atoi(splitted_str[1]);
		map_data->ceiling_rgb_arr[2] = ft_atoi(splitted_str[2]);
	}
	else if (boundary == 2)
	{
		map_data->floor_rgb_arr[0] = ft_atoi(splitted_str[0]);
		map_data->floor_rgb_arr[1] = ft_atoi(splitted_str[1]);
		map_data->floor_rgb_arr[2] = ft_atoi(splitted_str[2]);
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
