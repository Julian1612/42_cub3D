/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:14:00 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/14 11:06:32 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int	parser(int *argc, char **argv, t_map *map_data)
{
	if (check_args(argc, argv))
		return (1);
	if (check_file(argv[1], "cub"))
		return (1);
	if (get_file_data(map_data, argv[1]))
		return (1);
	if (check_map(map_data))
		return (1);
	printf("die map is die geilste map ever\n");
	// if (check_if_all_textures_are_set(map_data))
	// 	return (1);
	return (0);
}
