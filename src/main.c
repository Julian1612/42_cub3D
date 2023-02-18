/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/18 10:20:40 by jschneid         ###   ########.fr       */
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

	map_data.map = NULL;
	if (parser(&argc, argv, &map_data))
		return (1);
	printf("map_data.floor_rgb_array[0]: %d\n", map_data.floor_rgb_arr[0]);
	printf("map_data.floor_rgb_array[1]: %d\n", map_data.floor_rgb_arr[1]);
	printf("map_data.floor_rgb_array[2]: %d\n", map_data.floor_rgb_arr[2]);
	printf("map_data.ceiling_rgb_array[0]: %d\n", map_data.ceiling_rgb_arr[0]);
	printf("map_data.ceiling_rgb_array[1]: %d\n", map_data.ceiling_rgb_arr[1]);
	printf("map_data.ceiling_rgb_array[2]: %d\n", map_data.ceiling_rgb_arr[2]);
	return (0);
}
