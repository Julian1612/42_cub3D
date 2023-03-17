/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:19:57 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/13 10:13:35 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "cub3D.h"

typedef struct s_map
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*door;
	char			*barrel;
	char			*enemy;
	int				floor_rgb_arr[3];
	int				ceiling_rgb_arr[3];
	char			**map;
}					t_map;

// parser
int	parser(int *argc, char **argv, t_map *map_data);

#endif
