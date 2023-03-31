/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:42:33 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/31 10:21:43 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H
#include "cub3D.h"

void	draw_player(t_game *game);
int		draw_minimap(t_game *game);
void	get_map_measures(t_game *game);

void	draw_player_i(t_game *game);
int		draw_minimap_i(t_game *game);
double  get_wall_size_i(t_minimap *minimap);

#endif
