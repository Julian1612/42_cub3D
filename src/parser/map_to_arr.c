/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:16:13 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/01 19:04:15 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

static int	get_file_len(char *path);

int	map_to_arr(char ***raw_map, char *path)
{
	int		i;
	int		len;
	int		fd;
	char	*line;

	i = 0;
	fd = open(path, O_RDONLY);
	len = get_file_len(path);
	*raw_map = (char **) malloc(sizeof(char *) * (len + 1));
	if (raw_map == NULL)
	{
		error_message(3);
		return (1);
	}
	(*raw_map)[len] = NULL;
	while (i < len)
	{
		line = get_next_line(fd);
		if (line != NULL)
			(*raw_map)[i] = ft_strdup(line);
		// printf("%s", raw_map[i]);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}

static int	get_file_len(char *path)
{
	int		len;
	char	*line;
	int		fd;

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
