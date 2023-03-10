/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 19:58:13 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/10 13:50:59 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_get_textures.h"
#include <stdio.h>

// @todo add defines for we and ea etxc
// @todo add path with cub file path instead of just the path
int	get_textures(t_map *map_data, char *path)
{
	if (get_path(map_data, path))
		return (1);
	return (0);
}
