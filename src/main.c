/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/19 15:23:59 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// void	play_music(void)
// {
// 	system("afplay ./sound_track/preussengloria.mp3 &");
// }

int	main(int argc, char **argv)
{
	t_map	map_data;

	if (parser(&argc, argv, &map_data))
		return (1);
	// play_music();
	free(map_data.west);
	free(map_data.east);
	free(map_data.south);
	free(map_data.north);
	ft_free_arr((void **)map_data.map);
	// ft_free_arr((void **)map_data.ceiling_rgb_arr);
	// ft_free_arr((void **)map_data.floor_rgb_arr);
	return (0);
}
