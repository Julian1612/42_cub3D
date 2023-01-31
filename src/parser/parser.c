/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 19:14:00 by jschneid          #+#    #+#             */
/*   Updated: 2023/01/31 17:48:21 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

int	check_args(int *argc, char **argv)
{
	(void)argv;
	if (*argc != 2)
		return (1);

	exit(0);
	// return (0);
}

int	parser(int *argc, char **argv, t_map *map_data)
{
	(void)map_data;
	check_args(argc, argv);
	return (1);
}
