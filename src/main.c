/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:28:59 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/17 18:37:28 by jschneid         ###   ########.fr       */
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
	printf("llelelelelemap_data.west: %s\n", map_data.west);
	// system("leaks cub3D");
	return (0);
}
