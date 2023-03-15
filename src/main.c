/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/15 10:01:48 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parser.h"
#include "player_position.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#define WIDTH 512
#define HEIGHT 512
#define PLAYER_SIZE 2
#define DIRECTION 2
#define WALL_BLOCK 64
#define NBR_OF_RAYS 1

int	main(int argc, char **argv)
{
	t_map			map_data;

	if (parser(&argc, argv, &map_data))
		return (1);
	// printf("topo\n");
	// printf("map_data->north: %s\n", map_data.north);
	// printf("map_data->south: %s\n", map_data.south);
	// printf("map_data->east: %s\n", map_data.east);
	// printf("map_data->west: %s\n", map_data.west);
	// printf("map_data->floor_rgb_arr[0]: %d\n", map_data.floor_rgb_arr[0]);
	// printf("map_data->floor_rgb_arr[1]: %d\n", map_data.floor_rgb_arr[1]);
	// printf("map_data->floor_rgb_arr[2]: %d\n", map_data.floor_rgb_arr[2]);
	// printf("map_data->ceiling_rgb_arr[0]: %d\n", map_data.ceiling_rgb_arr[0]);
	// printf("map_data->ceiling_rgb_arr[1]: %d\n", map_data.ceiling_rgb_arr[1]);
	// printf("map_data->ceiling_rgb_arr[2]: %d\n", map_data.ceiling_rgb_arr[2]);
	// int i = 0;
	// while (map_data.map[i])
	// {
	// 	printf("map_data->map[%d]: %s\n", i, map_data.map[i]);
	// 	i++;
	// }
	return (0);
}
