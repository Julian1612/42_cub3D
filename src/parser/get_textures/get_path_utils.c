/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:17:26 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/07 17:29:17 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_get_textures.h"
#include <stdio.h>

static int	get_file_len(char *path);

char	*cpy_line(char **des, char *src, int len)
{
	int	i;

	i = 0;
	// printf("src: %s", src);
	*des = malloc(sizeof(char) * (len + 1));
	if (*des == NULL)
	{
		error_textures(4);
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
		error_textures(8);
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
int	find_line(char *cub_file_path, char *direction, char **line_content)
{
	int	i;
	int	fd;
	int	file_len;
	char *line;

	i = 0;
	fd = open(cub_file_path, O_RDONLY);
	file_len = get_file_len(cub_file_path);
	if (fd == -1)
	{
		error_message(2);
		return (1);
	}
	while (i < file_len - 1)
	{
		line = get_next_line(fd);
		if (line == NULL && i != file_len - 1)
		{
			error_message(4);
			return (1);
		}
		if (ft_strnstr(line, direction, ft_strlen(line)) != NULL)
		{
			cpy_line(line_content, line, ft_strlen(line));
			break ;
		}
		free(line);
		i++;
	}
	// printf("line_content: %s\n", line_content);
	// if (check_for_errors(raw_map, direction, count))
	// 	return (1);
	return (0);
}

static int	get_file_len(char *path)
{
	int		len;
	int		fd;
	char	*line;

	len = 1;
	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		len++;
	}
	free(line);
	close(fd);
	return (len);
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


