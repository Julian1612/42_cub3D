/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 09:59:24 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/20 10:15:33 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_parser.h"
#include <stdio.h>

void	init_struct_null(t_map *map_data)
{
	map_data->north.path = NULL;
	map_data->south.path = NULL;
	map_data->west.path = NULL;
	map_data->east.path = NULL;
	map_data->ceiling_color = -1;
	map_data->floor_color = -1;
	map_data->map = NULL;
}

unsigned int	convert_to_hexcode(unsigned char r, unsigned char g,
									unsigned char b, unsigned char a)
{
	unsigned int	rgba;

	printf("r: %d, g: %d, b: %d, a: %d\n", r, g, b, a);
	rgba = r;
	rgba = (rgba << 8) + g;
	rgba = (rgba << 8) + b;
	rgba = (rgba << 8) + a;
	return (rgba);
}
