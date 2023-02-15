/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:32:27 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/15 14:57:21 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

void	free_textures(t_map *map_data)
{
	free(map_data->we);
	free(map_data->ea);
	free(map_data->so);
	free(map_data->no);
}
