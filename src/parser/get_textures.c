/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:58:13 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/02 14:05:48 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

int	get_textures(t_map *map_data, char **raw_map)
{
	if (get_we(map_data, raw_map))
		return (1);
	// if (get_ea(map_dara, raw_map))
	// 	return (1);
	// if (get_so(map_dara, raw_map))
	// 	return (1);
	// if (get_no(map_dara, raw_map))
	// 	return (1);
	// if (get_s(map_dara, raw_map))
	// 	return (1);
	// if (get_f(map_dara, raw_map))
	// 	return (1);
	return (0);
}
