/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:14:00 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/22 14:05:57 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	parser(int *argc, char **argv, t_map *map_data)
{
	char	**raw_map;

	raw_map = NULL;
	if (check_args(argc, argv))
		return (1);
	if (check_file(argv[1], "cub"))
		return (1);
	if (put_file_content_in_arr(&raw_map, argv[1]))
		return (1);
	if (get_textures(map_data, raw_map))
		return (1);
	if (get_map(map_data, raw_map))
		return (1);
	return (0);
}
