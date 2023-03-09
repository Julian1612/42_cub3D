/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorbke <lorbke@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:04:16 by jschneid          #+#    #+#             */
/*   Updated: 2023/03/09 20:01:44 by lorbke           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/* INCLUDES																	  */
/* ************************************************************************** */

# include "../libraries/mlx/include/MLX42/MLX42.h" // mlx typedefs

/* ************************************************************************** */
/* DEFINES																	  */
/* ************************************************************************** */

# define WIDTH 512
# define HEIGHT 512
# define PLAYER_SIZE 2
# define DIRECTION 2
# define WALL_BLOCK 64
# define NBR_OF_RAYS 1
# define ERROR -1
# define SUCCESS 0

/* ************************************************************************** */
/* TYPEDEFS																	  */
/* ************************************************************************** */

typedef unsigned int	t_hexcolor;

typedef struct s_texture
{
	char			*path;
	xpm_t			*xpm;
	mlx_texture_t	*texture;
}	t_texture;

// @note ammunition is not implemented
typedef struct s_weapon
{
	t_texture		*texture;
	char			*damage;
	char			*range;
	char			*reload_time;
}	t_weapon;

typedef struct s_map
{
	char		**map;
	t_texture	west;
	t_texture	east;
	t_texture	south;
	t_texture	north;
	t_texture	*sprites;
	t_hexcolor	ceiling_color;
	t_hexcolor	floor_color;
}	t_map;

typedef struct s_player
{
	float			x;
	float			y;
	int				head_x;
	int				head_y;
	float			player_angle;
	t_weapon		*weapon; // @note pointer because the player can change weapons
}	t_player;

// @note enemies are always oriented towards the player
typedef struct s_enemy
{
	float			x;
	float			y;
	t_texture		*texture;
	char			health;
	char			*speed;
	t_weapon		weapon;
}	t_enemy;

// @note items might be added here
typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img_a;
	mlx_image_t		*img_b;
	t_map			map;
	t_player		player;
	t_enemy			*enemies;
}	t_game;

/* ************************************************************************** */
/* FUNCTIONS																  */
/* ************************************************************************** */

void	game_loop(void *param);
void	errexit_msg(char *msg);
void	errexit_mlx_errno(void);

#endif
