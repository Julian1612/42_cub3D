/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 09:59:24 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/20 17:05:44 by lorbke           ###   ########.fr       */
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
