/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:04:16 by jschneid          #+#    #+#             */
/*   Updated: 2023/02/22 14:04:21 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libraries/mlx/include/MLX42/MLX42.h"
# include "../libraries/libft/src/libft/libft.h"
# include "../libraries/libft/src/get_next_line/get_next_line.h"
// # include "parser.h"

typedef struct s_map
{
	char			*west;
	char			*east;
	char			*south;
	char			*north;
	int				ceiling_rgb_arr[3];
	int				floor_rgb_arr[3];
	char			**map;
}				t_map;

#endif
