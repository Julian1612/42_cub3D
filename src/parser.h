/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 13:19:57 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/23 16:15:14 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "cub3D.h"
# include <stdio.h>
# include <stdlib.h>
# include <memory.h>

// parser
int	parser(int *argc, char **argv, t_map *map_data);

#endif
