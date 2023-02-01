/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/01 18:08:24 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#define WIDTH 256
#define HEIGHT 256

int	main(int argc, char **argv)
{
	t_map	*map_data;

	printf("Hello World");
	map_data = NULL;
	if (parser(&argc, argv, map_data))
	{
		// free_data(map_data);
		return (1);
	}
	#ifdef RUN_TEST
		printf("correct");
	#endif
	return (0);
}
