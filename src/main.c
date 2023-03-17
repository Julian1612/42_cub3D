/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/17 10:28:23 by jschneid         ###   ########.fr       */
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
#define WIDTH 512
#define HEIGHT 512
#define PLAYER_SIZE 2
#define DIRECTION 2
#define WALL_BLOCK 64
#define NBR_OF_RAYS 1

void	play_music(void)
{
	system("afplay ./sound_track/preussengloria.mp3 &");
}

int	main(int argc, char **argv)
{
	t_map	map_data;

	if (parser(&argc, argv, &map_data))
		return (1);
	play_music();
	return (0);
}
