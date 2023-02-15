/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:16:13 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/15 18:11:21 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

static int	get_file_len(char *path);

int	file_to_arr(char ***raw_map, char *path)
{
	int		i;
	int		len;
	int		fd;
	char	*line;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		error_message(4);
		return (1);
	}
	len = get_file_len(path);
	*raw_map = (char **) malloc(sizeof(char *) * (len + 1));
	if (raw_map == NULL)
	{
		error_message(4);
		return (1);
	}
	(*raw_map)[len] = NULL;
	while (i < len)
	{
		line = get_next_line(fd);
		if (line == NULL && i != len - 1)
		{
			error_message(4);
			return (1);
		}
		if (line != NULL)
			(*raw_map)[i] = ft_strdup(line);
		free(line);
		i++;
	}
	close(fd);
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
