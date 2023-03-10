/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:32:27 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/22 13:29:41 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "private_get_textures.h"

void	free_textures(t_map *map_data)
{
	free(map_data->west);
	free(map_data->east);
	free(map_data->south);
	free(map_data->north);
}
