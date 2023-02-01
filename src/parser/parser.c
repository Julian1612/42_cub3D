/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:14:00 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/01 15:33:20 by jschneid         ###   ########.fr       */
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
	if (path[path_len - 3] != 'b' || path[path_len - 2] != 'u'
		|| path[path_len - 1] != 'c')
		return (1);
	return (0);
}

int	check_textures(char **argv, t_map *map_data)
{
	int	fd;

	(void)map_data;
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

int	parser(int *argc, char **argv, t_map *map_data)
{
	(void)map_data;
	if (check_args(argc, argv))
		return (1);
	if (check_textures(argv, map_data))
		return (1);
	// if (check_map(argv[1], map_data))
	// 	return (1);
	// remove this exit(0) later !!!
	exit(0);
	return (0);
}
