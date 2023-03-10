/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:22:15 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/10 17:26:39 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_get_textures.h"
#include <stdio.h>

// static int	get_rgb_values(char *boundary, int *rgb_values, char *line_content);
// static int	check_rgb_values(char **line_content);

// int	get_map_color(char *boundary, int *rgb_arr, char *cub_file_path)
// {
//     char    *line_content;

// 	line_content = NULL;
// 	if (find_line(cub_file_path, boundary, &line_content))
// 		return (1);
// 	if (get_rgb_values(boundary, rgb_arr, line_content))
// 		return (1);
// 	return (0);
// }

// static int	get_rgb_values(t_map *map_data, char *line)
// {
// 	char	**splitted_str;
// 	int		boundary;

// 	boundary = 0;
// 	splitted_str = ft_split(line, ',');
// 	if (splitted_str == NULL)
// 	{
// 		error_textures(4);
// 		return (1);
// 	}
// 	if (ft_arrlen(splitted_str) != 3)
// 	{
// 		error_textures(14);
// 		return (1);
// 	}
// 	boundary = remove_letter(splitted_str);
// 	if (check_rgb_values(&line))
// 		return (1);
// 	if (boundary == 1)
// 	{
// 		map_data->ceiling_rgb_arr[0] = ft_atoi(splitted_str[0]);
// 		map_data->ceiling_rgb_arr[1] = ft_atoi(splitted_str[1]);
// 		map_data->ceiling_rgb_arr[2] = ft_atoi(splitted_str[2]);
// 	}
// 	else if (boundary == 2)
// 	{
// 		map_data->floor_rgb_arr[0] = ft_atoi(splitted_str[0]);
// 		map_data->floor_rgb_arr[1] = ft_atoi(splitted_str[1]);
// 		map_data->floor_rgb_arr[2] = ft_atoi(splitted_str[2]);
// 	}

// 	ft_free_arr(splitted_str);
// 	return (0);
// }

// static int	check_rgb_values(char **line_content)
// {
// 	if (ft_atoi(line_content[0]) > 255 || ft_atoi(line_content[1]) > 255
// 		|| ft_atoi(line_content[2]) > 255)
// 	{
// 		error_textures(17);
// 		return (1);
// 	}
// 	if (ft_atoi(line_content[0]) < 0 || ft_atoi(line_content[1]) < 0
// 		|| ft_atoi(line_content[2]) < 0)
// 	{
// 		error_textures(17);
// 		return (1);
// 	}
// 	return (0);
// }
