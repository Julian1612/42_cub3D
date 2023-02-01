/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:16:13 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/01 17:21:13 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	get_file_len(int fd);

int	map_to_arr(char **raw_map, char *path)
{
	int		i;
	int		len;
	int		fd;
	char	*line;

	i = 0;
	fd = open(path, O_RDONLY);
	len = get_file_len(fd);
	raw_map = (char **) malloc(sizeof(char *) * (len + 1));
	raw_map[len] = NULL;
	while (i < len)
	{
		line = get_next_line(fd);
		if (line != NULL)
			raw_map[i] = ft_strdup(line);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}

static int	get_file_len(int fd)
{
	int		len;
	char	*line;

	len = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		len++;
	}
	free(line);
	return (len);
}
