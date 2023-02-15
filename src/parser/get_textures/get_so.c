/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_so.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:46:18 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/15 17:32:02 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include <stdio.h>

static int	get_data_so(t_map *map_data, char *raw_line);
static int	get_path_so(t_map *map_data, char **line_content);
static void	free_struct_so(t_map *map_data);

int	get_so(t_map *map_data, char **raw_map)
{
	int	i;

	i = 0;
	if (finde_line("SO", raw_map, &i))
		return (1);
	if (get_data_so(map_data, raw_map[i]))
	{
		ft_free_arr(raw_map);
		return (1);
	}
	return (0);
}

static int	get_data_so(t_map *map_data, char *raw_line)
{
	char	**line_content;

	line_content = get_line_content(raw_line);
	if (line_content == NULL)
		return (1);
	if (get_path_so(map_data, line_content))
	{
		ft_free_arr(line_content);
		return (1);
	}
	if (check_file(map_data->so, "xpm"))
	{
		ft_free_arr(line_content);
		return (1);
	}
	ft_free_arr(line_content);
	return (0);
}

static int	get_path_so(t_map *map_data, char **line_content)
{
	map_data->so = malloc(sizeof(char) * ft_strlen(line_content[1]));
	if (map_data->so == NULL)
	{
		error_message(4);
		return (1);
	}
	if (cpy_line(map_data->so, line_content[1],
			ft_strlen(line_content[1]) - 1) == NULL)
	{
		free_struct_so(map_data);
		ft_free_arr(line_content);
		error_message(4);
		return (1);
	}
	return (0);
}

static void	free_struct_so(t_map *map_data)
{
	free(map_data->we);
	free(map_data->ea);
	free(map_data->so);
}
