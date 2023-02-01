/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:14:00 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/01 17:11:16 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	check_args(int *argc, char **argv)
{
	if (*argc != 2)
	{
		error_message(1);
		return (1);
	}
	if (argv[1][0] == '\0')
	{
		error_message(1);
		return (1);
	}
	return (0);
}

int	check_data_type(char *path)
{
	int	path_len;

	path_len = ft_strlen(path);
	if (path[path_len - 3] != 'c' || path[path_len - 2] != 'u'
		|| path[path_len - 1] != 'b')
		return (1);
	return (0);
}

int	check_file(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	close(fd);
	if (fd < 0)
	{
		error_message(2);
		return (1);
	}
	if (check_data_type(argv[1]))
	{
		error_message(3);
		return (1);
	}
	return (0);
}

// int	check_textures(t_map *map_data, char **raw_map)
// {
// 	return (0);
// }

int	get_file_len(int fd)
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
	printf("len: %d\n", len);
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

int	parser(int *argc, char **argv, t_map *map_data)
{
	char	**raw_map;

	(void)map_data;
	raw_map = NULL;
	if (check_args(argc, argv))
		return (1);
	if (check_file(argv))
		return (1);
	map_to_arr(raw_map, argv[1]);
	// if (check_textures(map_data, raw_map))
	// 	return (1);
	// if (check_map(argv[1], map_data))
	// 	return (1);
	// remove this exit(0) later !!!
	exit(0);
	return (0);
}
