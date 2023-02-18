/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 13:46:22 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/18 09:26:33 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include <stdio.h>

static int	get_data_texture(char *raw_line, char **path);
static int	get_path_texture(char **path, char **line_content);

int	get_path(char **raw_map, char *direction, char **path)
{
	int	i;

	i = 0;
	if (finde_line(raw_map, direction, &i))
		return (1);
	if (get_data_texture(raw_map[i], path))
	{
		ft_free_arr(raw_map);
		return (1);
	}
	return (0);
}

static int	get_data_texture(char *raw_line, char **path)
{
	char	**line_content;

	line_content = get_line_content(raw_line);
	if (line_content == NULL)
		return (1);
	if (get_path_texture(path, line_content))
	{
		ft_free_arr(line_content);
		return (1);
	}
	if (check_file(*path, "xpm"))
	{
		ft_free_arr(line_content);
		return (1);
	}
	ft_free_arr(line_content);
	return (0);
}

static int	get_path_texture(char **path, char **line_content)
{
	*path = malloc(sizeof(char) * ft_strlen(line_content[1]));
	if (*path == NULL)
	{
		error_message(4);
		return (1);
	}
	if (cpy_line(*path, line_content[1],
			ft_strlen(line_content[1]) - 1) == NULL)
	{
		ft_free_arr(line_content);
		error_message(7);
		return (1);
	}
	return (0);
}
