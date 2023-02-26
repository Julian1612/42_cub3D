/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:17:26 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/26 21:17:32 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_get_textures.h"
#include <stdio.h>

char	*cpy_line(char *dest, char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// hier muss gecheckt ob fiel wirklich empty oder malloc error !!!
char	**get_line_content(char *raw_line)
{
	char	**line_content;

	line_content = ft_split(raw_line, ' ');
	if (line_content == NULL)
	{
		error_textures(8);
		return (NULL);
	}
	return (line_content);
}

int static	check_for_errors(char **raw_map, char *direction, int count)
{
	if (count == 0 && ft_arrlen(raw_map) > 1 && direction[0] == 'F')
	{
		ft_free_arr(raw_map);
		error_textures(14);
		return (1);
	}
	else if (count == 0 && ft_arrlen(raw_map) > 1 && direction[0] == 'C')
	{
		ft_free_arr(raw_map);
		error_textures(14);
		return (1);
	}
	else if (count == 0 && ft_arrlen(raw_map) > 1)
	{
		ft_free_arr(raw_map);
		error_textures(10);
		return (1);
	}
	else if (count > 1)
	{
		ft_free_arr(raw_map);
		error_textures(5);
		return (1);
	}
	return (0);
}

int	finde_line(char **raw_map, char *direction, int *i)
{
	int	count;
	int	i_save;
	int	line_len;

	count = 0;
	i_save = *i;
	while (raw_map[*i])
	{
		printf("1hi %d\n", *i);
		line_len = ft_strlen(raw_map[*i]);
		printf("%d\n", line_len);
		if (line_len >= 2
			&& ft_strnstr(raw_map[*i], direction, line_len) != NULL)
		{
			i_save = *i;
			count++;
		}
		(*i)++;
		printf("2hi %d\n", *i);
	}
	printf("heiland\n");
	if (check_for_errors(raw_map, direction, count))
		return (1);
	*i = i_save;
	return (0);
}

void	remove_letter(char **line_content, char letter)
{
	int	i;

	i = 0;
	while (line_content[0][i] != '\0')
	{
		if (line_content[0][i] == letter)
			line_content[0][i] = ' ';
		i++;
	}
}
