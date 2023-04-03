/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 18:42:33 by jschneid          #+#    #+#             */
/*   Updated: 2023/04/03 15:16:50 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H
# include "cub3D.h"

void	draw_player(t_game *game);
int		render_minimap(t_game *game);
void	get_map_measures(t_game *game);
void	draw_player_map(t_game *game);
int		draw_map(t_game *game);
double	get_wall_size_map(t_minimap *minimap);

#endif
