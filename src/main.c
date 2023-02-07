/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/07 11:28:42 by jschneid         ###   ########.fr       */
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
	t_map	map_data;

	if (parser(&argc, argv, &map_data))
		return (1);
	printf("WE: %s\n", map_data.we);
	printf("EA: %s\n", map_data.ea);
	printf("SO: %s\n", map_data.so);
	printf("NO: %s\n", map_data.no);
	printf("C: %d\n", map_data.ceiling_r);
	printf("C: %d\n", map_data.ceiling_g);
	printf("C: %d\n", map_data.ceiling_b);
	printf("F: %d\n", map_data.floor_r);
	printf("F: %d\n", map_data.floor_g);
	printf("F: %d\n", map_data.floor_b);
	return (0);
}
