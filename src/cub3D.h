/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jschneid <jschneid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:04:16 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/06 11:20:12 by jschneid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libraries/mlx/include/MLX42/MLX42.h"
# include "../libraries/libft/src/libft/libft.h"
# include "../libraries/libft/src/get_next_line/get_next_line.h"
# include "../libraries/mlx/include/MLX42/MLX42.h"
# include "../libraries/garbage_collector/waste_wizard.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

//// textures struct for west east south and north textures
//// map size struct for map width and map height

typedef struct s_map
{
	char			*west;
	char			*east;
	char			*south;
	char			*north;
	int				map_width;
	int				map_height;
	char			**map;
}					t_map;

typedef struct s_player
{
	double			x;
	double			y;
	char			direction;
	int				head_x;
	int				head_y;
	double			player_angle;
}					t_player;

typedef struct s_hook
{
	mlx_t			*mlx;
	t_player		*player;
	t_map			*map_data;
}					t_hook;

#endif
