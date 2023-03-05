/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:04:16 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/05 17:38:24 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libraries/mlx/include/MLX42/MLX42.h"
# include "../libraries/libft/src/libft/libft.h"
# include "../libraries/libft/src/get_next_line/get_next_line.h"
# include "../libraries/mlx/include/MLX42/MLX42.h"

typedef struct s_map
{
	char			*west;
	char			*east;
	char			*south;
	char			*north;
	int				ceiling_rgb_arr[3];
	int				floor_rgb_arr[3];
	int				map_width;
	int				map_hight;
	char			**map;
}				t_map;

typedef struct s_player
{
	float			x;
	float			y;
	int				head_x;
	int				head_y;
	float			player_angle;
}				t_player;

typedef struct s_hook
{
	mlx_t			*mlx;
	t_player		*player;
	t_map			*map_data;
}				t_hook;

#endif
