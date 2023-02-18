/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 14:22:15 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/18 10:18:10 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include <stdio.h>

static int	get_rgb_values(int *rgb_values, char *raw_line, char *surface);

int	get_map_color(int *rgb_values, char **raw_map, char *surface)
{
	int	i;

	i = 0;
	if (finde_line(raw_map, surface, &i))
		return (1);
	if (get_rgb_values(rgb_values, raw_map[i], surface))
		return (1);
	return (0);
}

static int	get_rgb_values(int *rgb_values, char *raw_line, char *surface)
{
	char	**line_content;

	line_content = ft_split(raw_line, ',');
	if (line_content == NULL)
	{
		//freen nicht vergessen
		error_message(4);
		return (1);
	}
	if (ft_arrlen(line_content) != 3)
	{
		//freen nicht vergessen
		error_message(14);
		return (1);
	}
	remove_letter(line_content, surface[0]);
	if (check_rgb_values(line_content))
		return (1);
	rgb_values[0] = ft_atoi(line_content[0]);
	rgb_values[1] = ft_atoi(line_content[1]);
	rgb_values[2] = ft_atoi(line_content[2]);
	ft_free_arr(line_content);
	return (0);
}

// error message noch einfuegen
int	check_rgb_values(char **line_content)
{
	if (ft_atoi(line_content[0]) > 255 || ft_atoi(line_content[1]) > 255
		|| ft_atoi(line_content[2]) > 255)
		return (1);
	if (ft_atoi(line_content[0]) < 0 || ft_atoi(line_content[1]) < 0
		|| ft_atoi(line_content[2]) < 0)
		return (1);
	return (0);
}
