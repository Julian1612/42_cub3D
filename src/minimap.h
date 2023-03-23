/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:42:33 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/23 10:08:28 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H
#include "cub3D.h"

int		draw_minimap(t_game *game);
void draw_player(t_game *game);
void	draw_square(t_minimap *minimap_data, int i, int j, int square_size);


#endif
