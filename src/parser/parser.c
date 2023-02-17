/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:14:00 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/17 13:55:24 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int	check_args(int *argc, char **argv);

int	parser(int *argc, char **argv, t_map *map_data)
{
	char	**raw_map;

	raw_map = NULL;
	if (check_args(argc, argv)) //checked
		return (1);
	if (check_file(argv[1], "cub")) //checked
		return (1);
	// filecontent_to_arr
	if (file_to_arr(&raw_map, argv[1])) //checked
		return (1);
	if (get_textures(map_data, raw_map))
		return (1);
	if (get_map(map_data, raw_map))
		return (1);
	printf("correct map\n");
	return (0);
}

static int	check_args(int *argc, char **argv)
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
