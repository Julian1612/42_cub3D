/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:17:26 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/11 16:43:15 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <stdio.h>

// static int	get_file_len(char *path);

char	*cpy_line(char **des, char *src, int len)
{
	int	i;

	i = 0;
	*des = malloc(sizeof(char) * (len + 1));
	if (*des == NULL)
	{
		// exit wenn malloc fail
		// error_textures(4);
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

// hier muss gecheckt ob fiel wirklich empty oder malloc error !!!
char	**get_line_content(char *raw_line)
{
	char	**line_content;

	line_content = ft_split(raw_line, ' ');
	if (line_content == NULL)
	{
		// error_textures(8);
		return (NULL);
	}
	return (line_content);
}

// int static	check_for_errors(char **raw_map, char *direction, int count)
// {
// 	if (count == 0 && ft_arrlen(raw_map) > 1 && direction[0] == 'F')
// 	{
// 		ft_free_arr(raw_map);
// 		error_textures(14);
// 		return (1);
// 	}
// 	else if (count == 0 && ft_arrlen(raw_map) > 1 && direction[0] == 'C')
// 	{
// 		ft_free_arr(raw_map);
// 		error_textures(14);
// 		return (1);
// 	}
// 	else if (count == 0 && ft_arrlen(raw_map) > 1)
// 	{
// 		ft_free_arr(raw_map);
// 		error_textures(10);
// 		return (1);
// 	}
// 	else if (count > 1)
// 	{
// 		ft_free_arr(raw_map);
// 		error_textures(5);
// 		return (1);
// 	}
// 	return (0);
// }

int	remove_letter(char **line_content)
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
