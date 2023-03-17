/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_file_content_in_arr.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 17:16:13 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/06 14:42:39 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <stdio.h>

static int	get_file_len(char *path);
static int	cpy_data_to_arr(char ***raw_map, int len, int fd);

int	put_file_content_in_arr(char ***raw_map, char *path)
{
	int		len;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		error_message(2);
		return (1);
	}
	// len = get_file_len(path);
	// if (len == 0)
	// {
	// 	error_message(4);
	// 	return (1);
	// }
	if (cpy_data_to_arr(raw_map, len, fd))
		return (1);
	close(fd);
	return (0);
}

static int	cpy_data_to_arr(char ***raw_map, int len, int fd)
{
	int		i;
	char	*line;

	// i = 0;
	// (*raw_map) = (char **) malloc(sizeof(char *) * (len + 1));
	// if (raw_map == NULL)
	// {
	// 	error_message(4);
	// 	return (1);
	// }
	while (i < len)
	{
		line = get_next_line(fd);
		if (line == NULL && i != len - 1)
		{
			error_message(4);
			return (1);
		}
		if (line != NULL)
		{
			(*raw_map)[i] = ft_strdup(line);
			if ((*raw_map)[i] == NULL)
			{
				error_message(4);
				return(1);
			}
		}
		free(line);
		i++;
	}
	(*raw_map)[len - 1] = NULL;
	int y = 0;
	while ((*raw_map)[y])
	{
		y++;
	}
	return (0);
}

// static int	get_file_len(char *path)
// {
// 	int		len;
// 	int		fd;
// 	char	*line;

// 	len = 1;
// 	fd = open(path, O_RDONLY);
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		free(line);
// 		line = get_next_line(fd);
// 		len++;
// 	}
// 	free(line);
// 	close(fd);
// 	return (len);
// }
