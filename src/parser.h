/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:19:57 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/17 15:20:18 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "cub3D.h"
# define NBR_B_TEXTURES 3
# define DOOR "D"
# define BARREL "B"
# define ENEMY "E"

typedef struct s_map
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			sprite[NBR_B_TEXTURES];
	int				floor_rgb_arr[3];
	int				ceiling_rgb_arr[3];
	int				starting_pos_x;
	int				starting_pos_y;
	char			starting_dir;
	char			**map;
}					t_map;

// parser
int	parser(int *argc, char **argv, t_map *map_data);

#endif
